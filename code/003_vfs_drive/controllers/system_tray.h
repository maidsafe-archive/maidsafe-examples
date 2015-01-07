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

#ifndef CODE_003_VFS_DRIVE_CONTROLLERS_SYSTEM_TRAY_H_
#define CODE_003_VFS_DRIVE_CONTROLLERS_SYSTEM_TRAY_H_

#include <string>

#include "helpers/qt_push_headers.h"
#include "helpers/qt_pop_headers.h"

class QMenu;
class QAction;

namespace safedrive {

class SystemTray : public QSystemTrayIcon {
  Q_OBJECT

 public:
  SystemTray();
  ~SystemTray();
  void SetIsLoggedIn(bool is_logged_in);

 signals:  // NOLINT - Viv
  void ShowSafeDriveRequested();

 private slots:  // NOLINT - Viv
  void OnSystrayActivate(QSystemTrayIcon::ActivationReason reason);

 private:
  SystemTray(const SystemTray&);
  SystemTray& operator=(const SystemTray&);

  QMenu* menu_;
  QAction* open_drive_;
  bool is_logged_in_;
};

}  // namespace safedrive

#endif  // CODE_003_VFS_DRIVE_CONTROLLERS_SYSTEM_TRAY_H_
