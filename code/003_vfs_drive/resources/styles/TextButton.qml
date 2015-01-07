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

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import "../js/brushes.js" as DefaultBrushes

Button {
  style: ButtonStyle {
    background: Rectangle {
      antialiasing: true
      border {
        color: DefaultBrushes.transparent
        width: 0
      }
      color: DefaultBrushes.transparent
      implicitHeight: 30
    }
    label: Label {
      anchors.fill: parent
      color: control.enabled && !control.pressed && control.hovered ? DefaultBrushes.focusBlack : DefaultBrushes.labelGray
      font {
        family: "Arial"
        pixelSize: 14
      }
      horizontalAlignment: Qt.AlignHCenter
      text: control.text
      verticalAlignment: Qt.AlignVCenter
    }
  }

  Keys.onEnterPressed: clicked();
  Keys.onReturnPressed: clicked();
  Keys.onSpacePressed: clicked();
}
