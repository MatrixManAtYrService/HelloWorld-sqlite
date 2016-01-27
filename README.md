Hello World
===========

### What is it?

This is a minimal project for use as an example of a build/test configuration that might be suitable for more serious work.  It aims to separate the platform-dependent details of development, from the (hopefully) platform indepent source.

Scripts are in Bash because unix folk are likely to already have access to it, and because "git bash" is distributed with git--which means that windows users capable of cloning this repository might also have a Bash shell lying around.

CMake is used for build configuration.  CMakeLists.txt contains all of the parameters necessary to build the project.  It uses these to generate a build environment in ./build.  Your compiler of choice can then make whatever sort of mess it likes in that directory, and it's separated from the code.

CMakeLists.txt is configured to use Boost's unit testing framework, and a sample test has been written to indicate how it works.  Sqlite3 is used in that test so I can iron out linker kinks with libraries that CMake doesn't find automatically.

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

### Does it work?

Kind of.

#### Here's what I've tested and found to work:

* Linux
  * `./configure.sh -g` populates `./build/` with the proper files
  * `make` builds everything without trouble
  * The main program runs correctly
  * The unit test passes
* Windows
  * `./configure.sh -v` populates `./build/` with the proper files
  * visual studio builds everything without trouble (though we do have a few linker warnings)
  * The main program runs correctly


#### Here's what I'm currently struggling with:

 * running `make test` fails, even though running `make` and then executing the test individually succeeds
 * The resulting Visual Studio configuration wants `sqlite3.lib` to be in `build/` despite that CMake successfully finds the file in /lib

