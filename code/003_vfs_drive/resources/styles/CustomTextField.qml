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

TextField {
  FontLoader { id: arialFont; name: "Arial" }

  property bool isMarkerTextVisible : true

  font.pixelSize: 12
  horizontalAlignment: Qt.AlignHCenter
  style: TextFieldStyle {
    background: Rectangle {
      border {
        color: {
          if (!control.enabled) {
            DefaultBrushes.disabledGray
          } else if (control.activeFocus) {
            DefaultBrushes.focusBlack
          } else {
            DefaultBrushes.borderGray
          }
        }
        width: 1
      }
      implicitHeight: 30
      implicitWidth: 225
    }
    font: arialFont.name
    selectionColor: DefaultBrushes.selectionBlue
    selectedTextColor: DefaultBrushes.focusBlack
    textColor: !control.enabled ? DefaultBrushes.disabledGray : DefaultBrushes.focusBlack
  }
}
