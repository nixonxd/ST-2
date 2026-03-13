add_executable(${PROJECT_NAME}.test
  AllTests.cpp
  tests.cpp)
target_link_libraries(${PROJECT_NAME}.test
  ${PROJECT_NAME} gtest pthread)
target_include_directories(${PROJECT_NAME}.test
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_compile_definitions(${PROJECT_NAME}.test 
  PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}")

install(TARGETS ${PROJECT_NAME}.test
        DESTINATION "${tool_dest}")