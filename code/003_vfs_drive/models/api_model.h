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

#ifndef SAFEDRIVE_MODELS_API_MODEL_H_
#define SAFEDRIVE_MODELS_API_MODEL_H_

// std
#include <memory>
#include <string>

#include "boost/optional.hpp"

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

#include "maidsafe.h"

namespace safedrive {

class APIModel : public QObject {
  Q_OBJECT

 public:
  explicit APIModel(QObject* parent = 0);
  ~APIModel() {}

  bool CreateAccount(const QString& pin, const QString& keyword, const QString& password);
  bool Login(const QString& pin, const QString& keyword, const QString& password);
  void MountDrive();
  void UnmountDrive();

 signals:
  void createAccountErrorRaised(const QString& errorMessage);
  void loginErrorRaised(const QString& errorMessage);
  void mountOrUnmountErrorRaised(const QString& errorMessage);
  void UnhandledException();

 private:
  APIModel(const APIModel&);
  APIModel& operator=(const APIModel&);
  std::unique_ptr<maidsafe::PrivateClient> private_client_;
};

}  // namespace safedrive

#endif  // SAFEDRIVE_MODELS_API_MODEL_H_
