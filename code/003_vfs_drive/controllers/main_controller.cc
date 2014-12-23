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
      system_tray_{new SystemTray} {
  qmlRegisterType<APIModel>("SAFEdrive", 1, 0, "APIModel");
  qmlRegisterUncreatableType<MainController>("SAFEdrive", 1, 0, "Controller", "Error!! Attempting to access uncreatable type");
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

void MainController::showLoginView() { setCurrentView(Login); }

void MainController::showCreateAccountView() { setCurrentView(CreateAccount); }

MainController::ShowView MainController::currentView() const { return current_view_; }
void MainController::setCurrentView(const ShowView new_current_view) {
  if(new_current_view != current_view_) {
    current_view_ = new_current_view;
    emit currentViewChanged(current_view_);
  }
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
  auto root_context = main_engine_->rootContext();
  root_context->setContextProperty(kMainController, this);
  root_context->setContextProperty(kAPIModel, api_model_.get());
  root_context->setContextProperty(kTestnetStatusMonitor, testnet_status_monitor_.get());

  main_engine_->load(QUrl(QString("qrc:/views/MainWindow.qml")));
  InitSignals();

  main_window_ = qobject_cast<QQuickWindow*>(main_engine_->rootObjects().first());
  main_window_->show();
  CenterToScreen(main_window_);
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

  main_window_->hide();
  system_tray_->SetIsLoggedIn(true);
}

void MainController::LoginCompleted() {
  disconnect(&future_watcher_, SIGNAL(finished()), this, SLOT(LoginCompleted()));
  if (future_watcher_.isCanceled() || !future_watcher_.result())
    return;

  main_window_->hide();
  system_tray_->SetIsLoggedIn(true);
}

void MainController::OpenDrive() {
  // Open SAFE Drive
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
