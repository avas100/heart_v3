# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\HeartApp_v3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\HeartApp_v3_autogen.dir\\ParseCache.txt"
  "HeartApp_v3_autogen"
  )
endif()
