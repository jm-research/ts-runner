file(GLOB UNITTESTS_LIST *.cpp)

foreach(FILE_PATH ${UNITTESTS_LIST})
  string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FILE_PATH})
  message(STATUS "unittest files found: ${FILE_NAME}.cpp")
  add_executable(${FILE_NAME} ${FILE_NAME}.cpp)
  target_link_libraries(${FILE_NAME} GTest::gtest GTest::gtest_main fmt tsrunner)
  add_test(${FILE_NAME} ${FILE_NAME})
endforeach()
