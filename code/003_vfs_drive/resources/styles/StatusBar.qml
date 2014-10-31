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
import QtQuick.Layouts 1.0
import "../js/brushes.js" as DefaultBrushes

Item {
  implicitHeight: Math.max(errorStatus.implicitHeight, progressStatus.implicitHeight)
  implicitWidth: Math.max(errorStatus.implicitWidth, progressStatus.implicitWidth)

  Item {
    id: errorStatus
    anchors.centerIn: parent
    implicitHeight: Math.max(errorIndicator.implicitHeight, errorLabel.contentHeight)
    implicitWidth: errorIndicator.implicitWidth + errorLabel.contentWidth + errorLabel.anchors.leftMargin
    visible: false

    Rectangle {
      id: errorIndicator
      color: DefaultBrushes.normalRed
      implicitHeight: 18
      implicitWidth: 18
      radius: errorIndicator.implicitWidth / 2
      Image {
        anchors.centerIn: parent
        source: "qrc:/resources/icons/status_error_glyph.svg"
      }
    }

    Label {
      id: errorLabel
      anchors {
        left: errorIndicator.right
        leftMargin: 5
      }
      color: DefaultBrushes.normalRed
      font {
        family: "Arial"
        pixelSize: 13
      }
      horizontalAlignment: Qt.AlignLeft
    }
  }

  Item {
    property int indicatorRadius: 3
    property bool isAnimationRunning : false

    id: progressStatus
    anchors.centerIn: parent
    implicitHeight: 10
    implicitWidth: progressStatus.indicatorRadius * 15
    visible: false

    RowLayout {
      anchors.centerIn: parent
      spacing: progressStatus.indicatorRadius

      Rectangle {
        id: indicatorOne
        color: DefaultBrushes.normalBlue
        height: progressStatus.indicatorRadius * 2
        opacity: 0.5
        radius: progressStatus.indicatorRadius
        width: progressStatus.indicatorRadius * 2
      }
      Rectangle {
        id: indicatorTwo
        color: DefaultBrushes.normalBlue
        height: progressStatus.indicatorRadius * 2
        opacity: 0.5
        radius: progressStatus.indicatorRadius
        width: progressStatus.indicatorRadius * 2
      }
      Rectangle {
        id: indicatorThree
        color: DefaultBrushes.normalBlue
        height: progressStatus.indicatorRadius * 2
        opacity: 0.5
        radius: progressStatus.indicatorRadius
        width: progressStatus.indicatorRadius * 2
      }
      Rectangle {
        id: indicatorFour
        color: DefaultBrushes.normalBlue
        height: progressStatus.indicatorRadius * 2
        opacity: 0.5
        radius: progressStatus.indicatorRadius
        width: progressStatus.indicatorRadius * 2
      }
      Rectangle {
        id: indicatorFive
        color: DefaultBrushes.normalBlue
        height: progressStatus.indicatorRadius * 2
        opacity: 0.5
        radius: progressStatus.indicatorRadius
        width: progressStatus.indicatorRadius * 2
      }
      SequentialAnimation {
        loops: Animation.Infinite
        running: progressStatus.isAnimationRunning

        ParallelAnimation {
          NumberAnimation { target: indicatorTwo; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorOne; property: "opacity"; to: 1; duration: 100 }
        }
        ParallelAnimation {
          NumberAnimation { target: indicatorOne; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorTwo; property: "opacity"; to: 1.0; duration: 100 }
        }
        ParallelAnimation {
          NumberAnimation { target: indicatorTwo; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorThree; property: "opacity"; to: 1.0; duration: 100 }
        }
        ParallelAnimation {
          NumberAnimation { target: indicatorThree; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorFour; property: "opacity"; to: 1.0; duration: 100 }
        }
        ParallelAnimation {
          NumberAnimation { target: indicatorFour; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorFive; property: "opacity"; to: 1.0; duration: 100 }
        }
        ParallelAnimation {
          NumberAnimation { target: indicatorFive; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorFour; property: "opacity"; to: 1.0; duration: 100 }
        }
        ParallelAnimation {
          NumberAnimation { target: indicatorFour; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorThree; property: "opacity"; to: 1.0; duration: 100 }
        }
        ParallelAnimation {
          NumberAnimation { target: indicatorThree; property: "opacity"; to: 0.5; duration: 100 }
          NumberAnimation { target: indicatorTwo; property: "opacity"; to: 1.0; duration: 100 }
        }
      }
    }
  }

  function showErrorStatus(errorMessage) {
    clearStatusInfo()
    errorLabel.text = errorMessage
    errorStatus.visible = true
  }

  function showProgressStatus(indicatorRadius) {
    progressStatus.indicatorRadius = indicatorRadius ? indicatorRadius : 3;
    clearStatusInfo()
    progressStatus.isAnimationRunning = true;
    progressStatus.visible = true
  }

  function clearStatusInfo() {
    progressStatus.isAnimationRunning = false;
    progressStatus.visible = false
    errorLabel.text = ""
    errorStatus.visible = false
  }

  function isInProgressStatus() {
    return progressStatus.isAnimationRunning
  }
}
