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

#ifndef CODE_003_VFS_DRIVE_MODELS_TESTNET_STATUS_MONITOR_H_
#define CODE_003_VFS_DRIVE_MODELS_TESTNET_STATUS_MONITOR_H_

// std
#include <memory>
#include <string>

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

namespace safedrive {

class TestnetStatusMonitor : public QObject {
  Q_OBJECT

 public:
  explicit TestnetStatusMonitor(QObject* parent = 0);

  Q_INVOKABLE void isTestnetAvailable();

 signals: // NOLINT - Viv
  void testnetStatusReceived(bool isAvailable);

 private slots: // NOLINT - Viv
  void NetworkReplyReceived(QNetworkReply* reply);

 private:
  TestnetStatusMonitor(const TestnetStatusMonitor&);
  TestnetStatusMonitor& operator=(const TestnetStatusMonitor&);

  std::unique_ptr<QNetworkAccessManager> network_access_manager_;
};

}  // namespace safedrive

#endif  // CODE_003_VFS_DRIVE_MODELS_TESTNET_STATUS_MONITOR_H_

