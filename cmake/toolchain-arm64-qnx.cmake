# CMake toolchain file for building ARM software on OI environment

# this one is important
SET(CMAKE_SYSTEM_NAME QNX)
SET(arch gcc_ntox86_64)

#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   /home/test/qnx/qos223/host/linux/x86_64/usr/bin/qcc)
SET(CMAKE_C_COMPILER_TARGET ${arch})

SET(CMAKE_CXX_COMPILER /home/test/qnx/qos223/host/linux/x86_64/usr/bin/q++)
SET(CMAKE_CXX_COMPILER_TARGET ${arch})

SET(CMAKE_STRIP /home/test/qnx/qos223/host/linux/x86_64/usr/bin/ntox86_64-strip)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /home/test/qnx/qos223/target/qnx7/x86_64)

if(DEFINED ENV{EXTERNAL_LIB_DIR})
    LIST(APPEND CMAKE_FIND_ROOT_PATH "$ENV{EXTERNAL_LIB_DIR}")
endif()

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

# if we set to ONLY, cmake won't try to find local compiled external libs, for example
# the find_path call in pcl cmake FindEigen won't work
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
