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

CheckBox {
  style: CheckBoxStyle {
    indicator: Item {
      implicitHeight: 15
      implicitWidth: 19 + textLabel.contentWidth

      Rectangle {
        id: glyph
        anchors {
          left: parent.left
          verticalCenter: parent.verticalCenter
        }
        border {
          color: {
            if (!control.enabled) {
              DefaultBrushes.disabledGray
            } else if (control.hovered) {
              DefaultBrushes.normalBlue
            } else if (control.activeFocus) {
              DefaultBrushes.focusBlack
            } else {
              DefaultBrushes.labelGray
            }
          }
          width: 1
        }
        color: {
          if (!control.checked) {
            DefaultBrushes.white
          } else if (!control.enabled) {
            DefaultBrushes.disabledGray
          } else {
            DefaultBrushes.labelGray
          }
        }
        height: 15
        radius: 1
        width: 15

        Image {
          anchors {
            fill: parent
            margins: 1
          }
          source: "qrc:/resources/icons/checkbox_glyph.svg"
          visible: control.checked
        }
      }
      Label {
        id: textLabel
        anchors {
          left: glyph.right
          leftMargin: 5
        }
        color: !control.enabled ? DefaultBrushes.disabledGray : DefaultBrushes.labelGray
        font {
          family: "Arial"
          pixelSize: 14
        }
        text: control.text
        verticalAlignment: Qt.AlignVCenter
      }
    }
    label: Text{}
  }

  Keys.onEnterPressed: checked = !checked;
  Keys.onReturnPressed: checked = !checked;
  Keys.onSpacePressed: checked = !checked;
}
