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

#include "controllers/main_controller.h"

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

#include "maidsafe/common/application_support_directories.h"

#include "helpers/custom_message_box.h"
#include "helpers/qml_indexers.h"

namespace safedrive {

MainController::MainController(QObject* parent)
    : QObject(parent),
      main_engine_(),
      views_(),
      api_model_(),
      testnet_status_monitor_(),
      system_tray_(new SystemTray),
      future_watcher_() {
  qmlRegisterType<APIModel>("SAFEdrive", 1, 0, "APIModel");
  installEventFilter(this);
  QTimer::singleShot(0, this, SLOT(EventLoopStarted()));
}

void MainController::createAccount(const QString& pin,
                                   const QString& keyword,
                                   const QString& password) {
  connect(&future_watcher_, SIGNAL(finished()), this, SLOT(CreateAccountCompleted()));
  future_watcher_.setFuture(
    QtConcurrent::run(api_model_.get(), &APIModel::CreateAccount, pin, keyword, password));
}

void MainController::login(const QString& pin, const QString& keyword, const QString& password) {
  connect(&future_watcher_, SIGNAL(finished()), this, SLOT(LoginCompleted()));
  future_watcher_.setFuture(
    QtConcurrent::run(api_model_.get(), &APIModel::Login, pin, keyword, password));
}

void MainController::mountDrive() {
  QtConcurrent::run(api_model_.get(), &APIModel::MountDrive);
}

void MainController::unmountDrive() {
  QtConcurrent::run(api_model_.get(), &APIModel::UnmountDrive);
}

void MainController::showLoginView() {
  views_[kTestnetStatus]->hide();
  views_[kCreateAccount]->hide();
  views_[kLogin]->show();
  CenterToScreen(views_[kLogin]);
}

void MainController::showCreateAccountView() {
  views_[kTestnetStatus]->hide();
  views_[kLogin]->hide();
  views_[kCreateAccount]->show();
  CenterToScreen(views_[kCreateAccount]);
}

bool MainController::eventFilter(QObject* object, QEvent* event) {
  if (object == this && event->type() >= QEvent::User && event->type() <= QEvent::MaxUser) {
    UnhandledException();
    return true;
  }
  return QObject::eventFilter(object, event);
}

void MainController::EventLoopStarted() {
  api_model_.reset(new APIModel);
  testnet_status_monitor_.reset(new TestnetStatusMonitor);
  main_engine_ = new QQmlApplicationEngine();
  main_engine_->addImportPath(qApp->applicationDirPath() + "/qml");
  main_engine_->addPluginPath(qApp->applicationDirPath() + "/plugins");
  auto root_context_ = main_engine_->rootContext();
  root_context_->setContextProperty(kMainController, this);
  root_context_->setContextProperty(kAPIModel, api_model_.get());
  root_context_->setContextProperty(kTestnetStatusMonitor, testnet_status_monitor_.get());
  LoadViews();
  InitSignals();

  QQuickWindow* current_view = views_[kTestnetStatus];
  current_view->show();
  CenterToScreen(current_view);
  system_tray_->show();
}

void MainController::UnhandledException() {
  CustomMessageBox::Show(
      tr("SAFEdrive has encountered an unexpected error. Please relaunch the app"),
      QMessageBox::Critical);
  qApp->quit();
}

void MainController::CreateAccountCompleted() {
  disconnect(&future_watcher_, SIGNAL(finished()), this, SLOT(CreateAccountCompleted()));
  if (future_watcher_.isCanceled() || !future_watcher_.result())
    return;

  views_[kCreateAccount]->hide();
  system_tray_->SetIsLoggedIn(true);
  qApp->setQuitOnLastWindowClosed(false);
}

void MainController::LoginCompleted() {
  disconnect(&future_watcher_, SIGNAL(finished()), this, SLOT(LoginCompleted()));
  if (future_watcher_.isCanceled() || !future_watcher_.result())
    return;

  views_[kLogin]->hide();
  system_tray_->SetIsLoggedIn(true);
  qApp->setQuitOnLastWindowClosed(false);
}

void MainController::OpenDrive() {
  // Open SAFE Drive
}

void MainController::LoadViews() {
  int view_count(4);

  for (int i = 0; i < view_count; ++i) {
    Views view_enum;
    QString view_name;
    switch (i) {
      case 0:
        view_enum = kLogin;
        view_name = "Login";
        break;
      case 1:
        view_enum = kCreateAccount;
        view_name = "CreateAccount";
        break;
      case 2:
        view_enum = kOpenDrive;
        view_name = "OpenDrive";
        break;
      case 3:
        view_enum = kTestnetStatus;
        view_name = "TestnetStatus";
        break;
      default:
        throw new std::exception();
    }
    main_engine_->load(QUrl(QString("qrc:/views/%1.qml").arg(view_name)));
    views_[view_enum] = qobject_cast<QQuickWindow*>(main_engine_->rootObjects().value(i));
    if (!views_[view_enum])
      throw new std::exception();
  }
}

void MainController::InitSignals() {
  connect(system_tray_.get(),   &SystemTray::OpenDriveRequested,
          this,                 &MainController::OpenDrive);
  connect(api_model_.get(),     &APIModel::UnhandledException,
          this,                 &MainController::UnhandledException);
}

void MainController::CenterToScreen(QQuickWindow* widget) {
  if (!widget)
    return;
  QDesktopWidget* m = QApplication::desktop();
  QRect desk_rect = m->screenGeometry(m->screenNumber(QCursor::pos()));
  int desk_x = desk_rect.width();
  int desk_y = desk_rect.height();
  int x = widget->width();
  int y = widget->height();
  widget->setFramePosition(
      QPoint(desk_x / 2 - x / 2 + desk_rect.left(), desk_y / 2 - y / 2 + desk_rect.top()));
}

}  // namespace safedrive
