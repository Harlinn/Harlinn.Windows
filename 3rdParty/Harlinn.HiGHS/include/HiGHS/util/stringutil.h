/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Written and engineered 2008-2024 by Julian Hall, Ivet Galabova,    */
/*    Leona Gottwald and Michael Feldmeier                               */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <ctype.h>

#include <cstring>
#include <string>

#include "highs_export.h"

/*
void strRemoveWhitespace(char* str);
char* strClone(const char* str);
int strIsWhitespace(const char* str);
void strToLower(char* str);
void strTrim(char* str);
*/
// std::string& str_tolower(std::string s);

HIGHS_EXPORT void tolower(std::string& str);

const std::string non_chars = "\t\n\v\f\r ";
HIGHS_EXPORT std::string& ltrim(std::string& str, const std::string& chars = non_chars);
HIGHS_EXPORT std::string& rtrim(std::string& str, const std::string& chars = non_chars);
HIGHS_EXPORT std::string& trim(std::string& str, const std::string& chars = non_chars);

HIGHS_EXPORT bool is_empty(std::string& str, const std::string& chars = non_chars);
HIGHS_EXPORT bool is_empty(char c, const std::string& chars = non_chars);
HIGHS_EXPORT bool is_end(std::string& str, size_t end, const std::string& chars = non_chars);

// todo: replace with pair of references rather than string ret value to avoid
// copy and also using function below. or do it properly with iterators.
HIGHS_EXPORT std::string first_word(std::string& str, size_t start);
HIGHS_EXPORT size_t first_word_end(std::string& str, size_t start);

#endif