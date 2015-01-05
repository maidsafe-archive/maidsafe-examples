/*  Copyright 2014 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#include <fstream>
#include <iostream>
#include <memory>
#include "maidsafe/common/config.h"
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
    std::string output_path{ (maidsafe::ThisExecutableDir() / "results.json").string() };
    std::unique_ptr<std::ofstream, decltype(close_and_delete)> results_fstream(
        new std::ofstream{ output_path, std::ios::trunc }, close_and_delete);

    CheckBootstrapsConnectivity(*results_fstream);
  }
  catch (const std::exception& e) {
    std::cout << "Error: " << e.what();
    return -1;
  }
  return 0;
}
