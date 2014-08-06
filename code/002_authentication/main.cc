#include <iostream>

#include "maidsafe.h"
#include "maidsafe/common/utils.h"

using namespace maidsafe;

int main(int /*argc*/, char* argv[]) {
  // Note: This snippet demonstrates how to create / login to an account on the SAFE network.
  //       Please verify the testnet is currently operational via
  //       http:://visualiser.maidsafe.net:8080/testnet-status before running this snippet.
  //       If you have a local network setup, Make sure bootstrap_override.dat file exists in the
  //       current folder of the executable before running this example.

  // Required for bootstrap handling
  SetThisExecutablePath(argv);

  /* Modify Pin/Keyword/Password variables to create a specific account */
  
  // Random Pin with a Minimum of 1000
  uint32_t pin(std::max(RandomUint32(), static_cast<uint32_t>(1000)));

  // Random keyword with 20 characters
  std::string keyword(RandomAlphaNumericString(20));

  // Random password with 25 characters
  std::string password(RandomAlphaNumericString(25));

  std::cout << "Creating account with:\n" <<
               "Pin: " << pin << '\n' <<
               "Keyword: " << keyword << '\n' <<
               "Password: " << password << "\n\n";
  {
    // Scope for Account creation

    try {
      std::cout << "Creating Account\n";
      std::future<std::unique_ptr<PrivateClient>> private_client_future{
          PrivateClient::CreateAccount(keyword, pin, password) };

      std::unique_ptr<PrivateClient> private_client{ private_client_future.get() };
      // Private Client is now created and ready for use
      std::cout << "Account created successfully\n";
      private_client->Logout();
      std::cout << "Logged out of Account\n\n";

    } catch (const maidsafe_error& error) {
      if (make_error_code(VaultErrors::account_already_exists) == error.code()) {
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
      std::future<std::unique_ptr<PrivateClient>> private_client_future{
          PrivateClient::Login(keyword, pin, password) };

      std::unique_ptr<PrivateClient> private_client{ private_client_future.get() };
      // Private Client is now ready for use
      std::cout << "Login completed successfully\n";
      private_client->Logout();
      std::cout << "Logged out of Account\n\n";
    } catch (const maidsafe_error& error) {
      if (make_error_code(VaultErrors::no_such_account) == error.code()) {
        std::cout << "Sorry, No such account exists on the network\n\n";
      } else {
        std::cout << "Error on Login :" << boost::diagnostic_information(error) << "\n\n";
      }
    }
  }

  return 0;
}
