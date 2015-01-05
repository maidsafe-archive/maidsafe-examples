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

#include <iostream>

#include "maidsafe.h"
#include "maidsafe/common/utils.h"

namespace ms = maidsafe;

int main(int /*argc*/, char* argv[]) {
  // Note: This snippet demonstrates how to create / login to an account on the SAFE network.
  //       Please verify the testnet is currently operational via
  //       http:://visualiser.maidsafe.net:8080/testnet-status before running this snippet.
  //       If you have a local network setup, Make sure bootstrap_override.dat file exists in the
  //       current folder of the executable before running this example.

  // Required for bootstrap handling
  ms::SetThisExecutablePath(argv);

  /* Modify Pin/Keyword/Password variables to create a specific account */

  // Random Pin with a Minimum of 1000
  uint32_t pin(std::max(ms::RandomUint32(), static_cast<uint32_t>(1000)));

  // Random keyword with 20 characters
  std::string keyword(ms::RandomAlphaNumericString(20));

  // Random password with 25 characters
  std::string password(ms::RandomAlphaNumericString(25));

  std::cout << "Creating account with:\n" <<
               "Pin: " << pin << '\n' <<
               "Keyword: " << keyword << '\n' <<
               "Password: " << password << "\n\n";
  {
    // Scope for Account creation

    try {
      std::cout << "Creating Account\n";
      std::future<std::unique_ptr<ms::PrivateClient>> private_client_future{
          ms::PrivateClient::CreateAccount(keyword, pin, password) };

      std::unique_ptr<ms::PrivateClient> private_client{ private_client_future.get() };
      // Private Client is now created and ready for use
      std::cout << "Account created successfully\n";
      private_client->Logout();
      std::cout << "Logged out of Account\n\n";
    } catch (const ms::maidsafe_error& error) {
      if (ms::make_error_code(ms::VaultErrors::data_already_exists) == error.code()) {
        std::cout << "Sorry, Account with given credentials already exist\n\n";
      } else {
        std::cout << "Error on Create Account :" << boost::diagnostic_information(error) << "\n\n";
      }
    }
  }

  {
    // Scope for Login

    try {
      std::cout << "Logging into Account\n";
      std::future<std::unique_ptr<ms::PrivateClient>> private_client_future{
          ms::PrivateClient::Login(keyword, pin, password) };

      std::unique_ptr<ms::PrivateClient> private_client{ private_client_future.get() };
      // Private Client is now ready for use
      std::cout << "Login completed successfully\n";
      private_client->Logout();
      std::cout << "Logged out of Account\n\n";
    } catch (const ms::maidsafe_error& error) {
      if (ms::make_error_code(ms::VaultErrors::no_such_account) == error.code()) {
        std::cout << "Sorry, No such account exists on the network\n\n";
      } else {
        std::cout << "Error on Login :" << boost::diagnostic_information(error) << "\n\n";
      }
    }
  }

  return 0;
}
