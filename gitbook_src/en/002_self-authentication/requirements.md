# Requirements


- API Project Libs & local_network_controller:

Please refer to the [Network Setup - Requirements](001_network_setup/requirements.md) to get your build environment setup for the MaidSafe super project.

This example requires two targets to be built from the MaidSafe Super project.

* “maidsafe_api” - This will get the API project libs built and ready to use from any external project
* “local_network_controller” - As seen in the Network Setup example, this target currently helps us run a local test network on a single machine we can use for examples to run on and function.



- Clone/Download the [MaidSafe-Examples](https://github.com/maidsafe/maidsafe-examples) github project to a preferred location on your machine. This project contains any code samples that the examples series will rely on.

Now from somewhere outside the Examples project root we need to run:

    cmake -H<path to MaidSafe-Examples/code> -Bbuild_maidsafe_examples -DMAIDSAFE_BINARY_DIR=<path to maidsafe super project build folder>
