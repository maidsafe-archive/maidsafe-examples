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
    property string chosenPin
    property string chosenKeyword

    id: rootItem
    anchors.fill: parent

    HeaderLabel {
      id: headerLabel
      anchors {
        top: parent.top
        topMargin: 20
      }
      text: qsTr("Create Account")
    }

    Item {
      property int selectedIndex : 0

      id: tabBar
      anchors {
        top: headerLabel.bottom
        topMargin: 15
        horizontalCenter: parent.horizontalCenter
      }
      implicitWidth: pinItem.implicitWidth + keywordItem.implicitWidth +  passwordItem.implicitWidth
      implicitHeight: Math.max(pinItem.contentHeight, keywordItem.contentHeight, passwordItem.contentHeight)
      TabItem {
        id: pinItem
        anchors {
          left: tabBar.left
          leftMargin: pinItem.horizontalMargin // WORKAROUND: Ignore's implicit component margin on Win-8
        }
        index: 0
        isSelected: tabBar.selectedIndex == pinItem.index
        onClicked: tabBar.selectedIndex = pinItem.index
        text: qsTr("PIN")
      }

      TabItem {
        id: keywordItem
        anchors.left: pinItem.right
        index: 1
        isSelected: tabBar.selectedIndex == keywordItem.index
        onClicked: tabBar.selectedIndex = keywordItem.index
        text: qsTr("Keyword")
      }

      TabItem {
        id: passwordItem
        anchors.left: keywordItem.right
        index: 2
        isSelected: tabBar.selectedIndex == passwordItem.index
        onClicked: tabBar.selectedIndex = passwordItem.index
        text: qsTr("Password")
      }
    }

    Loader {
      id: loader
      anchors {
        bottom: rootItem.bottom
        left: rootItem.left
        right: rootItem.right
        top: tabBar.bottom
        topMargin: 35
      }

      sourceComponent: {
        if (tabBar.selectedIndex == 0) {
          pinPage
        } else if (tabBar.selectedIndex == 1) {
          keywordPage
        } else {
          passwordPage
        }
      }
    }

    property Component pinPage : Item {
      anchors.fill: parent

      CustomTextField {
        id: pinBox
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: parent.top
        }
        echoMode: TextInput.Password
        Keys.onEnterPressed: pinNextButton.clicked()
        Keys.onReturnPressed: pinNextButton.clicked()
        onTextChanged: pinStatusBar.clearStatusInfo()
        placeholderText: qsTr("Choose a numeric PIN")
      }
      CustomTextField {
        id: confirmPinBox
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: pinBox.bottom
          topMargin: 15
        }
        echoMode: TextInput.Password
        Keys.onEnterPressed: pinNextButton.clicked()
        Keys.onReturnPressed: pinNextButton.clicked()
        onTextChanged: pinStatusBar.clearStatusInfo()
        placeholderText: qsTr("Confirm PIN choice")
      }
      StatusBar  {
        id: pinStatusBar
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: confirmPinBox.bottom
          topMargin: 15
        }
      }
      BlueButton {
        id: pinNextButton
        anchors {
          bottom: parent.bottom
          right: parent.right
        }
        onClicked: {
          rootItem.chosenPin = ""
          if (pinBox.text.trim() == "") {
            pinStatusBar.showErrorStatus("PIN cannot be empty")
          } else if (pinBox.text != confirmPinBox.text) {
            pinStatusBar.showErrorStatus("Entries do not match")
          } else if (isNaN(parseInt(pinBox.text, 10))) {
            pinStatusBar.showErrorStatus("PIN needs to be numeric")
          } else {
            rootItem.chosenPin = pinBox.text
            tabBar.selectedIndex = 1
          }
        }
        text: qsTr("Next")
      }
      TextButton {
        id: loginButton
        anchors {
          bottom: parent.bottom
          left: parent.left
        }
        onClicked: mainController.showLoginView()
        text: qsTr("Log in")
      }
    }

    property Component keywordPage : Item {
      anchors.fill: parent

      CustomTextField {
        id: keywordBox
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: parent.top
        }
        echoMode: TextInput.Password
        Keys.onEnterPressed: keywordNextButton.clicked()
        Keys.onReturnPressed: keywordNextButton.clicked()
        onTextChanged: keywordStatusBar.clearStatusInfo()
        placeholderText: qsTr("Choose a Keyword")
      }
      CustomTextField {
        id: confirmKeywordBox
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: keywordBox.bottom
          topMargin: 15
        }
        echoMode: TextInput.Password
        Keys.onEnterPressed: keywordNextButton.clicked()
        Keys.onReturnPressed: keywordNextButton.clicked()
        onTextChanged: keywordStatusBar.clearStatusInfo()
        placeholderText: qsTr("Confirm Keyword choice")
      }
      StatusBar  {
        id: keywordStatusBar
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: confirmKeywordBox.bottom
          topMargin: 15
        }
      }
      BlueButton {
        id: keywordNextButton
        anchors {
          bottom: parent.bottom
          right: parent.right
        }
        onClicked: {
          rootItem.chosenKeyword = ""
          if (keywordBox.text.trim() == "") {
            keywordStatusBar.showErrorStatus("Keyword cannot be empty")
          } else if (keywordBox.text != confirmKeywordBox.text) {
            keywordStatusBar.showErrorStatus("Entries do not match")
          } else {
            rootItem.chosenKeyword = keywordBox.text
            tabBar.selectedIndex = 2
          }
        }
        text: qsTr("Next")
      }
    }

    property Component passwordPage : Item {
      anchors.fill: parent

      CustomTextField {
        id: passwordBox
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: parent.top
        }
        echoMode: TextInput.Password
        Keys.onEnterPressed: createAccountButton.clicked()
        Keys.onReturnPressed: createAccountButton.clicked()
        onTextChanged: statusBar.clearStatusInfo()
        placeholderText: qsTr("Choose a Password")
      }
      CustomTextField {
        id: confirmPasswordBox
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: passwordBox.bottom
          topMargin: 15
        }
        echoMode: TextInput.Password
        Keys.onEnterPressed: createAccountButton.clicked()
        Keys.onReturnPressed: createAccountButton.clicked()
        onTextChanged: statusBar.clearStatusInfo()
        placeholderText: qsTr("Confirm Password choice")
      }
      StatusBar  {
        id: statusBar
        anchors {
          horizontalCenter: parent.horizontalCenter
          top: confirmPasswordBox.bottom
          topMargin: 15
        }
        Connections {
          onCreateAccountErrorRaised: {
            statusBar.showErrorStatus(errorMessage)
            rootItem.enabled = true
          }
          target: apiModel
        }
      }
      BlueButton {
        id: createAccountButton
        anchors {
          bottom: parent.bottom
          right: parent.right
        }
        onClicked: {
          if (passwordBox.text.trim() == "") {
            statusBar.showErrorStatus("Password cannot be empty")
          } else if (passwordBox.text != confirmPasswordBox.text) {
            statusBar.showErrorStatus("Entries do not match")
          } else {
            rootItem.enabled = false
            statusBar.showProgressStatus()
            mainController.createAccount(rootItem.chosenPin, rootItem.chosenKeyword, passwordBox.text)
          }
        }
        text: qsTr("Create")
      }
    }
  }
}


