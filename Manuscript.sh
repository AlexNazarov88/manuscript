#!/bin/sh

# Script that will set the required path for our executable
# The easiest way to do so is by creating a shell/bat script that will set the proper variables and then # call the executable.

#export LD_LIBRARY_PATH=`pwd`/libs
#export QT_QPA_PLATFORM_PLUGIN_PATH=`pwd`/libs/plugins/platforms
#export LD_LIBRARY_PATH="/opt/qt56/lib/":$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/opt/Manuscript/libs
#export QT_QPA_PLATFORM_PLUGIN_PATH=/opt/Manuscript/libs/plugins/platforms

#appname=`basename $0 | sed s,\.sh$,,`

#dirname=`dirname $0`
#tmp="${dirname#?}"

#if [ "${dirname%$tmp}" != "/" ]; then
#dirname=$PWD/$dirname
#fi
#LD_LIBRARY_PATH=$dirname
#export LD_LIBRARY_PATH
#$dirname/$appname "$@"

./Manuscript