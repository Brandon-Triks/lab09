cmake_minimum_required(VERSION 3.10)

project(solver VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Описание библиотеки
add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)
target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Описание приложения solver
add_executable(solver ${CMAKE_CURRENT_SOURCE_DIR}/sources/solver.cpp)
target_link_libraries(solver print)

# Правила установки
install(TARGETS solver RUNTIME DESTINATION bin)
install(TARGETS print ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

# --- Блок CPack (СТРОГО В КОНЦЕ) ---
set(CPACK_PACKAGE_NAME "solver")
set(CPACK_PACKAGE_VENDOR "Brandon-Triks")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "your-email@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Brandon-Triks")

# Лицензия (нужна для MSI)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")

# Настройки для Windows WiX
set(CPACK_WIX_UPGRADE_GUID "E8A6820D-47C2-4309-8B77-8335D2E12345")
# Эта строка поможет CPack найти solver.exe в папке Release на Windows
set(CPACK_PACKAGE_EXECUTABLES "solver" "Solver Application")

include(CPack)
