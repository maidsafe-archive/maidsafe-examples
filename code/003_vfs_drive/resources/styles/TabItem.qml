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
import "../js/properties.js" as DefaultProperties

Item {
  property alias text : tabLabel.text
  property alias contentHeight : tabLabel.contentHeight
  property int index : 0
  property bool isSelected : false
  property int horizontalMargin : 5
  signal clicked

  id: tabItem
  implicitWidth: tabLabel.contentWidth + (tabItem.horizontalMargin * 2)

  Label {
    id: tabLabel
    anchors {
      leftMargin: tabItem.horizontalMargin
      rightMargin: tabItem.horizontalMargin
    }
    color: {
      if (tabItem.isSelected) {
        DefaultBrushes.normalBlue
      } else if (mouseArea.containsMouse) {
        DefaultBrushes.focusBlack
      } else {
        DefaultBrushes.darkerGray
      }
    }
    font {
      family: "Arial"
      pixelSize: DefaultProperties.tabItemFontSize
    }
    MouseArea {
      id: mouseArea
      anchors.fill: parent
      hoverEnabled: true
      acceptedButtons: Qt.LeftButton
      onClicked: tabItem.clicked()
    }
  }
}
