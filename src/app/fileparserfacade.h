#ifndef FILEPARSERFACADE_H
#define FILEPARSERFACADE_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>

namespace s21 {
class FileHandler {
 public:
  FileHandler(const std::string& filePath);
  ~FileHandler();
  std::fstream file;
};

class Parser {
 public:
  Parser();
  ~Parser();
  std::vector<float> parseLine(const std::string& line);

 private:
  const std::regex mRegex;
};

class FileParserFacade {
 public:
  FileParserFacade(const std::string& filePath);
  ~FileParserFacade();
  const std::vector<float>& getVertexes();
  const std::vector<unsigned int>& getIndexes();
  bool processFile();
  int getVertexCaunt() const;

 private:
  void normalizeCoords(std::vector<float>& coords);
  FileHandler mFileHandler;
  Parser mParser;
  std::vector<float> mVertexes;
  std::vector<unsigned int> mIndexes;
  int mVertexCaunt = 0;
};
}  // namespace s21
#endif  // FILEPARSERFACADE_H
