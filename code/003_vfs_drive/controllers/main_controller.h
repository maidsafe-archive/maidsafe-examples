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

#ifndef SAFEDRIVE_CONTROLLERS_MAIN_CONTROLLER_H_
#define SAFEDRIVE_CONTROLLERS_MAIN_CONTROLLER_H_

// std
#include <memory>
#include <string>

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

#include "models/api_model.h"
#include "models/testnet_status_monitor.h"
#include "controllers/system_tray.h"

namespace safedrive {

class MainController : public QObject {
  Q_OBJECT

 public:
  enum Views {
    kLogin,
    kCreateAccount,
    kOpenDrive,
    kTestnetStatus
  };

  explicit MainController(QObject* parent = 0);
  ~MainController() {}
  Q_INVOKABLE void createAccount(const QString& pin,
                                 const QString& keyword,
                                 const QString& password);
  Q_INVOKABLE void login(const QString& pin, const QString& keyword, const QString& password);
  Q_INVOKABLE void mountDrive();
  Q_INVOKABLE void unmountDrive();
  Q_INVOKABLE void showLoginView();
  Q_INVOKABLE void showCreateAccountView();

 protected:
  bool eventFilter(QObject* object, QEvent* event);

 private slots:  // NOLINT - Viv
  void EventLoopStarted();
  void UnhandledException();
  void CreateAccountCompleted();
  void LoginCompleted();
  void OpenDrive();

 private:
  MainController(const MainController&);
  MainController& operator=(const MainController&);
  void LoadViews();
  void InitSignals();
  void CenterToScreen(QQuickWindow* widget);

  QQmlApplicationEngine* main_engine_;
  QMap<Views, QQuickWindow*> views_;
  std::unique_ptr<APIModel> api_model_;
  std::unique_ptr<TestnetStatusMonitor> testnet_status_monitor_;
  std::unique_ptr<SystemTray> system_tray_;
  QFutureWatcher<bool> future_watcher_;
};

}  // namespace safedrive

#endif  // SAFEDRIVE_CONTROLLERS_MAIN_CONTROLLER_H_

