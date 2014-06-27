# Self Authentication

User authentication is what is referred to on the SAFE network as Self Authentication. This process does not involve any central server verifying a user’s credentials and is a truly decentralised operation.

A very high level explanation of the process involves a user’s session data stored on the network at a location identified by a `PIN` and `Keyword`. This data is encrypted with the user’s `Password`. All three of these credentials are meant to be private and **never disclosed to anyone**. This identity is referred to as a user’s `MAID (MaidSafe Anonymous ID)`.

When a user authenticates, his/her password is never transmitted as the network does not require it to retrieve the packet stored at this location. Thus the packet is retrieved via the user’s `PIN` and `Keyword` and then decrypted locally with the `Password` to get the user’s session. This session data then gives the user the details to allow access to their data in the network.

If a combination of `PIN` and `Keyword` refers to an already-used location in the network, we get a duplicate account error when trying to create a new account.

When a malicious user tries to log in and provides a fake `PIN` and `Keyword`, the network detects that location is currently not being used and instead of throwing an “account not found” exception, it actually returns a dummy encrypted session object which the malicious user can then waste time and effort trying to decrypt for nothing. The API project exposes the Login function as a single function rather than split them into two for the retrieval/decrypt of `MAID`. This is merely done to keep the API simple. If you however wish to not use the single function Login, you are free to do so by using the underlying submodules and ignoring the Login function from the API project.
