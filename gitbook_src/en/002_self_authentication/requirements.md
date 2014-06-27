# Requirements


### API Project Libraries & local_network_controller:


Please refer to the [Network Setup - Requirements](001_network_setup/requirements.md) to get your build environment setup for the MaidSafe Super-Project.

This example requires two targets to be built from the MaidSafe Super-Project.

* `maidsafe_api` - This will get the API project library built and ready to use from any external project
* `local_network_controller` - As seen in the Network Setup example, this target currently helps us run a local test network on a single machine we can use for examples to run on and function.


Make sure to have the `local_network_controller` up and running. You should leave it running with the following message displayed


<Image>



### [MaidSafe-Examples](https://github.com/maidsafe/maidsafe-examples) Source Code

Clone/Download the Github project to a preferred location on your machine. This project contains any code samples that the examples series will rely on in the `code` folder.

Now from somewhere outside the Examples project root we need to run:

    cmake -H<path to MaidSafe-Examples/code> -Bbuild_maidsafe_examples -DMAIDSAFE_BINARY_DIR=<path to maidsafe Super-Project build folder>

Go ahead and build the `authentication` target from the examples project.
