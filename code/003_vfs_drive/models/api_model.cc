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

#include "models/api_model.h"

#include <map>
#include <vector>

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

namespace ms = maidsafe;

namespace safedrive {

APIModel::APIModel(QObject* parent)
    : QObject(parent),
      private_client_() {}

bool APIModel::CreateAccount(const QString& /*pin*/, const QString& /*keyword*/, const QString& /*password*/) {
  try {
    //    private_client_ = ms::PrivateClient::CreateAccount(keyword.toStdString(),
    //                                                       std::stoi(pin.toStdString()),
    //                                                       password.toStdString()).get();
        return true;
  } catch(const ms::maidsafe_error& /*error_code*/) {
    emit createAccountErrorRaised("Error Creating Account");
  } catch(...) {
    emit UnhandledException();
  }
  return false;
}

bool APIModel::Login(const QString& /*pin*/, const QString& /*keyword*/, const QString& /*password*/) {
  try {
//    private_client_ = ms::PrivateClient::Login(keyword.toStdString(),
//                                               std::stoi(pin.toStdString()),
//                                               password.toStdString()).get();
    return true;
  }
  catch (const ms::maidsafe_error& /*error_code*/) {
    emit loginErrorRaised("Error Logging in");
  }
  catch (...) {
    emit UnhandledException();
  }
  return false;
}

void APIModel::MountDrive() {
}

void APIModel::UnmountDrive() {
}

}  // namespace safedrive

