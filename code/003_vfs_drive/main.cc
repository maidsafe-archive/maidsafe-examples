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

#include <iostream>

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

#include "controllers/application.h"
#include "controllers/main_controller.h"

#include "maidsafe/common/config.h"
#include "maidsafe/common/log.h"

int main(int argc, char *argv[]) {
  safedrive::Application application(argc, argv);
  auto log_options(maidsafe::log::Logging::Instance().Initialise(argc, argv));

#ifdef MAIDSAFE_WIN32
  // Check and exit if duplicate instance
  if (!application.IsUniqueInstance())
    return 0;
#endif

  application.addLibraryPath(qApp->applicationDirPath() + "/plugins");
  application.setOrganizationDomain("http://www.maidsafe.net");
  application.setOrganizationName("MaidSafe.net Ltd.");
  application.setApplicationName("SAFEDrive");

  try {
    safedrive::MainController main_controller;
    application.SetErrorHandler(main_controller);
    return application.exec();
  } catch(const std::exception& ex) {
    std::cerr << "STD Exception Caught: " << ex.what();
    return -1;
  } catch(...) {
    std::cerr << "Default Exception Caught";
    return -1;
  }
}

