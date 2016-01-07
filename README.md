Hello World
===========

### What is it?

This is a minimal project for use as an example of a build/test configuration that might be suitable for more serious work.  It aims to separate the platform-dependent details of development, from the (hopefully) platform indepent source.

Scripts are in Bash because unix folk are likely to already have access to it, and because "git bash" is distributed with git--which means that windows users capable of cloning this repository might also have a Bash shell lying around.

CMake is used for build configuration.  CMakeLists.txt contains all of the parameters necessary to build the project.  It uses these to generate a build environment in ./build.  Your compiler of choice can then make whatever sort of mess it likes in that directory, and it's separated from the code.

CMakeLists.txt is configured to use Boost's unit testing framework, and some sample tests have been written to indicate how it works

### How do I use it?

#### General

1. Make sure you have the [dependencies](dependency.md) installed.  
2. Clone the repository
5. run `configure.sh` which will give you some options
6. run `configure.sh <flag> to indicate your environment of choice, this will create a build environment for you in the ./build folder
7. `cd build`

#### Specific

From this point how to proceed will depend on which environment you instructed CMake to build.  If you used the `-g` flag (for Gnu Make) then...

* `make` will put the main executable in ./build/bin
* `make test` will put the test executables in /build/testBin and run them.

Current bug:  test 2 fails when run via `make test`, but it passes when run directly via ./testBin/error_helloPrinter and I'm not sure why

