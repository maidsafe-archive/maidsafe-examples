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
  property Component currentComponent : warningPage

  content: Loader {
    id: loader
    anchors.fill: parent
    sourceComponent: currentComponent
  }

  property Component warningPage : Item {
    anchors.fill: parent

    Item {
      anchors {
        bottomMargin: warningNextButton.height
        fill: parent
      }

      HeaderLabel {
        id: licenseHeaderLabel
        anchors {
          top: parent.top
          topMargin: 20
        }
        color: DefaultBrushes.darkRed
        text: qsTr("Warning")
      }

      Label {
        id: warningLabel
        anchors {
          left: parent.left
          right: parent.right
          top: licenseHeaderLabel.bottom
          topMargin: 30
        }
        color: DefaultBrushes.labelGray
        font {
          family: "Arial"
          pixelSize: 14
        }
        horizontalAlignment: Qt.AlignHCenter
        onLinkActivated: Qt.openUrlExternally(link)
        text: qsTr("This is a DEMO application and should<br>be used for testing purposes only.<br>All data stored in your SAFEdrive<br><b>will be deleted</b> at some point<br>during this test period.")
        wrapMode: TextEdit.WordWrap
      }

      CustomCheckBox {
        id: warningCheckBox
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: warningLabel.bottom
          topMargin: 30
        }
        text: qsTr("I understand the Warning")
      }
    }
    BlueButton {
      id: warningNextButton
      anchors {
        bottom: parent.bottom
        right: parent.right
      }
      enabled: warningCheckBox.checked
      onClicked: currentComponent = loginPage
      text: qsTr("Next")
    }
  }

  property Component loginPage : Item {
      id: rootItem
      anchors.fill: parent

      Item {
        anchors {
          bottomMargin: loginButton.height
          fill: parent
        }
        HeaderLabel {
          id: loginHeaderLabel
          anchors {
            top: parent.top
            topMargin: 20
          }
          text: qsTr("Log in")
        }
        CustomTextField {
          id: pinBox
          anchors {
            horizontalCenter: parent.horizontalCenter
            top: loginHeaderLabel.bottom
            topMargin: 30
          }
          echoMode: TextInput.Password
          Keys.onEnterPressed: loginButton.clicked()
          Keys.onReturnPressed: loginButton.clicked()
          onTextChanged: statusBar.clearStatusInfo()
          placeholderText: qsTr("PIN")
        }
        CustomTextField {
          id: keywordBox
          anchors {
            horizontalCenter: parent.horizontalCenter
            top: pinBox.bottom
            topMargin: 10
          }
          echoMode: TextInput.Password
          Keys.onEnterPressed: loginButton.clicked()
          Keys.onReturnPressed: loginButton.clicked()
          onTextChanged: statusBar.clearStatusInfo()
          placeholderText: qsTr("Keyword")
        }
        CustomTextField {
          id: passwordBox
          anchors {
            horizontalCenter: parent.horizontalCenter
            top: keywordBox.bottom
            topMargin: 10
          }
          echoMode: TextInput.Password
          Keys.onEnterPressed: loginButton.clicked()
          Keys.onReturnPressed: loginButton.clicked()
          onTextChanged: statusBar.clearStatusInfo()
          placeholderText: qsTr("Password")
        }
        StatusBar  {
          id: statusBar
          anchors {
            horizontalCenter: parent.horizontalCenter
            top: passwordBox.bottom
            topMargin: 30
          }
          Connections {
            onCreateAccountErrorRaised: {
              statusBar.showErrorStatus(errorMessage)
              rootItem.enabled = true
            }
            target: apiModel
          }
        }
      }
      BlueButton {
        id: loginButton
        anchors {
          bottom: parent.bottom
          right: parent.right
        }
        onClicked: {
          rootItem.enabled = false
          statusBar.showProgressStatus()
          mainController.login(pinBox.text, keywordBox.text, passwordBox.text)
        }
        text: qsTr("Login")
      }
      TextButton {
        id: createAccountButton
        anchors {
          bottom: parent.bottom
          left: parent.left
        }
        onClicked: mainController.showCreateAccountView()
        text: qsTr("Create Account")
      }
    }
}
