# Local Network Setup

So now that you have the build environment setup on your machine, the target we require for this example is 'local_network_controller'. This serves as a client to connect to the vault manager and start the network with a bunch of vaults which we can then connect to in future examples.

* Go ahead and build the target 'local_network_controller'
* Run the tool and you should see something like:

![Local Network Controller - Start Screen](./img/start_screen.PNG)

For this example we are going to go with option "1". Hit "1" and Enter. This lets us start a new network on this machine.

You can provide custom settings where applicable for the various options in the tool such as "Path to vault Executable" or "Number or Vaults to run the network with". Following the default options you should see the tool function such as

![Local Network Controller - Vault Manager Root Path](./img/vault_manager_root.PNG)

![Local Network Controller - Vault App Path](./img/vault_executable.PNG)

![Local Network Controller - Listening port](./img/listening_port.PNG)

![Local Network Controller - Vault Count](./img/vaults_count.PNG)


Now with the default option for "Vault count" the tool sets up a network with 12 Vaults (**This process may take a few minutes**). There are 2 extra vaults (zero state nodes) that are created as part of this process which get destroyed during the bootstrap phase.*(Explain the process here)*.


Provided everything runs fine, you should now see something like:

![Local Network Controller - Network Started](./img/network_started.PNG)


As the message in the screenshot explains, we need to keep this tool running to keep the test network going on this machine. That brings us to the end of "Example 0". If you're reading this, we hope you've got a test net running on your machine, so gratz!!



