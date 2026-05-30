# Лабораторная работа №8
## Шаг 1
Аналогично прошлым лабораторным работам, подготовим наше рабочее окружение, объявим переменные среды и скопируем репозиторий lab07 как основу для выполнения lab08.

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

# Клонировать lab07 как основу для lab08
git clone https://github.com/${GITHUB_USERNAME}/lab07 projects/lab08
cd projects/lab08

# Изменить remote на новый репозиторий lab08
git remote remove origin
git remote add origin https://github.com/${GITHUB_USERNAME}/lab08
```
## Шаг 2
Установим в систему утилиту doxygen для генерации документации из комментариев в исходном коде, а также пакет graphviz для построения красивых диаграмм связей классов и функций.

```
# Обновить индексы пакетов и установить doxygen с зависимостями
sudo apt-get update && sudo apt-get install -y doxygen graphviz
```
Вывод:  
```
Пол:1 http://security.debian.org/debian-security trixie-security InRelease [43,4 kB]
Пол:2 http://security.debian.org/debian-security trixie-security/main Sources [167 kB]
Сущ:3 http://deb.debian.org/debian trixie InRelease                            
Пол:4 http://deb.debian.org/debian trixie-updates InRelease [47,3 kB]          
Пол:5 http://security.debian.org/debian-security trixie-security/main amd64 Packages [176 kB]
Пол:6 http://security.debian.org/debian-security trixie-security/main Translation-en [111 kB]
Игн:7 https://download.sublimetext.com apt/stable/ InRelease                   
Игн:7 https://download.sublimetext.com apt/stable/ InRelease       
Игн:7 https://download.sublimetext.com apt/stable/ InRelease       
Ошб:7 https://download.sublimetext.com apt/stable/ InRelease       
  SSL connection failed: error:00000000:lib(0)::reason(0) / Соединение разорвано другой стороной [IP: 159.203.66.81 443]
Получено 545 kB за 1мин 50с (4 951 B/s)                            
Чтение списков пакетов… Готово
W: Не удалось получить https://download.sublimetext.com/apt/stable/InRelease  SSL connection failed: error:00000000:lib(0)::reason(0) / Соединение разорвано другой стороной [IP: 159.203.66.81 443]
W: Некоторые индексные файлы скачать не удалось. Они были проигнорированы, или вместо них были использованы старые версии.
Чтение списков пакетов… Готово
Построение дерева зависимостей… Готово
Чтение информации о состоянии… Готово         
Будут установлены следующие дополнительные пакеты:
  libann0 libcdt5 libcgraph6 libfmt10 libgts-0.7-5t64 libgts-bin libgvc6
  libgvpr2 liblab-gamut1 libpathplan4 libxapian30
Предлагаемые пакеты:
  doxygen-latex doxygen-doc doxygen-gui gsfonts graphviz-doc xapian-tools
Следующие НОВЫЕ пакеты будут установлены:
  doxygen graphviz libann0 libcdt5 libcgraph6 libfmt10 libgts-0.7-5t64
  libgts-bin libgvc6 libgvpr2 liblab-gamut1 libpathplan4 libxapian30
Обновлено 0 пакетов, установлено 13 новых пакетов, для удаления отмечено 0 пакетов, и 217 пакетов не обновлено.
Необходимо скачать 8 385 kB архивов.
После данной операции объём занятого дискового пространства возрастёт на 33,4 MB.
Пол:1 http://deb.debian.org/debian trixie/main amd64 libfmt10 amd64 10.1.1+ds1-4 [127 kB]
Пол:2 http://deb.debian.org/debian trixie/main amd64 libxapian30 amd64 1.4.29-3 [1 165 kB]
Пол:3 http://deb.debian.org/debian trixie/main amd64 doxygen amd64 1.9.8+ds-2.1 [5 017 kB]
Пол:4 http://deb.debian.org/debian trixie/main amd64 libann0 amd64 1.1.2+doc-9+b1 [25,1 kB]
Пол:5 http://deb.debian.org/debian trixie/main amd64 libcdt5 amd64 2.42.4-3 [40,3 kB]
Пол:6 http://deb.debian.org/debian trixie/main amd64 libcgraph6 amd64 2.42.4-3 [64,0 kB]
Пол:7 http://deb.debian.org/debian trixie/main amd64 libgts-0.7-5t64 amd64 0.7.6+darcs121130-5.2+b1 [160 kB]
Пол:8 http://deb.debian.org/debian trixie/main amd64 libpathplan4 amd64 2.42.4-3 [42,6 kB]
Пол:9 http://deb.debian.org/debian trixie/main amd64 libgvc6 amd64 2.42.4-3 [686 kB]
Пол:10 http://deb.debian.org/debian trixie/main amd64 libgvpr2 amd64 2.42.4-3 [192 kB]
Пол:11 http://deb.debian.org/debian trixie/main amd64 liblab-gamut1 amd64 2.42.4-3 [198 kB]
Пол:12 http://deb.debian.org/debian trixie/main amd64 graphviz amd64 2.42.4-3 [621 kB]
Пол:13 http://deb.debian.org/debian trixie/main amd64 libgts-bin amd64 0.7.6+darcs121130-5.2+b1 [47,7 kB]
Получено 8 385 kB за 13с (628 kB/s)                                            
Выбор ранее не выбранного пакета libfmt10:amd64.
(Чтение базы данных … на данный момент установлено 169315 файлов и каталогов.)
Подготовка к распаковке …/00-libfmt10_10.1.1+ds1-4_amd64.deb …
Распаковывается libfmt10:amd64 (10.1.1+ds1-4) …
Выбор ранее не выбранного пакета libxapian30:amd64.
Подготовка к распаковке …/01-libxapian30_1.4.29-3_amd64.deb …
Распаковывается libxapian30:amd64 (1.4.29-3) …
Выбор ранее не выбранного пакета doxygen.
Подготовка к распаковке …/02-doxygen_1.9.8+ds-2.1_amd64.deb …
Распаковывается doxygen (1.9.8+ds-2.1) …
Выбор ранее не выбранного пакета libann0.
Подготовка к распаковке …/03-libann0_1.1.2+doc-9+b1_amd64.deb …
Распаковывается libann0 (1.1.2+doc-9+b1) …
Выбор ранее не выбранного пакета libcdt5:amd64.
Подготовка к распаковке …/04-libcdt5_2.42.4-3_amd64.deb …
Распаковывается libcdt5:amd64 (2.42.4-3) …
Выбор ранее не выбранного пакета libcgraph6:amd64.
Подготовка к распаковке …/05-libcgraph6_2.42.4-3_amd64.deb …
Распаковывается libcgraph6:amd64 (2.42.4-3) …
Выбор ранее не выбранного пакета libgts-0.7-5t64:amd64.
Подготовка к распаковке …/06-libgts-0.7-5t64_0.7.6+darcs121130-5.2+b1_amd64.deb …
Распаковывается libgts-0.7-5t64:amd64 (0.7.6+darcs121130-5.2+b1) …
Выбор ранее не выбранного пакета libpathplan4:amd64.
Подготовка к распаковке …/07-libpathplan4_2.42.4-3_amd64.deb …
Распаковывается libpathplan4:amd64 (2.42.4-3) …
Выбор ранее не выбранного пакета libgvc6.
Подготовка к распаковке …/08-libgvc6_2.42.4-3_amd64.deb …
Распаковывается libgvc6 (2.42.4-3) …
Выбор ранее не выбранного пакета libgvpr2:amd64.
Подготовка к распаковке …/09-libgvpr2_2.42.4-3_amd64.deb …
Распаковывается libgvpr2:amd64 (2.42.4-3) …
Выбор ранее не выбранного пакета liblab-gamut1:amd64.
Подготовка к распаковке …/10-liblab-gamut1_2.42.4-3_amd64.deb …
Распаковывается liblab-gamut1:amd64 (2.42.4-3) …
Выбор ранее не выбранного пакета graphviz.
Подготовка к распаковке …/11-graphviz_2.42.4-3_amd64.deb …
Распаковывается graphviz (2.42.4-3) …
Выбор ранее не выбранного пакета libgts-bin.
Подготовка к распаковке …/12-libgts-bin_0.7.6+darcs121130-5.2+b1_amd64.deb …
Распаковывается libgts-bin (0.7.6+darcs121130-5.2+b1) …
Настраивается пакет libxapian30:amd64 (1.4.29-3) …
Настраивается пакет liblab-gamut1:amd64 (2.42.4-3) …
Настраивается пакет libpathplan4:amd64 (2.42.4-3) …
Настраивается пакет libann0 (1.1.2+doc-9+b1) …
Настраивается пакет libgts-0.7-5t64:amd64 (0.7.6+darcs121130-5.2+b1) …
Настраивается пакет libcdt5:amd64 (2.42.4-3) …
Настраивается пакет libcgraph6:amd64 (2.42.4-3) …
Настраивается пакет libfmt10:amd64 (10.1.1+ds1-4) …
Настраивается пакет libgts-bin (0.7.6+darcs121130-5.2+b1) …
Настраивается пакет doxygen (1.9.8+ds-2.1) …
Настраивается пакет libgvc6 (2.42.4-3) …
Настраивается пакет libgvpr2:amd64 (2.42.4-3) …
Настраивается пакет graphviz (2.42.4-3) …
Обрабатываются триггеры для man-db (2.13.1-1) …
Обрабатываются триггеры для libc-bin (2.41-12+deb13u3) …
```
## Шаг 3
Сгенерируем базовый файл конфигурации Doxygen (Doxyfile) по умолчанию и отредактируем его ключевые параметры с помощью потокового редактора gsed (sed), чтобы настроить пути к исходникам и включить генерацию диаграмм.

```
# Создать стандартный конфигурационный файл Doxyfile
doxygen -g
```
Вывод:
```
Configuration file 'Doxyfile' created.

Now edit the configuration file and enter

  doxygen

to generate the documentation for your project
```
```
# Сконфигурировать основные параметры внутри Doxyfile
gsed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = "solver"/' Doxyfile
gsed -i 's/OUTPUT_DIRECTORY       =/OUTPUT_DIRECTORY       = doxygen_output/' Doxyfile
gsed -i 's/INPUT                  =/INPUT                  = include\/ sources\/ demo\//' Doxyfile
gsed -i 's/RECURSIVE              = NO/RECUR
SIVE              = YES/' Doxyfile
gsed -i 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/' Doxyfile
gsed -i 's/HAVE_DOT               = NO/HAVE_DOT               = YES/' Doxyfile
gsed -i 's/GENERATE_LATEX         = YES/GENERATE_LATEX         = NO/' Doxyfile
```
## Шаг 4
Добавим документирующие комментарии в формате Doxygen в заголовочный файл нашей библиотеки, чтобы описать назначение функций и их аргументы.

```
# Добавить комментарии в файл include/print.hpp
cat > include/print.hpp <<EOF
/**
 * @file print.hpp
 * @brief Заголовочный файл с функциями вывода текста
 */

#pragma once

#include <string>
#include <iostream>

/**
 * @brief Функция для записи текста в любой стандартный выходной поток
 * @param text Строка текста для вывода
 * @param out Ссылка на поток вывода (по умолчанию std::cout)
 */
void print(const std::string& text, std::ostream& out = std::cout);
EOF
Проверим локальную генерацию документации, запустив doxygen.
```

```
# Сборка локальной документации
doxygen Doxyfile
```
Вывод:
```
Doxygen version used: 1.9.8
Notice: Output directory 'doxygen_output' does not exist. I have created it for you.
Searching for include files...
Searching for example files...
Searching for images...
Searching for dot files...
Searching for msc files...
Searching for dia files...
Searching for files to exclude
Searching INPUT for files to process...
Searching for files in directory /home/igor/Brandon-Triks/workspace/projects/lab08/include
Searching for files in directory /home/igor/Brandon-Triks/workspace/projects/lab08/sources
Searching for files in directory /home/igor/Brandon-Triks/workspace/projects/lab08/demo
Reading and parsing tag files
Parsing files
Preprocessing /home/igor/Brandon-Triks/workspace/projects/lab08/include/print.hpp...
Parsing file /home/igor/Brandon-Triks/workspace/projects/lab08/include/print.hpp...
Preprocessing /home/igor/Brandon-Triks/workspace/projects/lab08/sources/print.cpp...
Parsing file /home/igor/Brandon-Triks/workspace/projects/lab08/sources/print.cpp...
Preprocessing /home/igor/Brandon-Triks/workspace/projects/lab08/sources/solver.cpp...
Parsing file /home/igor/Brandon-Triks/workspace/projects/lab08/sources/solver.cpp...
Preprocessing /home/igor/Brandon-Triks/workspace/projects/lab08/demo/main.cpp...
Parsing file /home/igor/Brandon-Triks/workspace/projects/lab08/demo/main.cpp...
Building macro definition list...
Building group list...
Building directory list...
Building namespace list...
Building file list...
Building class list...
Building concept list...
Computing nesting relations for classes...
Associating documentation with classes...
Associating documentation with concepts...
Associating documentation with modules...
Building example list...
Searching for enumerations...
Searching for documented typedefs...
Searching for members imported via using declarations...
Searching for included using directives...
Searching for documented variables...
Building interface member list...
Building member list...
Searching for friends...
Searching for documented defines...
Computing class inheritance relations...
Computing class usage relations...
Flushing cached template relations that have become invalid...
Computing class relations...
Add enum values to enums...
Searching for member function documentation...
Creating members for template instances...
Building page list...
Search for main page...
Computing page relations...
Determining the scope of groups...
Computing module relations...
Sorting lists...
Determining which enums are documented
Computing member relations...
Building full member lists recursively...
Adding members to member groups.
Computing member references...
Inheriting documentation...
Generating disk names...
Adding source references...
Adding xrefitems...
Sorting member lists...
Setting anonymous enum type...
Computing dependencies between directories...
Generating citations page...
Counting members...
Counting data structures...
Resolving user defined references...
Finding anchors and sections in the documentation...
Transferring function references...
Combining using relations...
Adding members to index pages...
Correcting members for VHDL...
Computing tooltip texts...
Generating style sheet...
Generating search indices...
Generating example documentation...
Generating file sources...
Generating code for file include/print.hpp...
Generating file documentation...
Generating docs for file demo/main.cpp...
Generating docs for file include/print.hpp...
Generating docs for file sources/print.cpp...
Generating docs for file sources/solver.cpp...
Generating page documentation...
Generating group documentation...
Generating class documentation...
Generating concept documentation...
Generating module documentation...
Generating namespace documentation...
Generating graph info page...
Generating directory documentation...
Generating dependency graph for directory demo
Generating dependency graph for directory sources
Generating index page...
Generating page index...
Generating topic index...
Generating module index...
Generating module member index...
Generating namespace index...
Generating namespace member index...
Generating concept index...
Generating annotated compound index...
Generating alphabetical compound index...
Generating hierarchical class index...
Generating graphical class hierarchy...
Generating member index...
Generating file index...
Generating file member index...
Generating example index...
finalizing index lists...
writing tag file...
Running plantuml with JAVA...
Running dot...
Generating dot graphs using 3 parallel threads...
Running dot for graph 1/8
Running dot for graph 2/8
Running dot for graph 3/8
Running dot for graph 4/8
Running dot for graph 5/8
Running dot for graph 6/8
Running dot for graph 7/8
Running dot for graph 8/8
Patching output file 1/6
Patching output file 2/6
Patching output file 3/6
Patching output file 4/6
Patching output file 5/6
Patching output file 6/6
type lookup cache used 2/65536 hits=3 misses=2
symbol lookup cache used 3/65536 hits=3 misses=3
finished...
```
## Шаг 5  
Шаг 5
Полностью перезапишем файл CMakeLists.txt чистой и корректной структурой, включая интеграцию Doxygen через пользовательскую цель doc, чтобы избежать ошибок дублирования или некорректной вложенности if / endif.

```
cat > CMakeLists.txt <<EOF
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
EOF
```
Удалим старый сломанный кэш CMake и заново выполним сборку и генерацию документации.

```
# Полностью удалить старую директорию сборки, чтобы сбросить сломанный кэш
rm -rf _builds

# Переконфигурировать проект с чистого листа
cmake -H. -B_builds -DBUILD_TESTS=ON
```
Вывод:  
```
...  
-- The C compiler identification is GNU 14.2.0
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
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.10 will be removed from a future version of
  CMake.
...  
-- [hunter] GTEST_ROOT: /home/igor/.hunter/_Base/ca7838d/d1e9b55/0b339ba/Install (ver.: 1.12.1)
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Found Doxygen: /usr/bin/doxygen (found version "1.9.8") found components: doxygen dot
-- Configuring done (1.4s)
-- Generating done (0.0s)
-- Build files have been written to: /home/igor/Brandon-Triks/workspace/projects/lab08/_builds
```  
## Шаг 6
Обновим автоматический воркфлоу непрерывной интеграции GitHub Actions в файле .github/workflows/ci.yml. Настроим его так, чтобы при каждом пуше в ветку main он компилировал проект, прогонял тесты, собирал документацию Doxygen и автоматически публиковал её на GitHub Pages (в ветку gh-pages).

```
# Создать папку для воркфлоу
mkdir -p .github/workflows

# Перезаписать файл конфигурации GitHub Actions
cat > .github/workflows/ci.yml <<EOF
name: CMake and Doxygen CI

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

    - name: Install Dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y doxygen graphviz clang

    - name: Configure CMake with Hunter
      run: cmake -H. -B_builds -DBUILD_TESTS=ON

    - name: Build project
      run: cmake --build _builds

    - name: Run tests
      run: cmake --build _builds --target test

    - name: Generate Documentation
      run: cmake --build _builds --target doc

    - name: Deploy to GitHub Pages
      if: github.ref == 'refs/heads/main'
      uses: peaceiris/actions-gh-pages@v4
      with:
        github_token: \${{ secrets.GITHUB_TOKEN }}
        publish_dir: ./doxygen_output/html
EOF
```  
# Шаг 7
Исключим сгенерированные локально папки с документацией и сборкой из индексации Git с помощью добавления правил в .gitignore, после чего закоммитим все файлы и отправим их в удаленный репозиторий lab08.

```
# Добавить выходную директорию doxygen и папки сборки в .gitignore
echo "doxygen_output/" >> .gitignore
echo "_builds/" >> .gitignore
echo "_logs/" >> .gitignore

# Добавить файлы в индекс, сделать коммит и отправить на GitHub
git add .
git commit -m "docs: clean rebuild, integrated doxygen target into cmake layout and added actions pages deploy"
git push origin main
```

# Вывод:
В ходе выполнения лабораторной работы мы познакомились с системой автоматического управления внешними зависимостями в C++ проектах с использованием пакетного менеджера Hunter. Мы перевели наш проект со статического ручного копирования исходников на автоматизированный учёт внешней тестовой библиотеки GTest через макрос HunterGate. Мы успешно решили проблему отсутствия внешних тулчейнов компиляции, установив пакет clang на хост-систему, что позволило скрипту polly.py штатно сгенерировать конфигурационные файлы проекта под clang-cxx14. Кроме того, мы научились переопределять корневые настройки Hunter, работать со сторонними тулчейнами и настроили непрерывную интеграцию через автоматические воркфлоу GitHub Actions.
