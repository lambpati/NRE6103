#set(BINARY ${CMAKE_PROJECT_NAME}_tst)

#file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

#set(SOURCES ${TEST_SOURCES})

#add_executable(${BINARY} ${TEST_SOURCES})

#add_test(NAME ${BINARY} COMMAND ${BINARY})

#target_link_libraries(${BINARY} ${TEST_SOURCES} GTest::gtest_main)

#include(GoogleTest)
#gtest_discover_tests(${TEST_SOURCES})

add_executable(
  hello_test
  hello_test.cc
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)