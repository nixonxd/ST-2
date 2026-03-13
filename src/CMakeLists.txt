set(header_path "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(header ${header_path}/circle.h
           ${header_path}/tasks.h)
set(src circle.cpp
        tasks.cpp)

add_library(${PROJECT_NAME} SHARED
  ${header}
  ${src})
  
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}
  pthread)

add_executable(${PROJECT_NAME}.info main.cpp)
target_include_directories(${PROJECT_NAME}.info
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}.info
  ${PROJECT_NAME})

enable_testing()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}_tests test/tests.cpp)
target_include_directories(${PROJECT_NAME}_tests
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
         ${${PROJECT_NAME}_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_tests
  ${PROJECT_NAME}
  GTest::GTest
  GTest::Main
  Threads::Threads)

add_test(NAME ${PROJECT_NAME}_tests
         COMMAND ${PROJECT_NAME}_tests)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION "${lib_dest}"
    ARCHIVE DESTINATION "${lib_dest}"
    COMPONENT library)
install(TARGETS ${PROJECT_NAME}.info
        RUNTIME DESTINATION "${tool_dest}"
    COMPONENT library)
install(FILES ${header} DESTINATION "${include_dest}")