# Лабораторная работа №7
## Шаг 1
Аналогично прошлым лабораторным работам, подготовим наше рабочее окружение, объявим переменные среды и скопируем репозиторий lab06 как основу для выполнения lab07.

```
# Установить переменные окружения
export GITHUB_USERNAME=Brandon-Triks
export GITHUB_EMAIL=ваш@email.com
alias edit=nano
alias gsed=sed # для Linux

# Перейти в рабочую директорию
cd ${GITHUB_USERNAME}/workspace
pushd .
source scripts/activate

# Клонировать lab06 как основу для lab07
git clone https://github.com/${GITHUB_USERNAME}/lab06 projects/lab07
cd projects/lab07

# Изменить remote на новый репозиторий lab07
git remote remove origin
git remote add origin https://github.com/${GITHUB_USERNAME}/lab07
```
## Шаг 2
Интегрируем менеджер пакетов Hunter в наш проект. Скачаем архив Hunter вручную через системный wget и сохраним его локально в проект, чтобы полностью защититься от сетевых сбоев встроенного в CMake загрузчика.

```
# Создать структуру папок для CMake модулей и архивов dependencies
mkdir -p cmake

# Скачать официальный файл HunterGate.cmake по рабочей ссылке
wget -O cmake/HunterGate.cmake https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake

# Скачать архив Hunter v0.24.8 локально в папку cmake
wget -O cmake/hunter-v0.24.8.tar.gz https://github.com/cpp-pm/hunter/archive/v0.24.8.tar.gz
```
Создадим демонстрационную утилиту в подпапке demo заранее, чтобы CMake не ругался на отсутствие исходных файлов при конфигурации проекта:

```
# Создать директорию demo
mkdir -p demo

# Создать файл main.cpp для утилиты demo
cat > demo/main.cpp <<EOF
#include <print.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
  const char* log_path = std::getenv("LOG_PATH");
  if (log_path == nullptr)
  {
    std::cerr << "undefined environment variable: LOG_PATH" << std::endl;
    return 1;
  }

  std::string text;
  while (std::cin >> text)
  {
    std::ofstream out{log_path, std::ios_base::app};
    print(text, out);
    out << std::endl;
  }
}
EOF
```
Полностью перезапишем CMakeLists.txt. Для обратной совместимости с Hunter v0.24.x мы используем имя таргета линковки GTest::gtest_main:

```
cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.10)

# 1. Глобальные настройки компилятора (C++11 обязателен для GTest)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Подключение менеджера пакетов Hunter через локальный архив с корректным хэшем
include(cmake/HunterGate.cmake)
HunterGate(
    URL "file://\${CMAKE_CURRENT_SOURCE_DIR}/cmake/hunter-v0.24.8.tar.gz"
    SHA1 "ca7838dded9a1811b04ffd56175f629e0af82d3d"
)

# 3. Объявление проекта
project(solver VERSION 1.0.0)

# 4. Описание библиотеки print
add_library(print STATIC \${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)
target_include_directories(print PUBLIC
  $<BUILD_INTERFACE:\${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# 5. Описание приложения solver
add_executable(solver \${CMAKE_CURRENT_SOURCE_DIR}/sources/solver.cpp)
target_link_libraries(solver print)

# 6. Подключение тестов через Hunter GTest (Используем корректный импортированный таргет)
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
add_executable(demo \${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp)
target_link_libraries(demo print)

# 8. Правила установки
install(TARGETS solver demo RUNTIME DESTINATION bin)
install(TARGETS print ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install(DIRECTORY \${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)

# 9. Блок CPack
set(CPACK_PACKAGE_NAME "solver")
set(CPACK_PACKAGE_VENDOR "Brandon-Triks")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "your-email@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Brandon-Triks")
set(CPACK_RESOURCE_FILE_LICENSE "\${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_WIX_UPGRADE_GUID "E8A6820D-47C2-4309-8B77-8335D2E12345")
set(CPACK_PACKAGE_EXECUTABLES "solver" "Solver Application")

include(CPack)
EOF
```
## Шаг 3
Проверим сборку проекта. Удалим старый закэшированный ошибочный воркспейс и запустим конфигурацию заново.

```
# Сбросить старую директорию сборки и очистить локальный кэш Hunter
rm -rf _builds
rm -rf $HOME/.hunter

# Сконфигурировать проект с включенными тестами
cmake -H. -B_builds -DBUILD_TESTS=ON
```

Вывод:
```
- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- [hunter] Calculating Toolchain-SHA1
-- [hunter] Calculating Config-SHA1
-- [hunter] HUNTER_ROOT: /home/igor/projects/hunter
-- [hunter] [ Hunter-ID: xxxxxxx | Toolchain-ID: d1e9b55 | Config-ID: dde7d8a ]
-- [hunter] GTEST_ROOT: /home/igor/projects/hunter/_Base/xxxxxxx/d1e9b55/dde7d8a/Install (ver.: 1.15.2)
-- [hunter] Building GTest
loading initial cache file /home/igor/projects/hunter/_Base/xxxxxxx/d1e9b55/dde7d8a/cache.cmake
loading initial cache file /home/igor/projects/hunter/_Base/xxxxxxx/d1e9b55/dde7d8a/Build/GTest/args.cmake
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/igor/projects/hunter/_Base/xxxxxxx/d1e9b55/dde7d8a/Build/GTest/Build
...
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /home/igor/projects/hunter/_Base/xxxxxxx/d1e9b55/dde7d8a/Build/GTest/Build/GTest-Release-prefix/src/GTest-Release-build
...
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (0.3s)
-- Generating done (0.0s)
-- Build files have been written to: /home/igor/projects/hunter/_Base/xxxxxxx/d1e9b55/dde7d8a
...
- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (24.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/igor/Brandon-Triks/workspace/projects/lab07/_builds
...
```
```
# Скомпилировать проект вместе с тестами
cmake --build _builds
```
Вывод:
```
[ 12%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 25%] Linking CXX static library libprint.a
[ 25%] Built target print
[ 37%] Building CXX object CMakeFiles/solver.dir/sources/solver.cpp.o
[ 50%] Linking CXX executable solver
[ 50%] Built target solver
[ 62%] Building CXX object CMakeFiles/test_solver.dir/sources/solver.cpp.o
[ 75%] Linking CXX executable test_solver
[ 75%] Built target test_solver
[ 87%] Building CXX object CMakeFiles/demo.dir/demo/main.cpp.o
[100%] Linking CXX executable demo
[100%] Built target demo

```
```
# Запустить прогон тестов
cmake --build _builds --target test
```
Вывод:
```
Running tests...
Test project /home/igor/Brandon-Triks/workspace/projects/lab07/_builds
    Start 1: solver_test
1/1 Test #1: solver_test ......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec

```
## Шаг 4
Проверим переопределение корня Hunter через локальный репозиторий и работу локального файла конфигурации config.cmake.

```
# Клонировать локально репозиторий менеджера пакетов hunter
git clone https://github.com/cpp-pm/hunter $HOME/projects/hunter

# Установить переменную среды HUNTER_ROOT на наш локальный репозиторий
export HUNTER_ROOT=$HOME/projects/hunter

# Очистить прошлую сборку
rm -rf _builds

# Снова запустить конфигурацию, используя локальный репозиторий Hunter
cmake -H. -B_builds -DBUILD_TESTS=ON
```


Создадим файл локальных настроек проекта cmake/Hunter/config.cmake, чтобы зафиксировать нужную нам версию пакета:

```
# Создать директорию для собственных конфигураций внутри проекта
mkdir -p cmake/Hunter

# Записать кастомную версию для GTest
cat > cmake/Hunter/config.cmake <<EOF
hunter_config(GTest VERSION 1.10.0-hunter-p0)
EOF
```


## Шаг 5
Утилита demo уже успешно создана на Шаге 2 и сконфигурирована в CMakeLists.txt. Проверим структуру каталогов проекта, чтобы убедиться, что всё находится на своих местах.

```
# Посмотреть структуру проекта
ls -la demo/
```
Вывод:
```
итого 12
drwxrwxr-x  2 igor igor 4096 мая 25 21:44 .
drwxrwxr-x 13 igor igor 4096 мая 25 21:56 ..
-rw-rw-r--  1 igor igor  443 мая 25 21:44 main.cpp
```
## Шаг 6
Подключим репозиторий polly, содержащий шаблоны тулчейнов для CMake. Установим недостающий в системе компилятор clang, чтобы протестировать кросс-компиляцию сборки под стандарт clang-cxx14.

```
# Добавить polly как подмодуль гит
mkdir -p tools
git submodule add https://github.com/ruslo/polly tools/polly

# Установить компилятор clang в систему, чтобы polly смог его обнаружить
sudo apt-get update && sudo apt-get install -y clang

# Проверить сборку проекта с использованием тулчейна через polly
tools/polly/bin/polly.py --toolchain clang-cxx14
```
Вывод:
```
Python version: 3.13
Build dir: /home/igor/Brandon-Triks/workspace/projects/lab07/_builds/clang-cxx14
Execute command: [
  `which`
  `cmake`
]

[/home/igor/Brandon-Triks/workspace/projects/lab07]> "which" "cmake"

/usr/bin/cmake
Execute command: [
  `cmake`
  `--version`
]

[/home/igor/Brandon-Triks/workspace/projects/lab07]> "cmake" "--version"

cmake version 3.31.6

CMake suite maintained and supported by Kitware (kitware.com/cmake).
Execute command: [
  `cmake`
  `-H.`
  `-B/home/igor/Brandon-Triks/workspace/projects/lab07/_builds/clang-cxx14`
  `-GUnix Makefiles`
  `-DCMAKE_TOOLCHAIN_FILE=/home/igor/Brandon-Triks/workspace/projects/lab07/tools/polly/clang-cxx14.cmake`
]

[/home/igor/Brandon-Triks/workspace/projects/lab07]> "cmake" "-H." "-B/home/igor/Brandon-Triks/workspace/projects/lab07/_builds/clang-cxx14" "-GUnix Makefiles" "-DCMAKE_TOOLCHAIN_FILE=/home/igor/Brandon-Triks/workspace/projects/lab07/tools/polly/clang-cxx14.cmake"

-- [polly] Used toolchain: clang / c++14 support
-- The C compiler identification is Clang 19.1.7
-- The CXX compiler identification is Clang 19.1.7
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/clang - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/clang++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.7s)
-- Generating done (0.0s)
-- Build files have been written to: /home/igor/Brandon-Triks/workspace/projects/lab07/_builds/clang-cxx14
Execute command: [
  `cmake`
  `--build`
  `/home/igor/Brandon-Triks/workspace/projects/lab07/_builds/clang-cxx14`
  `--`
]

[/home/igor/Brandon-Triks/workspace/projects/lab07]> "cmake" "--build" "/home/igor/Brandon-Triks/workspace/projects/lab07/_builds/clang-cxx14" "--"

[ 16%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 33%] Linking CXX static library libprint.a
[ 33%] Built target print
[ 50%] Building CXX object CMakeFiles/solver.dir/sources/solver.cpp.o
[ 66%] Linking CXX executable solver
[ 66%] Built target solver
[ 83%] Building CXX object CMakeFiles/demo.dir/demo/main.cpp.o
[100%] Linking CXX executable demo
[100%] Built target demo
-
Log saved: /home/igor/Brandon-Triks/workspace/projects/lab07/_logs/polly/clang-cxx14/log.txt
-
Generate: 0:00:01.722649s
Build: 0:00:02.099593s
-
Total: 0:00:03.824549s
-
SUCCESS
```

## Шаг 7
Настроим автоматический воркфлоу тестирования через непрерывную интеграцию GitHub Actions вместо Travis CI. Создадим файл .github/workflows/ci.yml. Шаг с созданием файла REPORT.md пропускаем.

```
# Создать папку для воркфлоу
mkdir -p .github/workflows

# Создать конфигурацию GitHub Actions
cat > .github/workflows/ci.yml <<EOF
name: Hunter CMake CI

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v4

    - name: Configure CMake with Hunter
      run: cmake -H. -B_builds -DBUILD_TESTS=ON

    - name: Build project
      run: cmake --build _builds

    - name: Run tests
      run: cmake --build _builds --target test
EOF
```
Отправим все изменения в наш удаленный репозиторий на GitHub:

```
# Закоммитить и запушить изменения
git add .
git commit -m "fixed cmake layout, installed clang compiler toolset dependency for polly integrations"
git push origin main
```
Вывод:
```
Username for 'https://github.com': Brandon-Triks
Password for 'https://Brandon-Triks@github.com': 
Перечисление объектов: 212, готово.
Подсчет объектов: 100% (212/212), готово.
При сжатии изменений используется до 2 потоков
Сжатие объектов: 100% (118/118), готово.
Запись объектов: 100% (212/212), 2.69 МиБ | 3.64 МиБ/с, готово.
Total 212 (delta 64), reused 191 (delta 61), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (64/64), done.
To https://github.com/Brandon-Triks/lab07
 * [new branch]      main -> main
```

# Вывод:
В ходе выполнения лабораторной работы мы познакомились с системой автоматического управления внешними зависимостями в C++ проектах с использованием пакетного менеджера Hunter. Мы перевели наш проект со статического ручного копирования исходников на автоматизированный учёт внешней тестовой библиотеки GTest через макрос HunterGate. Мы успешно решили проблему отсутствия внешних тулчейнов компиляции, установив пакет clang на хост-систему, что позволило скрипту polly.py штатно сгенерировать конфигурационные файлы проекта под clang-cxx14. Кроме того, мы научились переопределять корневые настройки Hunter, работать со сторонними тулчейнами и настроили непрерывную интеграцию через автоматические воркфлоу GitHub Actions.
