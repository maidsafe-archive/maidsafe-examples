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

#include "models/testnet_status_monitor.h"
#include <iostream>

namespace safedrive {

TestnetStatusMonitor::TestnetStatusMonitor(QObject* parent)
  : QObject(parent),
    network_access_manager_(new QNetworkAccessManager(this)) {
  connect(network_access_manager_.get(), SIGNAL(finished(QNetworkReply*)),             // NOLINT - Viv
          this,                          SLOT(NetworkReplyReceived(QNetworkReply*)));  // NOLINT - Viv
}

void TestnetStatusMonitor::isTestnetAvailable() {
  QUrl url("http://visualiser.maidsafe.net:8080/backend/testnetStatus");
  network_access_manager_->get(QNetworkRequest(url));
}

void TestnetStatusMonitor::NetworkReplyReceived(QNetworkReply* reply) {
  if (reply->error() != QNetworkReply::NoError) {
    emit testnetStatusReceived(false);
    return;
  }

  QString data = static_cast<QString>(reply->readAll());
  QScriptEngine engine;
  QScriptValue is_available = engine.evaluate("(" + data + ")").property("isReady");
  emit testnetStatusReceived(is_available.toBool());
  delete reply;
}

}  // namespace safedrive
