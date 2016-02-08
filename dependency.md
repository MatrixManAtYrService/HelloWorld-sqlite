# Dependency

## Configuration management goes through [CMake](https://cmake.org/).

CMake puts platform-specific things in `./build/` so that developers can do whatever they want in that directory.  This keeps the source platform-independent.

### Installation In Linux

The following command will install cmake:

    sudo apt-get install cmake

I found the ubuntu repo version to be a bit old for my taste, so I installed the version from cmake.org instead:

    wget https://cmake.org/files/v3.4/cmake-3.4.1-Linux-x86_64.sh
    sudo chmod +x cmake-3.4.1-Linux-x86_64.sh 
    sudo ./cmake-3.4.1-Linux-x86_64.sh --prefix=/usr/local
    # answer "y" if you accept the agreement
    # answer "n" because you want cmake in /usr/local/bin and not /usr/local/cmake-3.4.a-Linux-x86_64/bin

    cmake --version
    # should output:  cmake version 3.4.1

### Installation in Windows

Start here: [https://cmake.org/download/](https://cmake.org/download/) and follow the steps (opting to add cmake to your PATH).
The installer is pretty typical of windows installers.


## Unit testing uses [Boost](http://www.boost.org)

The following steps will compile the boost libraries.  Many of them can be included as a header file only, but certain ones (including the boost test module, which we're using) must be compiled.  It's possible to extract just the parts we need--in which case this compilation would be very short.  However, the use of boost libraries is fairly standard--it is probably best to just compile the whole thing so that you don't have to do this again next time you want to link to a new boost library.

### [Installation In Linux](http://www.boost.org/doc/libs/1_60_0/more/getting_started/unix-variants.html)

Conversations with a friend indicate that the boost test module underwent significant changes in version 1.59, and that those changes are relevant to his decision to use boost for unit testing.  As such, the ubuntu-repository version was not new enough for me.  If you don't care, feel free to update the version number in CMakeLists.txt and use the following command:

    sudo apt-get install libboost-test-dev

To install it from source (which gives you control of the version you're installing) use the following instructions instead:

I found that installing `python-dev`and `libbz2-dev` populated some headers that certain boost libraries needed to build.  These libraries may not be strictly necessary for your application, so if you're ok with an incomplete build, you may skip the first command

    sudo apt-get install g++ bzip2 python-dev libbz2-dev
    wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.bz2
    tar --bzip2 -xf boost_1_60_0.tar.bz2
    cd boost_1_60_0
    ./bootstrap.sh --exec-prefix=/usr/local
    cd ..

Note that the `-j#` flag indicates how many proccessor cores to use for compilation (which can take a while).  If you have two cores, use `-j2`.
    
    ./b2 -j#
    sudo ./b2 install

### [Installation In Windows](http://www.boost.org/doc/libs/1_60_0/more/getting_started/windows.html)

1. Have visual studio installed (be sure to select "Visual C++", it's not a default option)
2. Open a VS Developer Command prompt (mine was called "Developer Command Prompt for VS2015")
3. Download and extract the boost source (it is available [here](http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.zip/download))
4. navigate to the `boost_1_60_0 folder` and run the following commands.  Note that the `-j#` flag below indicates how many proccessor cores to use for compilation (which can take a while).  If you have two cores, use `-j2`.
    
        bootstrap.bat
        b2 toolset=msvc-14.0 --build-type=complete --abbreviate-paths architecture=x86 address-model=32 variant=release,debug threading=multi link=shared runtime-link=shared install -j#

5. Go into Control Panel / System / Advanced System Settings / Environment Variables and append `;C:\Boost\lib\` to your path.

6. Install the visual studio Boost Unit Test Adapter [Unit Test Adapter](https://visualstudiogallery.msdn.microsoft.com/5f4ae1bd-b769-410e-8238-fb30beda987f).

7. After building the main solution (helloWorld.sln) navigate to Test -> Windows -> Test Explorer to see your currently configured tests

## Database Access uses [Sqlite3](http://sqlite.org)

Sqlite is a lightweight database manager.  It stores the entirety of the database in a file, which simplifies things considerably compared to DBMS's that run as a service and require things like logins.

### Installation in Linux
Run the following command:

    sudo apt-get install sqlite3 libsqlite3-dev

The file `cmake/FindSQLite3.cmake` describes how to find the sqlite3 library for several standard installation paths.  If the library is installed to a standard location, cmake should find it.  CMakeLists.txt should be all set up for this.

### Installation in Windows

#### The c++ api

The Sqlite3 library is distributed under windows as two files, sqlite3.dll and a sqlite3.def  These files, along with a script to generate them, are in `./tools/buildSqlite3`

When `./configure.sh` is run with `-v`, this script is run, and the necessary files are generated and put in ./lib/ (if they aren't already there).  No action *should* be needed, as long as you have Visual Studio installed.

Rather than adjusting your path for this project specifically, configure.sh places sqlite3.dll in ./build/testBin/Debug so that it can be found when the test that depends on it gets run.  This means you must sprinkle this file into the working directory any time that an executable that needs it is run.

If you'd prefer to avoid this, you can instead adjust your PATH to point at the dll instead.

#### The sqlite3 user interface

If you would like to use the sqlite3 CLI interface to interact with the database files that sqlite3 creates, it can be found in the sqlite-tools package on [sqlite.org](http://www.sqlite.org/download.html).
