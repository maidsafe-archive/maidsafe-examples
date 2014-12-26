import QtQuick 2.2
import SAFEdrive 1.0
import "../resources/styles"

CustomWindow {
  id: rootWindow

  contentSource: mainController.currentView === MainController.Login ?
                   "Login.qml"
                 :
                   mainController.currentView === MainController.CreateAccount ?
                     "CreateAccount.qml"
                   :
                     mainController.currentView === MainController.TestnetStatus ?
                       "TestnetStatus.qml"
                     :
                       "OpenDrive.qml"
}
