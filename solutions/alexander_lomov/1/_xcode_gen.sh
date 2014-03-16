#!/bin/sh

export SOLUTION_NAME=task1
export BUILD_FOLDER=xcode_proj
export BUILD_TYPE=Debug

if [ ! -d $BUILD_FOLDER ];
then
  mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
cmake -DVERBOSE=ON -DSOLUTION_NAME=$SOLUTION_NAME -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Xcode" ../
cd ../
