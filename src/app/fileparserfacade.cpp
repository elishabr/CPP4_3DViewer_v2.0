#include "fileparserfacade.h"

#include <iostream>

s21::FileHandler::FileHandler(const std::string& filePath) {
  file.open(filePath, std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filePath;
  }
}

s21::FileHandler::~FileHandler() {
  if (file.is_open()) {
    file.close();
  }
}

s21::Parser::Parser() : mRegex(R"((\S+)\s+)") {}
s21::Parser::~Parser() {}

std::vector<float> s21::Parser::parseLine(const std::string& line) {
  std::vector<float> result;
  const std::vector<std::smatch> matches{
      std::sregex_iterator{line.begin(), line.end(), mRegex},
      std::sregex_iterator{}};
  if (matches.empty()) return result;
  if (matches[0].str(1) == "v" || matches[0].str(1) == "f") {
    for (const std::smatch& i : matches) {
      if (i.str(1) == "v") continue;
      if (i.str(1) == "f") continue;
      result.push_back(std::stof(i.str(1)));
    }
  }
  return result;
}

s21::FileParserFacade::FileParserFacade(const std::string& filePath)
    : mFileHandler(filePath), mParser() {}
s21::FileParserFacade::~FileParserFacade() {}

const std::vector<float>& s21::FileParserFacade::getVertexes() {
  return mVertexes;
}

const std::vector<unsigned int>& s21::FileParserFacade::getIndexes() {
  return mIndexes;
}

bool s21::FileParserFacade::processFile() {
  mVertexes.clear();
  mIndexes.clear();
  if (mFileHandler.file.is_open()) {
    std::vector<float> result;
    std::string line;
    while (getline(mFileHandler.file, line)) {
      line += ' ';
      if (line[0] == 'v') {
        if (!(result = mParser.parseLine(line)).empty()) {
          mVertexes.push_back(result[0]);
          mVertexes.push_back(result[1]);
          mVertexes.push_back(result[2]);
          mVertexCaunt++;
        }
      }
      if (line[0] == 'f') {
        if (!(result = mParser.parseLine(line)).empty()) {
          mIndexes.push_back(result[0] > 0 ? result[0] - 1
                                           : mVertexCaunt + result[0]);
          for (size_t i = 1; i < result.size(); i++) {
            mIndexes.push_back(result[i] > 0 ? result[i] - 1
                                             : mVertexCaunt + result[i]);
            mIndexes.push_back(result[i] > 0 ? result[i] - 1
                                             : mVertexCaunt + result[i]);
          }
          mIndexes.push_back(result[0] > 0 ? result[0] - 1
                                           : mVertexCaunt + result[0]);
        }
      }
    }
    normalizeCoords(mVertexes);
    mFileHandler.file.clear();                  // Сброс флага eof
    mFileHandler.file.seekg(0, std::ios::beg);  // Возврат к началу файла
    return true;
  }
  return false;
}

int s21::FileParserFacade::getVertexCaunt() const { return mVertexCaunt; }

void s21::FileParserFacade::normalizeCoords(std::vector<float>& coords) {
  // Найдем минимальные и максимальные значения
  float minX = *std::min_element(coords.begin(), coords.end());
  float maxX = *std::max_element(coords.begin(), coords.end());

  // Вычислим коэффициенты масштабирования
  float scale = 2.0f / (maxX - minX);
  float offset = -0.5f * (maxX + minX) * scale;

  for (std::vector<float>::iterator it = coords.begin(); it != coords.end();
       ++it) {
    *it = *it * scale + offset;
  }
}
