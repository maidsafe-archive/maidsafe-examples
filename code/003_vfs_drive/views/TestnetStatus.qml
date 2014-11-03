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
import SAFEdrive 1.0
import "../resources/styles"
import "../resources/js/brushes.js" as DefaultBrushes

CustomWindow {
  content: Item {
    id: rootItem
    anchors.fill: parent
    Component.onCompleted: testnetStatusMonitor.isTestnetAvailable()
    Connections {
      onTestnetStatusReceived: {
        if (isAvailable) {
          statusBar.clearStatusInfo()
          mainController.showLoginView()
        } else {
          progressStatus.visible = false;
          errorStatus.visible = true;
        }
      }
      target: testnetStatusMonitor
    }

    Item {
      id: progressStatus
      anchors.fill: parent
      visible: true

      StatusBar  {
        id: statusBar
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: parent.top
          topMargin: 80
        }
        Component.onCompleted: statusBar.showProgressStatus(6)
      }
      Label {
        id: statusLabel
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: statusBar.bottom
          topMargin: 20
        }
        color: DefaultBrushes.labelGray
        font {
          family: "Arial"
          pixelSize: 18
        }
        text: qsTr("Checking Testnet Status...")
      }
    }

    Item {
      id: errorStatus
      anchors.fill: parent
      visible: false

      Image {
        id: errorImage
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: parent.top
          topMargin: 80
        }
        height: 35
        width: 35
        source: "qrc:/resources/icons/not_connected.svg"
      }

      Label {
        id: errorStatusLabel
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: errorImage.bottom
          topMargin: 20
        }
        color: DefaultBrushes.normalRed
        font {
          family: "Arial"
          pixelSize: 18
        }
        horizontalAlignment: Qt.AlignHCenter
        text: qsTr("Testnet is unavailable\nPlease try again later")
      }
      BlueButton {
        id: quitButton
        anchors {
          bottom: parent.bottom
          right: parent.right
        }
        text: qsTr("Quit")
        onClicked: Qt.quit()
      }
      GrayButton {
        id: ignoreButton
        anchors {
          bottom: parent.bottom
          right: quitButton.left
          rightMargin: 10
        }
        text: qsTr("Ignore")
        onClicked: mainController.showLoginView()
      }
    }
  }
}
