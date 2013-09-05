#!/bin/sh
# cm - CMake shortcut command

SOURCE_DIR=$(printf "%q" "$PWD") # escapes the dir with backslashes

mkdir -p build/debug

cd build/debug

# If CMake cannot find one of these, uncomment and write the correct path
export GLEW_ROOT="E:/Projects/C++/Libs/glew-1.9.0-win32"
export GLM_ROOT="E:/Projects/C++/Libs/glm-0.9.4.1"

# SFML
export SFML_ROOT="E:/Projects/C++/Libs/SFML-2.0-gcc"

# Boost
export BOOST_ROOT="E:/Projects/C++/Libs/boost_1_53_0"

# Change this to Unix Makefiles on Linux
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$SOURCE_DIR -G "MSYS Makefiles" ../..

make
cd ..
