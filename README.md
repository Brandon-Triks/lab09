# Лабораторная работа 5
## Шаг 1  - настройка окружения  
Создадим переменную окружения, псевдоним команды, сохраним текущую директорию в стек и выполним скрипт активации с помощью следующих команд:  
```
# Установить переменные  
export GITHUB_USERNAME=Brandon-Triks  
alias gsed=sed  # для Linux (gsed = sed)  
  
# Перейти в рабочую директорию  
cd ${GITHUB_USERNAME}/workspace  
pushd .  
source scripts/activate  
```
   
 ## Шаг 2 - клонирование репозитория 4-ой лабы  
 ```
 Скопируем репозиторий 4-ой лабы и настроим удалённый репозиторий, используя нижепредставленные команды:  
# Клонировать lab04 как основу для lab06  
git clone https://github.com/${GITHUB_USERNAME}/lab04 projects/lab06  
cd projects/lab06  
# Изменить remote на новый репозиторий  
git remote remove origin  
git remote add origin https://github.com/${GITHUB_USERNAME}/lab06  
```

## Шаг 3 - добавим Google Test как подмодуль  
Снизу представлены необходимые для этого команды с пояснениями:  
  *Команды:*  
```
# Создать папку для сторонних библиотек 
mkdir third-party  
  
# Добавить Google Test как git submodule  
git submodule add https://github.com third-party/gtest  
```  
  *Вывод*:
```
Клонирование в «/home/igor/Brandon-Triks/workspace/projects/lab06/third-party/gtest»...  
remote: Enumerating objects: 28627, done.  
remote: Counting objects: 100% (61/61), done.  
remote: Compressing objects: 100% (46/46), done.  
remote: Total 28627 (delta 32), reused 15 (delta 15), pack-reused 28566 (from 2)  
Получение объектов: 100% (28627/28627), 13.74 МиБ | 9.89 МиБ/с, готово.  
Определение изменений: 100% (21273/21273), готово.  
```  
*Команды:*
```
# Перейти в gtest и выбрать версию  
cd third-party/gtest && git checkout release-1.8.1 && cd ../..  
```
  
  *Вывод*:  
```
Примечание: переключение на «release-1.8.1».  
  
Вы сейчас в состоянии «отсоединённого указателя HEAD». Можете осмотреться,  
внести экспериментальные изменения и зафиксировать их, также можете  
отменить любые коммиты, созданные в этом состоянии, не затрагивая другие  
ветки, переключившись обратно на любую ветку.  
  
Если хотите создать новую ветку для сохранения созданных коммитов, можете 
сделать это (сейчас или позже), используя команду switch с параметром -c.  
Например:  
  
  git switch -c <новая-ветка>  
  
Или отмените эту операцию с помощью:  
  
  git switch -  
  
Отключите этот совет, установив переменную конфигурации  
advice.detachedHead в значение false  
  
HEAD сейчас на 2fe3bd99 Merge pull request #1433 from dsacre/fix-clang-warnings  
```  
*Команды:*  
```
# Зафиксировать изменения  
git add third-party/gtest  
git commit -m "added gtest framework"  
```
  *Вывод*:  
  ```
 [main d9a5e97] added gtest framework  
 2 files changed, 4 insertions(+)  
 create mode 100644 .gitmodules  
 create mode 160000 third-party/gtest  
```
  
  ## Шаг 4 - модификация CMakeLists.txt  
  В этом шаге модифицировуем CMakeLists.txt, добавив опцию BUILD_TESTS для управления сборкой тестов. Внутри условия подключим библиотеку Google Test, автоматически найдём все тестовые файлы и создадим исполняемый файл check, связав его с основным проектом для последующего запуска проверок через CMake.
  Подробнее: 
  ```
  # Добавить опции BUILD_TESTS в CMakeLists.txt
gsed -i '/option(BUILD_EXAMPLES "Build examples" OFF)/a\
option(BUILD_TESTS "Build tests" OFF)' CMakeLists.txt

# Добавить конфигурацию тестирования
cat >> CMakeLists.txt <<EOF

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest)
    file(GLOB \${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
    add_executable(check \${\${PROJECT_NAME}_TEST_SOURCES})
    target_link_libraries(check \${PROJECT_NAME} gtest_main)
    add_test(NAME check COMMAND check)
endif()
EOF
```
## Шаг 5 - создание тестового файла  
Создадим папку tests и напишем
тестовый файл test1.cpp, который проверяет корректность работы функции print: записывает строку в файл, 
затем читает её обратно и сравнивает результат с исходным значением через макрос EXPECT_EQ.  
```
# Создать папку для тестов
mkdir tests

# Создать файл теста
cat > tests/test1.cpp <<EOF
#include <print.hpp>
#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
    std::string filepath = "file.txt";
    std::string text = "hello";
    std::ofstream out{filepath};

    print(text, out);
    out.close();

    std::string result;
    std::ifstream in{filepath};
    in >> result;

    EXPECT_EQ(result, text);
}
EOF
```
## Шаг 6 - сборка и запуск тестов  
Сгенерируем систему сборки CMake с включённой опцией BUILD_TESTS=ON, 
скомпилируем проект и запустил тесты через целевую задачу test, убедившись, что все проверки проходят успешно.  
```
# Сгенерировать сборку с включёнными тестами
cmake -H. -B_build -DBUILD_TESTS=ON

# Собрать проект
cmake --build _build

# Запустить тесты
cmake --build _build --target test

# Подробный вывод тестов
cmake --build _build --target test -- ARGS=--verbose
```  
*Тесты прошли успешно.*  
  
## Шаг 7 - настройка Github Actions  
Создадим файл конфигурации .github/workflows/ci.yml, который автоматически собирает проект, 
запускает тесты и загружает артефакты при каждом пуше в репозиторий, заменив устаревшую систему Travis CI на современное решение от GitHub.  
```mkdir -p .github/workflows

cat > .github/workflows/ci.yml <<EOF
name: CI


