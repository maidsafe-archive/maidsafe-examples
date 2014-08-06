#include <fstream>
#include <iostream>
#include <memory>
#include "maidsafe/common/log.h"
#include "check_bootstraps_connectivity.h"

int main(int argc, char* argv[]) {
  maidsafe::log::Logging::Instance().Initialise(argc, argv);

  try {
    // Open an ofstream managed by a unique_ptr which closes the stream on destruction.
    auto close_and_delete([](std::ofstream* output) {
      output->close();
      delete output;
    });
    std::unique_ptr<std::ofstream, decltype(close_and_delete)> results_fstream(
        new std::ofstream{ "results.json", std::ios::trunc }, close_and_delete);

    CheckBootstrapsConnectivity(*results_fstream);
  }
  catch (const std::exception& e) {
    std::cout << "Error: " << e.what();
    return -1;
  }
  return 0;
}
