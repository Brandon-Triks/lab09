cmake_minimum_required(VERSION 3.10)

# 1. Указываем имя проекта SOLVER (это важно для имен пакетов)
project(solver VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

# 2. Описание библиотеки print
add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# 3. Описание исполняемого файла solver
# Он должен быть объявлен ДО команд install и CPack
add_executable(solver ${CMAKE_CURRENT_SOURCE_DIR}/sources/solver.cpp)
target_link_libraries(solver print)

# 4. Правила установки (куда попадут файлы при упаковке)
install(TARGETS solver RUNTIME DESTINATION bin)
install(TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

# 5. Примеры (если включены)
if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} print)
    install(TARGETS ${EXAMPLE_NAME} RUNTIME DESTINATION bin)
  endforeach()
endif()

# 6. Тесты (если включены)
if(BUILD_TESTS)
    enable_testing()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=maybe-uninitialized")
    add_subdirectory(third-party/gtest)
    file(GLOB TEST_SOURCES tests/*.cpp)
    add_executable(check ${TEST_SOURCES})
    target_link_libraries(check print gtest_main)
    add_test(NAME check COMMAND check)
endif()

# 7. НАСТРОЙКИ УПАКОВКИ (CPACK) - строго в конце файла
set(CPACK_PACKAGE_NAME "solver")
set(CPACK_PACKAGE_VENDOR "Brandon-Triks")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "your-email@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Brandon-Triks")

# Чтобы пакет назывался solver-1.0.0-OS.extension
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")

# Лицензия для Windows (WiX)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_WIX_UPGRADE_GUID "E8A6820D-47C2-4309-8B77-8335D2E12345")

# Генерировать только бинарные пакеты (убираем Source из названия)
set(CPACK_SOURCE_GENERATOR "") 

include(CPack)
