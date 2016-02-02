Hello World
===========

### What is it?

This is a minimal project for use as an example of a build/test configuration that might be suitable for more serious work.  It aims to separate the platform-dependent details of development, from the (hopefully) platform indepent source.

Scripts are in Bash because unix folk are likely to already have access to it, and because "git bash" is distributed with git--which means that windows users capable of cloning this repository might also have a Bash shell lying around.

CMake is used for build configuration.  CMakeLists.txt contains all of the parameters necessary to build the project.  It uses these to generate a build environment in ./build.  Your compiler/IDE of choice can then make whatever sort of mess it likes in that directory, and it's separated from the code.

CMakeLists.txt is configured to use Boost's unit testing framework, and a sample test has been written to indicate how it works.  Sqlite3 is used in that test so I can iron out linker kinks with libraries that CMake doesn't come preconfigured to find.

### How do I use it?

0. Make sure you have the [dependencies](dependency.md) installed.
1. Clone the repository
2. run `./configure.sh` with the appropriate flag (run without flags to see usage)
3. Navigate to `./build/` and begin developing

### What does it do?

`./build/bin/hello.exe` prints "hello world".

`./build/testBin/sampleDB` saves some text to a database, retrieves it, and checks to see that the right thing was saved.
