#include "Parser.h"
#include <fstream>

std::vector<std::string> Parser::split(std::string line, const std::string &delimiter){
   size_t pos;
   std::string token;
   std::vector<std::string> result;
   while(line.find(delimiter) != std::string::npos) {
      pos = line.find(delimiter);
      token = line.substr(0,pos);
      result.push_back(token);
      line = line.substr(pos + delimiter.length());
   }
   result.push_back(line.substr(0));
   return result;
}


std::list<std::vector<std::string> > Parser::readFile(const std::string &path, const bool pop) {
   std::ifstream file(path);
   std::string line;
   std::list<std::vector<std::string>> result;
   while (getline(file,line)) {
       line = line.substr(0,line.length());
       result.push_back(split(line,","));
   }
   file.close();
   if(pop) result.pop_front();
   return result;
}