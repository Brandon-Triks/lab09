# Лабораторная работа №9
## Шаг 1: Подготовка окружения и репозитория
Аналогично прошлым лабораторным работам, задаем переменные окружения и копируем репозиторий lab08 в качестве основы для lab09.
```bash
export GITHUB_USERNAME=Brandon-Triks
export GITHUB_EMAIL=p0strelov@yandex.ru
export PACKAGE_MANAGER="sudo apt-get"
export GPG_PACKAGE_NAME=gnupg

```

Переходим в рабочую директорию, клонируем и настраиваем структуру lab09:
```bash
cd ~/Brandon-Triks/workspace/projects/
git clone https://github.com/${GITHUB_USERNAME}/lab08 lab09
cd lab09
git remote set-url origin https://github.com/${GITHUB_USERNAME}/lab09.git

```

## Шаг 2: Установка GPG и генерация ключей подписи
Устанавливаем утилиту для работы с ключами шифрования и проверяем список существующих секретных ключей.
```bash
$PACKAGE_MANAGER install ${GPG_PACKAGE_NAME}
gpg --list-secret-keys --keyid-format LONG

```
*Вывод команды:*
```
gpg: создан щит с ключами '/home/igor/.gnupg/pubring.kbx'
gpg: /home/igor/.gnupg/trustdb.gpg: создана таблица доверия

```
Запускаем процесс интерактивной генерации нового ключа. Выбираем тип RSA and RSA, длину 4096 бит, срок действия — неограничен, и вводим свои данные (имя и Email, привязанный к GitHub):
```bash
gpg --full-generate-key

```
*Вывод команды:*
```
gpg (GnuPG) 2.4.7; Copyright (C) 2024 g10 Code GmbH
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Выберите тип ключа:
   (1) RSA and RSA
   (2) DSA and Elgamal
   (3) DSA (sign only)
   (4) RSA (sign only)
   (9) ECC (sign and encrypt) *default*
  (10) ECC (только для подписи)
  (14) Existing key from card
Ваш выбор? 1
длина ключей RSA может быть от 1024 до 4096.
Какой размер ключа Вам необходим? (3072) 4096
Запрошенный размер ключа - 4096 бит
Выберите срок действия ключа.
         0 = не ограничен
      <n>  = срок действия ключа - n дней
      <n>w = срок действия ключа - n недель
      <n>m = срок действия ключа - n месяцев
      <n>y = срок действия ключа - n лет
Срок действия ключа? (0) 0
Срок действия ключа не ограничен
Все верно? (y/N) N
Срок действия ключа? (0) 0
Срок действия ключа не ограничен
Все верно? (y/N) y

GnuPG должен составить идентификатор пользователя для идентификации ключа.

Ваше полное имя: Brandon-Triks
Адрес электронной почты: p0strelov@yandex.ru
Примечание: MyKey
Вы выбрали следующий идентификатор пользователя:
    "Brandon-Triks (MyKey) <p0strelov@yandex.ru>"

Сменить (N)Имя, (C)Примечание, (E)Адрес; (O)Принять/(Q)Выход? O
Необходимо получить много случайных чисел. Желательно, чтобы Вы
в процессе генерации выполняли какие-то другие действия (печать
на клавиатуре, движения мыши, обращения к дискам); это даст генератору
случайных чисел больше возможностей получить достаточное количество энтропии.
gpg: создан каталог '/home/igor/.gnupg/openpgp-revocs.d'
gpg: сертификат отзыва записан в '/home/igor/.gnupg/openpgp-revocs.d/7862D389B27984A65A297719349FE00244AFA43D.rev'.
открытый и секретный ключи созданы и подписаны.

pub   rsa4096 2026-06-06 [SC]
      7862D389B27984A65A297719349FE00244AFA43D
uid                      Brandon-Triks (MyKey) <p0strelov@yandex.ru>
sub   rsa4096 2026-06-06 [E]

```
Проверяем успешность создания ключа и выводим информацию в длинном формате:
```bash
gpg --list-secret-keys --keyid-format LONG
gpg -K ${GITHUB_USERNAME}

```
*Вывод команды:*
```
gpg: проверка таблицы доверия
gpg: marginals needed: 3  completes needed: 1  trust model: pgp
gpg: глубина: 0  достоверных:   1  подписанных:   0  доверие: 0-, 0q, 0n, 0m, 0f, 1u
/home/igor/.gnupg/pubring.kbx
-----------------------------
sec   rsa4096/349FE00244AFA43D 2026-06-06 [SC]
      7862D389B27984A65A297719349FE00244AFA43D
uid               [  абсолютно ] Brandon-Triks (MyKey) <p0strelov@yandex.ru>
ssb   rsa4096/783E842E25B6733F 2026-06-06 [E]


sec   rsa4096 2026-06-06 [SC]
      7862D389B27984A65A297719349FE00244AFA43D
uid         [  абсолютно ] Brandon-Triks (MyKey) <p0strelov@yandex.ru>
ssb   rsa4096 2026-06-06 [E]

```
## Шаг 3: Экспорт ключа и связывание с аккаунтом GitHub
Автоматически вырезаем идентификаторы созданного публичного и секретного ключей из вывода утилиты gpg и сохраняем их в переменные окружения.
```bash
GPG_KEY_ID=$(gpg --list-secret-keys --keyid-format LONG | grep ssb | tail -1 | awk '{print $2}' | awk -F'/' '{print $2}')
GPG_SEC_KEY_ID=$(gpg --list-secret-keys --keyid-format LONG | grep sec | tail -1 | awk '{print $2}' | awk -F'/' '{print $2}')

```

Экспортируем публичный ключ в текстовом (armor) формате, чтобы добавить его в настройки профиля на GitHub:
```bash
gpg --armor --export ${GPG_KEY_ID}

```
*Вывод команды:*
```
-----BEGIN PGP PUBLIC KEY BLOCK-----

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
eVrkepi5VQ==
=r+G/
-----END PGP PUBLIC KEY BLOCK-----
```
Открываем страницу управления ключами GitHub в браузере и привязываем скопированный ключ:
```bash
open https://github.com/settings/keys
```
<img width="670" height="256" alt="image" src="https://gist.github.com/user-attachments/assets/9085ebc9-d835-4c5a-9b50-e0b0a3f025c2" />

## Шаг 4: Настройка локального Git для автоматической подписи
Прописываем сгенерированный секретный ключ в конфигурацию Git и указываем использовать системный gpg для подписи всех коммитов и тегов.
```bash
git config user.signingkey ${GPG_SEC_KEY_ID}
git config gpg.program gpg
git config commit.gpgsign true

```

## Шаг 5: Контроль целостности кода библиотеки
Чтобы исправить ошибку компиляции no match for operator<< при сборках, принудительно перезаписываем sources/print.cpp, добавляя недостающий заголовочный файл <fstream>.
```bash
cat > sources/print.cpp <<EOF
#include "print.hpp"
#include <fstream>
#include <iostream>

void print(const std::string& text, std::ostream& out) {
  out << text;
}

void print(const std::string& text, std::ofstream& out) {
  out << text;
}
EOF

```

## Шаг 6: Фиксация изменений и отправка подписанного коммита
Создаем правильный файл .gitignore (без опечаток), добавляем измененные файлы в индекс и отправляем коммит, который теперь автоматически подпишется GPG-ключом.
```bash
cat > .gitignore <<EOF
_builds/
_builds_artifacts/
_logs/
doxygen_output/
.hunter/
EOF

```

Фиксируем изменения и отправляем код в основную ветку


```bash
git branch -M main
git add sources/print.cpp .gitignore
git commit -m "build: setup gpg signing for verification"
git push -u origin main

```
*Вывод команды:*
```
Username for 'https://github.com': Brandon-Triks
Password for 'https://Brandon-Triks@github.com': 
Перечисление объектов: 249, готово.
Подсчет объектов: 100% (249/249), готово.
При сжатии изменений используется до 2 потоков
Сжатие объектов: 100% (137/137), готово.
Запись объектов: 100% (249/249), 2.74 МиБ | 5.46 МиБ/с, готово.
Total 249 (delta 79), reused 243 (delta 77), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (79/79), done.
To https://github.com/Brandon-Triks/lab09.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```
