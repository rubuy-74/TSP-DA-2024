#ifndef PARSER_H_
#define PARSER_H_

#include <vector>
#include <string>
#include <list>

class Parser {
   public:
      std::vector<std::string> split(std::string line, const std::string &delimiter);
      std::list<std::vector<std::string>> readFile(const std::string &path, const bool pop);
};

#endif