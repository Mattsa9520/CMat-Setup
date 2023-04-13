#!/bin/bash

#==========

# A simple bash script to quickly setup a c++ project. I got tired of constantly creating 
# C++ projects with the same layout and decided to automate it with a simple script. I'm 
# planning on creating a simple build script as well so that this one doesn't have to create
# one for you. This script creates the project relative to whatever repository your in, however you 
# can pass in an absolute path and it will work as expected. 
# just run cpp_setup [project_name]
# enjoy :)

#==========

# Check if there was even an argument passed, instruct user what to do 
# if there was no arguments.
if [ "$#" -eq 0 ]
then
    echo "Project name not given, add a project name after the commmand"
    exit 1
fi

project_name="$1"
echo ${project_name}
echo ${project_name:0:1}

# create project root directory form argument
mkdir -p ${project_name}
# create subdirectories.
# Tried to follow the most common c++ filing conventions that I 
# saw online, obviously it's all up to personal preference.
mkdir -p ${project_name}/src
mkdir -p ${project_name}/include
mkdir -p ${project_name}/target
mkdir -p ${project_name}/target/debug
mkdir -p ${project_name}/target/release

# create main file
touch ${project_name}/src/main.cpp
echo "#include <iostream>

int main() 
{
    std::cout << \"Hello, World!\\n\";
}" > ${project_name}/src/main.cpp

# Show the user where the path to their project is.
echo "Project Setup Complete"

# Check whether or not the user input an absolute path or a relative path
# Print appropriate message depending on whether or not they did. 
if [ ${project_name:0:1} != "/" ]
then    
    cwd=$(pwd)
    echo "Project located at: ${cwd}/${project_name}"
else
    echo "Project located at: ${project_name}"
fi

