# Example

You can find the full source code for the following example of Self Authentication [in GitHub](https://github.com/maidsafe/maidsafe-examples/tree/master/code/002_authentication).

## General

The example predominantly makes use of the [`PrivateClient`](https://github.com/maidsafe/MaidSafe-API/blob/master/include/maidsafe/private_client.h) class.  This class allows users to access the network anonymously, hence the "Private" in the name of the class.

Internally, it opens and maintains connections to vaults in the network, so a single instance of the class should normally be maintained for the duration of a user's session.

For convenience, and to abstract the underlying mechanics of initiating a connection to the network, the class can only be constructed via one of two static factory functions: `Login`, or `CreateAccount`.  Both of these require the caller to pass a keyword, pin and password.

## Account Creation

To create a new anonymous account using MAID keys, you should call `PrivateClient::CreateAccount`:

    std::future<std::unique_ptr<PrivateClient>> private_client_future{
        PrivateClient::CreateAccount(keyword, pin, password) };

This returns a `std::future` to a `std::unique_ptr<PrivateClient>` to allow the relatively expensive account creation to run asynchronously.  You can subsequently `get()` the `PrivateClient`:

    std::unique_ptr<PrivateClient> private_client{ private_client_future.get() };

Since the `PrivateClient` is not default-constructible, it is useful to manage it in a `std::unique_ptr` so that such a pointer can be held as an external class member and set once the `PrivateClient` is constructed.  This isn't a requirement though; the `PrivateClient` class is move-constructible and move-assignable (but not copyable).

On failure to create a new account, a `std::exception` will be thrown when calling `private_client_future.get()`.  If no exception has been thrown, the returned `PrivateClient` is logged in and usable for storing and retrieving data on the network.

## Logging In

Once an account has been successfully created, further attempts to rejoin the network should be made via `PrivateClient::Login`:

    std::future<std::unique_ptr<PrivateClient>> private_client_future{
        PrivateClient::Login(keyword, pin, password) };

For the same reasons as `CreateAccount` this returns a `std::future` to a `std::unique_ptr<PrivateClient>` and should be treated the same way.

## Logging Out

Prior to destroying an instance of the class, `PrivateClient::Logout` should be called:

    private_client->Logout();

This causes the account to be updated and stored to the network.  After this, the `PrivateClient` is no longer connected to the network, and should be treated much like a moved-from object, i.e. it should either be reassigned-to or destructed.
