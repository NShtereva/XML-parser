#ifndef __HELPER_HPP
#define __HELPER_HPP

#include <iostream>

unsigned int numberOfDigits(unsigned int num);

char* toString(unsigned int num);
unsigned int toNumber(const char* str);

void processTheIndentation(std::ostream& out, unsigned int level);

void inLowerCase(char*& str);

bool isValidFileName(const char* fileName);

bool isWhiteSpace(char a);

#endif
