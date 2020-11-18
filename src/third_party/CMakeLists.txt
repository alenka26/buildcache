#---------------------------------------------------------------------------------------------------
# Copyright (c) 2018 Marcus Geelnard
#
# This software is provided 'as-is', without any express or implied warranty. In no event will the
# authors be held liable for any damages arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose, including commercial
# applications, and to alter it and redistribute it freely, subject to the following restrictions:
#
#  1. The origin of this software must not be misrepresented; you must not claim that you wrote
#     the original software. If you use this software in a product, an acknowledgment in the
#     product documentation would be appreciated but is not required.
#
#  2. Altered source versions must be plainly marked as such, and must not be misrepresented as
#     being the original software.
#
#  3. This notice may not be removed or altered from any source distribution.
#---------------------------------------------------------------------------------------------------

# Disable all warnings for third party code.
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
elseif(MSVC)
  # Remove any /W flags from the compiler options.
  string(REGEX REPLACE "(^| )([/-])W[0-9]( |$)" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE "(^| )([/-])W[0-9]( |$)" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

#---------------------------------------------------------------------------------------------------
# doctest
#---------------------------------------------------------------------------------------------------
add_library(doctest
  doctest/doctest_main.cpp
  )
target_include_directories(doctest INTERFACE .)

#---------------------------------------------------------------------------------------------------
# cJSON
#---------------------------------------------------------------------------------------------------
add_library(cjson
  cjson/cJSON.c
  )
target_include_directories(cjson INTERFACE .)

#---------------------------------------------------------------------------------------------------
# MD4
#---------------------------------------------------------------------------------------------------
add_library(md4
  md4/md4.c
  )
target_include_directories(md4 INTERFACE .)

#---------------------------------------------------------------------------------------------------
# cpp-base64
#---------------------------------------------------------------------------------------------------
add_library(cpp-base64
  cpp-base64/base64.cpp
  )
target_include_directories(cpp-base64 INTERFACE .)

#---------------------------------------------------------------------------------------------------
# mingw-std-threads (implements std::thread for MinGW).
#---------------------------------------------------------------------------------------------------
if(MINGW)
  add_library(mingw_std_threads INTERFACE)
  target_include_directories(mingw_std_threads INTERFACE .)
endif()

#---------------------------------------------------------------------------------------------------
# HTTPRequest
#---------------------------------------------------------------------------------------------------
add_library(HTTPRequest INTERFACE)
target_include_directories(HTTPRequest INTERFACE HTTPRequest/include)
if(WIN32 OR MINGW)
  target_link_libraries(HTTPRequest INTERFACE ws2_32)
endif()
