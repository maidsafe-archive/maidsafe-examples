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

#include <thread>
#include <chrono>
#include <map>
#include <vector>

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

#include "boost/filesystem.hpp"

namespace ms = maidsafe;

namespace safedrive {

APIModel::APIModel(QObject* parent)
    : QObject(parent),
      private_client_() {}

bool APIModel::CreateAccount(const QString& pin, const QString& keyword, const QString& password) {
  try {
        private_client_ = ms::PrivateClient::CreateAccount(keyword.toStdString(),
                                                           std::stoi(pin.toStdString()),
                                                           password.toStdString()).get();
        return true;
  } catch(const ms::maidsafe_error& /*error_code*/) {
    emit createAccountErrorRaised("Error Creating Account");
  } catch(...) {
    emit UnhandledException();
  }
  return false;
}

bool APIModel::Login(const QString& pin, const QString& keyword, const QString& password) {
  try {
    private_client_ = ms::PrivateClient::Login(keyword.toStdString(),
                                               std::stoi(pin.toStdString()),
                                               password.toStdString()).get();
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

QString APIModel::MountDrive() {
  try {
    /*
    auto& account_handler(private_client_->GetAccountHandler());

    boost::filesystem::path drive_name{ms::RandomAlphaNumericString(32)};
    boost::filesystem::path mount_path{boost::filesystem::unique_path(
            boost::filesystem::temp_directory_path() / "MaidSafe_Private_Client_%%%%-%%%%-%%%%")};

    ms::crypto::AES256Key symm_key{ms::RandomString(ms::crypto::AES256_KeySize)};
    ms::crypto::AES256InitialisationVector symm_iv{ms::RandomString(ms::crypto::AES256_IVSize)};
    ms::crypto::CipherText encrypted_maid{ms::passport::EncryptMaid(
            account_handler.account().passport->GetMaid(),
            symm_key, symm_iv)};

    ms::drive::Options options;
    options.mount_path = mount_path;
    options.drive_name = drive_name;
    options.unique_id = account_handler.account().unique_user_id;
    options.root_parent_id = account_handler.account().root_parent_id;
    options.encrypted_maid = encrypted_maid->string();
    options.symm_key = symm_key.string();
    options.symm_iv = symm_iv.string();
    drive_launcher_.reset(new ms::drive::Launcher(options));
    return QString::fromStdString(drive_launcher_->kMountPath().string());
    */
    std::this_thread::sleep_for(std::chrono::seconds{2});
    return QCoreApplication::applicationDirPath();
  }
  catch (const ms::maidsafe_error&) {
    emit mountOrUnmountErrorRaised("Error Mounting Device. Try Again.");
  }
  catch (...) {
    emit UnhandledException();
  }
  return QString{""};
}

bool APIModel::UnmountDrive() {
  static bool error_simulator;  // simulate error
  try {
    std::this_thread::sleep_for(std::chrono::seconds{1});  // simulate delay
    if (!error_simulator) { error_simulator = true; throw ms::maidsafe_error{}; }
    return true;
  }
  catch (const ms::maidsafe_error&) {
    emit mountOrUnmountErrorRaised("Error Unmounting Device. Try Again.");
  }
  catch (...) {
    emit UnhandledException();
  }
  return false;
}

}  // namespace safedrive

