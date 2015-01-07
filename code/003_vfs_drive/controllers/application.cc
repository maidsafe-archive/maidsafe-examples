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

#include "controllers/application.h"

#include "controllers/main_controller.h"

namespace safedrive {

ExceptionEvent::ExceptionEvent(const QString& exception_message, Type type)
    : QEvent(type),
      exception_message_(exception_message) {}

QString ExceptionEvent::ExceptionMessage() {
  return exception_message_;
}

Application::Application(int& argc, char** argv)
    : QApplication(argc, argv),
      handler_object_(),
      shared_memory_() {}

bool Application::notify(QObject* receiver, QEvent* event) {
  try {
    return QApplication::notify(receiver, event);
  } catch(...) {
    if (handler_object_) {
      QApplication::instance()->postEvent(&(*handler_object_),
                                          new ExceptionEvent(tr("Unknown Exception")));
    } else {
      QApplication::quit();
    }
  }
  return false;
}

void Application::SetErrorHandler(boost::optional<MainController&> handler_object) {
  if (handler_object)
    handler_object_ = handler_object;
}

bool Application::IsUniqueInstance() {
  shared_memory_.setKey("SAFEdrive");
  return shared_memory_.create(1);
}

}  // namespace safedrive
