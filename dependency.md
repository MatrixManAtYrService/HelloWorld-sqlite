# Dependency

## Configuration management goes through [CMake](https://cmake.org/).

### Installation In Linux

I found the ubuntu repo version to be a bit old for my taste, so I installed it from source:

    cd
    wget https://cmake.org/files/v3.4/cmake-3.4.1-Linux-x86_64.sh
    sudo chmod +x cmake-3.4.1-Linux-x86_64.sh 
    sudo ./cmake-3.4.1-Linux-x86_64.sh --prefix=/usr/local
    # answer "y" if you accept the agreement
    # answer "n" because you want cmake in /usr/local/bin and not /usr/local/cmake-3.4.a-Linux-x86_64/bin

    # this command should output:
    # cmake version 3.4.1
    cmake --version # should give 

### Installation in Windows

Start here: [https://cmake.org/download/](https://cmake.org/download/) and follow the steps (opting to add cmake to your PATH).
The installer is pretty typical of windows installers.

http://sourceforge.net/projects/boost/files/boost-binaries/1.60.0/


## Unit testing uses [Boost](http://www.boost.org)

The following steps will compile the boost libraries.  Many of them can be included as a header file only, but certain ones (including the boost test module, which we're using) must be compiled.  It's possible to extract just the parts we need--in which case this compilation would be very short.  However, the use of boost libraries is fairly standard--it is probably best to just compile the whole thing so that you don't have to do this again next time you want to link to a new boost library.

### [Installation In Linux](http://www.boost.org/doc/libs/1_60_0/more/getting_started/unix-variants.html)

Conversations with a friend indicate that the boost test module underwent significant changes in version 1.59, and that those changes are relevant to his decision to use boost for unit testing.  As such, the ubuntu-repository version was not new enough.  If you don't care, feel free to update the version number in CMakeLists.txt and use the following command:

    sudo apt-get install libboost-test-dev

To install it from source and get a newer version:

    cd
    wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.bz2
    tar --bzip2 -xf boost_1_60_0.tar.bz2
    cd boost_1_60_0/
    ./bootstrap.sh --exec-prefix=/usr/local
    ./b2
    sudo ./b2 install

### [Installation In Windows](http://www.boost.org/doc/libs/1_60_0/more/getting_started/windows.html)


1. Have visual studio installed (be sure to select "Visual C++", it's not a default option)
2. Get the code from [http://www.boost.org/users/download/](http://www.boost.org/users/download/)
3. Extract it to *folder*
4. Open a VS Developer Command prompt (mine was called "Developer Command Prompt for VS2015")

    cd folder
    bootstrap.bat
    b2.exe install --link=shared -- prefix=C:/

The above prefix will put the libraries in C:\lib\boost_1_60_0\ Feel free to change this, but note that this path must also be included in the boost section of CMakeLists.txt so that CMake can find the libraries.


## Database Access uses [Sqlite3](http://sqlite.org)

The file `cmake/FindSQLite3.cmake` describes how to find the sqlite3 library for several standard installation paths.  If the library is installed to a standard location, cmake should find it.  CMakeLists.txt should be all set up for this.

If sqlite3 is not found in this way (the Windows case), it may have to be built separately.  The code is included in `include/sqlite3` and the steps should be similar to the Windows instructions below.

## Installation in Linux

    sudo apt-get install sqlite3 libsqlite3-dev

## [Installation in Windows](http://www.boost.org/doc/libs/1_60_0/more/getting_started/windows.html)

1. Have visual studio installed (be sure to select "Visual C++", it's not a default option)
2. Open a VS Developer Command prompt (mine was called "Developer Command Prompt for VS2015")
3. navigate to ./Geo/include/sqlite3 and run the following command:

    cl sqlite3.c -link -dll -out:..\..\lib\sqlite3.dll

This will build the sqlite3 dll and place it in lib/
