# Self-authentication

User authentication is what is referred to on the SAFE network as Self Authentication. This process does not involve any central server verifying a user’s credential and is truly decentralised in the mode it operates.

A very high level explanation of the process involves a user’s session data stored on the network at a location identified by a “PIN” and “Keyword”. This data is encrypted with the user’s “Password”. All three of these credentials are meant to be private and never disclosed to anyone. This identify is referred to as a user’s MAID(MaidSafe Anonymous ID).

When a user logs into the network his password is never transmitted as the network does not require it to fetch the packet stored at this location. Thus the packet is retrieved via the user’s PIN and Keyword and then decrypted locally with the password to get the user’s session. This session data then gives the user the details to all his data in the network.

Address space in the network is unique so if a combination of PIN and Keyword refers to an already used location in the network. We get a duplicate account error when trying to create a new account.

When a malicious user tries to login and provides a fake PIN and Keyword, the network detects that location is currently not being used and instead of throwing a account not found exception, it actually returns a dummy encrypted session object which the malicious user can then waste his time trying to decrypt for nothing. API project exposes the Login function as a single function than split them into two for the retrieval/decrypt of MAID. This is merely done to keep the API simple. If you however wish to not use the single function Login, you are free to do so by using the underlying submodules and ignoring the login function from the API.

So with that out of the way, let’s see how we can create an account and login to the SAFE network via the API project. Assuming you followed the requirements section for this example, you should have your build environment setup for the examples project.
Make sure to have the local_network_controller up and running. You should leave it running with the following message displayed

<Image>

Go ahead and build the “authentication” target from the examples project. Running this target will show you the process of Authentication, however we’ll jump into some key parts of the code from the main.cc file


