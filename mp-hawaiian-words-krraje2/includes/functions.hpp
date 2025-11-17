#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <string>

std::string PhoneticPronunciation(std::string str);
std::string Lowercase(std::string word);
char DashRules(std::string str, int pos);
std::string WRules(std::string word, int pos);
std::string ARules(std::string word, int pos);
std::string ERules(std::string word, int pos);
std::string IRules(std::string word, int pos);
std::string ORules(std::string word, int pos);
std::string URules(std::string word, int pos);
std::string NotValid(std::string& str, char c);
int APos(std::string str, int pos);
#endif