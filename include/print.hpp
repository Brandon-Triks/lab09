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
