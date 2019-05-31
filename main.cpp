#include <dirent.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// Declare methods
std::map<std::string, std::vector<std::string>> loadDictionaryASCII(
    std::string dictionaryPath);
std::vector<std::string> readFile(std::string filePath);
void printTimeASCII(std::map<std::string, std::vector<std::string>> &dictionary,
                    std::string currentTime);

int main() {
  // Init Load ASCII Dictionary
  std::map<std::string, std::vector<std::string>> dictionaryASCII =
      loadDictionaryASCII("./DictionaryASCII/");

  bool end = false;
  std::string currentTime = "";
  while (!end) {
    // Get current hour
    currentTime = "000";
    // Print current hour
    printTimeASCII(dictionaryASCII, currentTime);

    // clean screen

    end = true;
  }

  return 0;
}

std::map<std::string, std::vector<std::string>> loadDictionaryASCII(
    std::string dictionaryDirectoryPath) {
  // inits map
  std::map<std::string, std::vector<std::string>> dictionary;

  // Read Dictionary folder content
  DIR *dp;
  struct dirent *ep;
  dp = opendir("./DictionaryASCII/");

  if (dp != NULL) {
    while (ep = readdir(dp)) {
      std::string fileName = ep->d_name;
      std::string filePath = dictionaryDirectoryPath + "/" + fileName;
      std::vector<std::string> currentFileContent = readFile(filePath);
      dictionary.insert(std::pair<std::string, std::vector<std::string>>(
          fileName, currentFileContent));
    }
    (void)closedir(dp);

  } else {
    perror("Couldn't open the directory");
  }

  return dictionary;
}

std::vector<std::string> readFile(std::string filePath) {
  std::vector<std::string> fileContent;
  std::ifstream fileStream;

  fileStream.open(filePath);
  printf("Loading '%s'\n", filePath.c_str());
  std::string currentLine;
  if (fileStream.is_open()) {
    while (std::getline(fileStream, currentLine)) {
      fileContent.push_back(currentLine);
    }
    fileStream.close();
    printf("File '%s' loaded successfully\n", filePath.c_str());
  } else {
    printf("Unable to open '%s' file\n", filePath.c_str());
  }
  return fileContent;
}

void printTimeASCII(std::map<std::string, std::vector<std::string>> &dictionary,
                    std::string currentTime) {
  // Get length of each letter
  int letterLength = dictionary.begin()->second.size();

  std::string line;
  for (int i = 0; i < letterLength; i++) {
    line = "";
    for (char &c : currentTime) {
      line += dictionary.find("e")->second.at(i);
    }
    printf("%s\n", line.c_str());
  }
}