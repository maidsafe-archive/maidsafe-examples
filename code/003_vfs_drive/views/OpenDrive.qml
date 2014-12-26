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
import "../resources/js/properties.js" as DefaultProperties

Item {
  id: rootItem

  HeaderLabel {
    id: headerLabel
    anchors {
      top: parent.top
      topMargin: 20
    }
    text: qsTr("Your Drive")
  }

  Item {
    id: verticalSpacer
    anchors { top: headerLabel.bottom; horizontalCenter: parent.horizontalCenter }
    height: 45; width: 1
  }

  Row {
    id: mountDismountRow

    anchors { top: verticalSpacer.bottom; left: parent.left; leftMargin: 15 }
    spacing: 8

    opacity: !statusBar.isInProgress / 2 + 0.5
    enabled: !statusBar.isInProgress

//    Image {
//      id: safeDriveImage
//    }

    Rectangle {
      id: placeholderForProperImage
      height: 30
      width: 15
      color: DefaultBrushes.labelGray
    }

    Text {
      id: safeDriveText

      text: qsTr("SAFE Drive")
      font { family: "Arial"; pointSize: DefaultProperties.subHeaderFontPointSize }

      anchors { verticalCenter: parent.verticalCenter }
      color: DefaultBrushes.labelGray
    }

    Item {
      id: horizSpacer
      height: 1; width: 50
    }

    Image {
      id: openDriveImage
      anchors { verticalCenter: parent.verticalCenter }
      source: "qrc:/resources/icons/open_drive.png"
      opacity: mainController.currentView === MainController.UnmountOrOpenDrive
      enabled: opacity

      MouseArea {
        anchors.fill: parent
        onClicked: mainController.openDrive()
      }
    }

    Image {
      id: mountDismountImage

      anchors { verticalCenter: parent.verticalCenter }
      source: mainController.currentView === MainController.MountDrive ?
                "qrc:/resources/icons/mount_drive.png" : "qrc:/resources/icons/unmount_drive.png"

      MouseArea {
        anchors.fill: parent
        onClicked: {
          statusBar.showProgressStatus(DefaultProperties.smallProgressBarRadius)
          if(mainController.currentView === MainController.MountDrive) mainController.mountDrive()
          else mainController.unmountDrive()
        }
      }
    }
  }

  StatusBar  {
    id: statusBar
    anchors {
      horizontalCenter: parent.horizontalCenter
      top: mountDismountRow.bottom
      topMargin: 30
    }
    Connections {
      onMountOrUnmountErrorRaised: statusBar.showErrorStatus(errorMessage)
      target: apiModel
    }
    Connections {
      onCurrentViewChanged: statusBar.clearStatusInfo()
      target: mainController
    }
  }

  BlueButton {
    id: closeButton
    anchors {
      bottom: parent.bottom
      right: parent.right
    }
    onClicked: rootWindow.hide()
    text: qsTr("Close")
  }
}
