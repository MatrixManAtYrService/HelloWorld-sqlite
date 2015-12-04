#!/usr/bin/env bash

# create build directory if it doesn't exist
mkdir -p build && 
cd build && 

# put a .gitignore file there so user-specific files don't get checked in accidentally
echo "*" > .gitignore && 
echo "!.gitignore" >> .gitignore && 

# If you'd like to make persistent, configuration-specific, changes, consider putting those files in a new repository and then adding it as a subrepo.  That way, carting around environment-specific files is optional. Feel free to do this for convenience, but keep in mind that mission-critical changes should go through CMakeLists.txt so that we don't break platform-independence.

# -m (vanilla configuration, Makefile only)
if [[ $1 == -*[mM]* ]] ; then
    # The IDE's specify the build type internally, but it would seem that Make wants it explicitly
    cmake .. -DCMAKE_BUILD_TYPE=Debug

# -v (Visual Studio 2015)
elif [[ $1 == -*[vV]* ]] ; then
    echo "configuring ./build/ for Visual Studio"
    cmake .. -G "Visual Studio 14 2015 Win64"

# -b (Borland)
elif [[ $1 == -*[bB]* ]] ; then
    echo "configuring ./build/ for Borland"
    cmake .. -G "Borland Makefiles"

# -e (Eclipse)
elif [[ $1 == -*[eE]* ]] ; then
    echo "configuring ./build/ for Eclipse"
    cmake .. -G "Eclipse CDT4 - Unix Makefiles"

# anything else
else
    echo "Generates a build configuration using CMake and puts it in ./build"
    echo "These project files are generated--so changes to them might get clobbered."
    echo ""
    echo "If you need to make a persistent change, consider modifying CMakeLists.txt"
    echo "That way, your change will propagate into everybody's configuration--not just yours."
    echo ""
    echo "Usage: configure [OPTION]"
    echo ""
    echo  "<none>                   Display this message"
    echo  "-m                       CRun cmake with no flags, puts Makefile in ./build"
    echo  "-v                       Configure build directory for Visual Studio 2015 (Win64)"
    echo  "-b                       Configure build directory for Borland" 
    echo  "-e                       Configure build directory for Eclipse" 

fi

# leave a breadcrumb so reconfigure.sh can recreate the right environment
echo $1 > .breadcrumb

# return to original directory
cd ..
