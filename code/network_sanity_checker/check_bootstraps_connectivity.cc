#include "check_bootstraps_connectivity.h"

#include <exception>
#include <future>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "boost/asio/ip/udp.hpp"
#include "maidsafe/common/node_id.h"
#include "maidsafe/common/utils.h"
#include "maidsafe/rudp/managed_connections.h"
#include "maidsafe/rudp/return_codes.h"

using boost::asio::ip::udp;
using boost::asio::ip::address;

namespace {

std::future<int> CanConnect(const udp::endpoint& contact) {
  return std::async(std::launch::async, [contact]()->int {
    maidsafe::asymm::Keys keys{ maidsafe::asymm::GenerateKeyPair() };
    maidsafe::NodeId chosen_bootstrap_peer;
    maidsafe::rudp::NatType nat_type;
    maidsafe::rudp::ManagedConnections managed_connections;
    return managed_connections.Bootstrap(
        std::vector<udp::endpoint>{ contact },
        [](const std::string&) {},
        [](const maidsafe::NodeId&) {},
        maidsafe::NodeId{ maidsafe::NodeId::IdType::kRandomId },
        std::make_shared<maidsafe::asymm::PrivateKey>(keys.private_key),
        std::make_shared<maidsafe::asymm::PublicKey>(keys.public_key),
        chosen_bootstrap_peer,
        nat_type);
  });
}

void HandleResult(std::pair<const udp::endpoint, std::future<int>>& result,
                  bool is_last_result,
                  std::ofstream& results_fstream) {
  std::string closer{ is_last_result ? " }\n" : " },\n" };
  try {
    results_fstream << "    { \"contact\": \"" << result.first << "\", \"canConnect\": " << std::boolalpha;
    int code{ result.second.get() };
    if (code == maidsafe::rudp::kSuccess) {
      results_fstream << true << closer;
      return;
    }
    std::cout << "Failed to connect to " << result.first << " with return code " << code << '\n';
  }
  catch (const std::exception& e) {
    std::cout << "Exception trying to connect to " << result.first << ": " << e.what() << '\n';
  }
  results_fstream << false << closer;
}

}  // unnamed namespace

void CheckBootstrapsConnectivity(std::ofstream& results_fstream) {
  std::map<udp::endpoint, std::future<int>> results;
  results.emplace(udp::endpoint{ address::from_string("23.239.27.245"),  maidsafe::kLivePort }, std::future<int>{});
  results.emplace(udp::endpoint{ address::from_string("95.85.32.100"),   maidsafe::kLivePort }, std::future<int>{});
  results.emplace(udp::endpoint{ address::from_string("104.131.253.66"), maidsafe::kLivePort }, std::future<int>{});
  results.emplace(udp::endpoint{ address::from_string("106.185.24.221"), maidsafe::kLivePort }, std::future<int>{});
  results.emplace(udp::endpoint{ address::from_string("128.199.159.50"), maidsafe::kLivePort }, std::future<int>{});
  results.emplace(udp::endpoint{ address::from_string("178.79.156.73"),  maidsafe::kLivePort }, std::future<int>{});

  for (auto& result : results)
    result.second = CanConnect(result.first);

  results_fstream << "{\n  \"bootstrapConnectivityCheck\": [\n";

  auto itr(std::begin(results));
  const auto last_element_itr(--std::end(results));
  while (itr != last_element_itr)
    HandleResult(*itr++, false, results_fstream);
  HandleResult(*itr, true, results_fstream);

  results_fstream << "  ]\n}\n";
}
