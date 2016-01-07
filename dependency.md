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

I did not take notes while doing this, will do so next time.  I don't remember the process, so it probably proceeded without suprise.

Start here: https://cmake.org/download/


## Unit testing uses [Boost](http://www.boost.org)

### [Installation In Linux](http://www.boost.org/doc/libs/1_60_0/more/getting_started/unix-variants.html)

Conversations with a friend indicate that the boost test module underwent significant changes in version 1.59, and that those changes are relevant to his decision to use boost for unit testing.  As such, the ubuntu-repository version was not new enough.  If you don't care, feel free to update the version number in CMakeLists.txt and use the following command:

    sudo apt-get install libboost-test-dev

To install it from source and get a newer version:

    cd
    wget http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.bz2
    tar --bzip2 -xf boost_1_60_0.tar.bz2
    cd boost_1_60_0/
    ./bootstrap.sh
    ./bootstrap.sh --exec-prefix=/usr/local
    ./b2
    sudo ./b2 install

### [Installation In Windows](http://www.boost.org/doc/libs/1_60_0/more/getting_started/windows.html)

I got this working by using `msvc`, the Microsoft compiler (which I had installed anyway).  Will add installation notes here next time I do this.
sudo apt-get install libsqlite3-dev
