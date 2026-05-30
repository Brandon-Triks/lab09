
cmake_minimum_required(VERSION 3.10)

# 1. Глобальные настройки компилятора
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Подключение менеджера пакетов Hunter
include(cmake/HunterGate.cmake)
HunterGate(
    URL "file://${CMAKE_CURRENT_SOURCE_DIR}/cmake/hunter-v0.24.8.tar.gz"
    SHA1 "ca7838dded9a1811b04ffd56175f629e0af82d3d"
)

# 3. Объявление проекта
project(solver VERSION 1.0.0)

# 4. Описание библиотеки print
add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)
target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# 5. Описание приложения solver
add_executable(solver ${CMAKE_CURRENT_SOURCE_DIR}/sources/solver.cpp)
target_link_libraries(solver print)

# 6. Подключение тестов через Hunter GTest
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
  hunter_add_package(GTest)
  find_package(GTest CONFIG REQUIRED)
  enable_testing()
  add_executable(test_solver sources/solver.cpp)
  target_link_libraries(test_solver print GTest::gtest_main)
  add_test(NAME solver_test COMMAND test_solver)
endif()

# 7. Демонстрационная утилита
add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp)
target_link_libraries(demo print)

# 8. Правила установки
install(TARGETS solver demo RUNTIME DESTINATION bin)
install(TARGETS print ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

# 9. Блок CPack
set(CPACK_PACKAGE_NAME "solver")
set(CPACK_PACKAGE_VENDOR "Brandon-Triks")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "your-email@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Brandon-Triks")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_WIX_UPGRADE_GUID "E8A6820D-47C2-4309-8B77-8335D2E12345")
set(CPACK_PACKAGE_EXECUTABLES "solver" "Solver Application")

include(CPack)

# 10. Интеграция Doxygen в CMake
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
  )
endif()
