#include <conio.h>
#include <dirent.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

const std::string COLON_CHARACTER = ":";
const std::string COLON_FILE_NAME = "Colon";

// Declare methods
std::map<std::string, std::vector<std::string>> loadDictionaryASCII(
    std::string dictionaryPath);
std::vector<std::string> readFile(std::string filePath);
std::string getCurrentTimeString();
void printTimeASCII(std::map<std::string, std::vector<std::string>> &dictionary,
                    std::string currentTime);

int main() {
  // Init Load ASCII Dictionary
  std::map<std::string, std::vector<std::string>> dictionaryASCII =
      loadDictionaryASCII("./DictionaryASCII/");

  std::string currentTime = "";

  while (true) {
    // Get current hour
    currentTime = getCurrentTimeString();

    // clean screen
    system("CLS");

    // Print current hour
    printTimeASCII(dictionaryASCII, currentTime.c_str());

    // Sleps for 1 second
    sleep(1);
  }

  return 0;
}

std::map<std::string, std::vector<std::string>> loadDictionaryASCII(
    std::string dictionaryDirectoryPath) {
  // inits map
  std::map<std::string, std::vector<std::string>> dictionary;
  const std::string TXT_FORMAT = ".txt";

  // Read Dictionary folder content
  DIR *dp;
  struct dirent *ep;
  dp = opendir(dictionaryDirectoryPath.c_str());

  if (dp != NULL) {
    while (ep = readdir(dp)) {
      std::string fileName = ep->d_name;
      int txtFormatPosition = fileName.find(TXT_FORMAT);
      if (txtFormatPosition != -1) {
        std::string filePath = dictionaryDirectoryPath + fileName;

        // Get file content
        std::vector<std::string> currentFileContent = readFile(filePath);

        // insert into map
        fileName = fileName.substr(0, txtFormatPosition);

        if (fileName.compare(COLON_FILE_NAME) == 0) {
          fileName = COLON_CHARACTER;
        }

        dictionary.insert(std::pair<std::string, std::vector<std::string>>(
            fileName, currentFileContent));
      }
    }
    (void)closedir(dp);

  } else {
    perror("Couldn't open the directory");
  }
  // return map
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

std::string getCurrentTimeString() {
  // Gets current time
  time_t theTime = time(NULL);
  struct tm *aTime = localtime(&theTime);

  // Splits time
  int day = aTime->tm_mday;
  int month = aTime->tm_mon +
              1;  // Month is 0 – 11, add 1 to get a jan-dec 1-12 concept
  int year = aTime->tm_year + 1900;  // Year is # years since 1900
  // Parse string
  std::string hour = std::to_string(aTime->tm_hour);
  std::string min = std::to_string(aTime->tm_min);
  std::string sec = std::to_string(aTime->tm_sec);

  // Adds a 0 to the left in case there is only one digit
  if (hour.size() == 1) {
    hour = '0' + hour;
  }
  if (min.size() == 1) {
    min = '0' + min;
  }
  if (sec.size() == 1) {
    sec = '0' + sec;
  }

  // Concats the final time
  std::string stringTime;
  stringTime.append(hour)
      .append(COLON_CHARACTER)
      .append(min)
      .append(COLON_CHARACTER)
      .append(sec);

  return stringTime;
}

void printTimeASCII(std::map<std::string, std::vector<std::string>> &dictionary,
                    std::string currentTime) {
  // Get length of each letter
  int letterLength = dictionary.begin()->second.size();

  std::string line;
  //
  for (int i = 0; i < letterLength; i++) {
    line = "";
    for (int j = 0; j < currentTime.size(); j++) {
      std::string charAsString;
      charAsString.push_back(currentTime[j]);

      // std::cout << dictionary.find(charAsString)->first << "  -->  "

      //         << dictionary.find(charAsString)->second[i] << std::endl;
      line.append(dictionary.find(charAsString)->second[i]);
    }
    printf("%s\n", line.c_str());
  }
}