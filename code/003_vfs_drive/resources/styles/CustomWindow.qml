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
import "../js/brushes.js" as DefaultBrushes
import "../js/properties.js" as DefaultProperties

ApplicationWindow {
  // Content Property for the Window
  property Component content: null

  color: "white"
  height: DefaultProperties.normalWindowHeight
  maximumHeight: DefaultProperties.normalWindowHeight

  maximumWidth: DefaultProperties.normalWindowWidth
  minimumHeight: DefaultProperties.normalWindowHeight
  minimumWidth: DefaultProperties.normalWindowWidth
  title: "SAFEdrive"
  width: DefaultProperties.normalWindowWidth

  Item {
    id: rootItem
    anchors.fill: parent

    Image {
      id: headerImage
      anchors {
        horizontalCenter: parent.horizontalCenter
        top: parent.top
      }
      fillMode: Image.PreserveAspectFit
      source: "qrc:/resources/images/app_header.svg"
    }

    Loader {
      id: contentLoader
      anchors {
        bottom: parent.bottom
        left: parent.left
        margins: 30
        right: parent.right
        top: headerImage.bottom
        topMargin: 0
      }
      sourceComponent: content
    }
  }
}
