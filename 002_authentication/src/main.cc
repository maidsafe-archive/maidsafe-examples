#include <iostream>

#include "maidsafe/common/make_unique.h"
#include "maidsafe/common/menu.h"
#include "maidsafe/common/log.h"
#include "maidsafe/passport/passport.h"
#include "maidsafe/routing/bootstrap_file_operations.h"
#include "maidsafe/routing/parameters.h"
#include "maidsafe/client.h"
#include "maidsafe/anonymous_session.h"

void InputKeyword(std::string& keyword, maidsafe::CLI& cli) {
  keyword.clear(); keyword = cli.Get<std::string>("Enter Keyword");
}

void InputPin(uint32_t& pin, maidsafe::CLI& cli) {
  pin = 0; pin = cli.Get<uint32_t>("Enter Pin");
}

void InputPassword(std::string& password, maidsafe::CLI& cli) {
  password.clear(); password = cli.Get<std::string>("Enter Password");
}

void CreateAccount(const std::string& keyword, uint32_t pin, const std::string& password) {
  try {
    maidsafe::authentication::UserCredentials user_credentials;
    user_credentials.keyword =
      maidsafe::make_unique<maidsafe::authentication::UserCredentials::Keyword>(keyword);
    user_credentials.pin =
      maidsafe::make_unique<maidsafe::authentication::UserCredentials::Pin>(std::to_string(pin));
    user_credentials.password =
      maidsafe::make_unique<maidsafe::authentication::UserCredentials::Password>(password);
  
    maidsafe::routing::Parameters::append_local_live_port_endpoint = true;
    maidsafe::routing::BootstrapContacts bootstrap_contacts;

    auto maid_and_signer(maidsafe::passport::CreateMaidAndSigner());

    maidsafe::Client client(maid_and_signer, bootstrap_contacts);
    maidsafe::AnonymousSession session(maid_and_signer);
    maidsafe::SessionHandler<maidsafe::AnonymousSession>
      session_handler(std::move(session), client, std::move(user_credentials));
  }
  catch (std::exception& e) {
    LOG(kError) << "Error on Account Creation: " << boost::diagnostic_information(e);
  }
}

void Login(const std::string& keyword, uint32_t pin, const std::string& password) {
  try {
    maidsafe::authentication::UserCredentials user_credentials;
    user_credentials.keyword =
      maidsafe::make_unique<maidsafe::authentication::UserCredentials::Keyword>(keyword);
    user_credentials.pin =
      maidsafe::make_unique<maidsafe::authentication::UserCredentials::Pin>(std::to_string(pin));
    user_credentials.password =
      maidsafe::make_unique<maidsafe::authentication::UserCredentials::Password>(password);

    maidsafe::routing::Parameters::append_local_live_port_endpoint = true;
    maidsafe::routing::BootstrapContacts bootstrap_contacts;

    maidsafe::SessionHandler<maidsafe::AnonymousSession> session_handler(bootstrap_contacts);
    session_handler.Login(std::move(user_credentials));
    maidsafe::Client client(session_handler.session().passport->GetMaid(), bootstrap_contacts);
  }
  catch (std::exception& e) {
    LOG(kError) << "Error on Login: " << boost::diagnostic_information(e);
  }
}

int main(int argc, char* argv[]) {
  maidsafe::log::Logging::Instance().Initialise(argc, argv);

  std::string keyword, password;
  uint32_t pin(0);
  maidsafe::CLI cli;

  maidsafe::Menu menu("Authentication Menu");

  maidsafe::MenuItem* create_account(menu.AddItem("Create a New Account"));
    
  create_account->AddChildItem("Input a Keyword", [&]{ InputKeyword(keyword, cli); });
  create_account->AddChildItem("Input a Pin", [&]{ InputPin(pin, cli); });
  create_account->AddChildItem("Input a Password", [&]{ InputPassword(password, cli); });
  create_account->AddChildItem("Create Account", [&]{ CreateAccount(keyword, pin, password); });

  maidsafe::MenuItem* login(menu.AddItem("Login to Existing Account"));
    
  login->AddChildItem("Input a Keyword", [&]{ InputKeyword(keyword, cli); });
  login->AddChildItem("Input a Pin", [&]{ InputPin(pin, cli); });
  login->AddChildItem("Input a Password", [&]{ InputPassword(password, cli); });
  login->AddChildItem("Login", [&]{ Login(keyword, pin, password); });

  menu.Run();

  return 0;
}
