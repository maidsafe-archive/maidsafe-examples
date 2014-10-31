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

#include "controllers/system_tray.h"

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

namespace safedrive {

SystemTray::SystemTray()
  : menu_(new QMenu),
    open_drive_(),
    is_logged_in_(false) {
#if defined MAIDSAFE_WIN32
  setIcon(QIcon(":/resources/icons/tray_icon_win.png"));
#else
  setIcon(QIcon(":/resources/icons/tray_icon_osx.png"));
#endif

  setToolTip("SAFEdrive");

  open_drive_ = menu_->addAction(tr("Open Drive"), this, SIGNAL(OpenDriveRequested()));
  open_drive_->setVisible(false);

  menu_->addAction(tr("Quit"), qApp, SLOT(quit()));
  setContextMenu(menu_);
}

void SystemTray::SetIsLoggedIn(bool is_logged_in) {
  is_logged_in_ = is_logged_in;
  open_drive_->setVisible(is_logged_in_);
}

void SystemTray::OnSystrayActivate(QSystemTrayIcon::ActivationReason reason) {
  if (reason == QSystemTrayIcon::DoubleClick && is_logged_in_)
    emit OpenDriveRequested();
}

SystemTray::~SystemTray() {
  delete menu_;
  menu_ = nullptr;
}

}  // namespace safedrive
