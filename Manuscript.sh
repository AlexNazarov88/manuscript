#!/bin/sh

# Script that will set the required path for our executable
# The easiest way to do so is by creating a shell/bat script that will set the proper variables and then # call the executable.

export LD_LIBRARY_PATH=`pwd`/libs
export QT_QPA_PLATFORM_PLUGIN_PATH=`pwd`/libs/plugins/platforms
./Manuscript