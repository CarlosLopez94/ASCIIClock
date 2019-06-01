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

const std::string DICTIONARIES_PATH = "./ASCIIDictionaries/";
const std::string TXT_FORMAT = ".txt";
const std::string COLON_CHARACTER = ":";
const std::string COLON_FILE_NAME = "Colon";

// Declare methods
std::vector<std::string> getFilesOnDirectory(std::string directoryPath);

std::string getChoosedDictionaryPath();
std::map<std::string, std::vector<std::string>> loadDictionaryASCII(
    std::string dictionaryPath);
std::vector<std::string> readFile(std::string filePath);
std::string getCurrentTimeString();
void printTimeASCII(std::map<std::string, std::vector<std::string>> &dictionary,
                    std::string currentTime);

int main() {
  // Choose dictionaryPath
  std::string dictionaryPath = getChoosedDictionaryPath();

  // Init Load ASCII Dictionary
  std::map<std::string, std::vector<std::string>> dictionaryASCII =
      loadDictionaryASCII(dictionaryPath);

  std::string currentTime = "";

  // Wait until user input
  printf("\nPresh 'Enter' to Start!!\n");
  std::cin.clear();
  fflush(stdin);
  std::cin.get();  // waits for 'Enter' key

  // Initinite loop, Starts execution
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

std::vector<std::string> getFilesOnDirectory(std::string directoryPath) {
  std::vector<std::string> files;
  DIR *dp;
  struct dirent *ep;
  dp = opendir(directoryPath.c_str());

  if (dp != NULL) {
    while (ep = readdir(dp)) {
      std::string fileName = ep->d_name;
      // Remove 'currentDirectory' and 'ParentDirectory' from the list
      if (fileName.compare(".") != 0 && fileName.compare("..") != 0) {
        std::cout << fileName << std::endl;
        // save the filenames
        files.push_back(fileName);
      }
    }
    (void)closedir(dp);
  } else {
    perror("Couldn't open the directory");
  }

  return files;
}

std::string getChoosedDictionaryPath() {
  std::string dictionaryPath;

  std::vector<std::string> dictionaries =
      getFilesOnDirectory(DICTIONARIES_PATH);

  do {
    printf("Choose your Dictionary:\n");
    for (int i = 0; i < dictionaries.size(); i++) {
      printf("[%d] %s\n", i, dictionaries[i].c_str());
    }
    int choosedDictionary;
    std::cin >> choosedDictionary;
    if (choosedDictionary >= 0 && choosedDictionary < dictionaries.size()) {
      dictionaryPath = "./";
      dictionaryPath += DICTIONARIES_PATH;
      dictionaryPath += "/";
      dictionaryPath += dictionaries[choosedDictionary].c_str();
      dictionaryPath += "/";

      std::cout << "path: " << dictionaryPath;
    } else {
      printf(
          "'%d' IS NOT a possible value... Try again with a number from 0 to "
          "%d.\n",
          choosedDictionary, dictionaries.size() - 1);
    }
  } while (dictionaryPath.size() < 1);

  return dictionaryPath;
}

std::map<std::string, std::vector<std::string>> loadDictionaryASCII(
    std::string dictionaryDirectoryPath) {
  // inits map
  std::map<std::string, std::vector<std::string>> dictionary;

  // Read Dictionary folder content
  std::vector<std::string> dictionaryFiles =
      getFilesOnDirectory(dictionaryDirectoryPath);

  for (std::string fileName : dictionaryFiles) {
    std::string filePath = dictionaryDirectoryPath + fileName;
    // Get file content

    std::vector<std::string> currentFileContent = readFile(filePath);

    // insert into map
    int txtFormatPosition = fileName.find(TXT_FORMAT);
    fileName = fileName.substr(0, txtFormatPosition);

    if (fileName.compare(COLON_FILE_NAME) == 0) {
      fileName = COLON_CHARACTER;
    }

    dictionary.insert(std::pair<std::string, std::vector<std::string>>(
        fileName, currentFileContent));
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
  // int day = aTime->tm_mday;
  // int month = aTime->tm_mon +1; // Month is 0 – 11, add 1 to get 1-12
  // int year = aTime->tm_year + 1900;  // Year starts at 1900
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

      line.append(dictionary.find(charAsString)->second[i]);
    }
    printf("%s\n", line.c_str());
  }
}