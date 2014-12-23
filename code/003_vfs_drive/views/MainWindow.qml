import QtQuick 2.2
import SAFEdrive 1.0
import "../resources/styles"

CustomWindow {
  contentSource: mainController.currentView === Controller.Login ?
                   "Login.qml"
                 :
                   mainController.currentView === Controller.CreateAccount ?
                     "CreateAccount.qml"
                   :
                     mainController.currentView === Controller.TestnetStatus ?
                       "TestnetStatus.qml"
                     :
                       "OpenDrive.qml"
}
