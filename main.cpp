#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

//Declare methods
std::map<std::string, std::vector<std::string>> loadDictionaryASCII(std::string dictionaryPath);
std::vector<std::string> readFile(std::string filePath);
void printTimeASCII(std::map<std::string, std::vector<std::string>>& dictionary, std::string currentTime);

int main(){
    //Init Load ASCII Dictionary
    std::map<std::string, std::vector<std::string>> dictionaryASCII = loadDictionaryASCII("./Dictionary");

    int cont=10;
    std::string currentTime = "";
    while(cont!=0){
        //Get current hour
        currentTime = "000";
        //Print current hour
        printTimeASCII(dictionaryASCII, currentTime);

        //clean screen


        cont--;
    }

    printf("finish");
    return 0;
}

std::map<std::string, std::vector<std::string>> loadDictionaryASCII(std::string dictionaryDirectoryPath){
    //inits map
    std::map<std::string, std::vector<std::string>> dictionary;
   
   //TODO - read all files from dictionary directory
    std::vector<std::string> currentFileContent = readFile("./DictionaryASCII/Number0.txt");

    dictionary.insert(std::pair<std::string, std::vector<std::string>>("e", currentFileContent));
    return dictionary;
}


std::vector<std::string> readFile(std::string filePath){
    std::vector<std::string> fileContent;
    std::ifstream fileStream;

    fileStream.open(filePath);
    printf("Loading '%s'\n", filePath.c_str());
    std::string currentLine;
    if(fileStream.is_open()){
        while(std::getline(fileStream, currentLine)){
            fileContent.push_back(currentLine);
        }
        fileStream.close();
        printf("File '%s' loaded successfully\n", filePath.c_str());
    } else {
			printf("Unable to open '%s' file\n", filePath.c_str());
	}
    return fileContent;
}

void printTimeASCII(std::map<std::string, std::vector<std::string>>& dictionary, std::string currentTime){
    //Get length of each letter
    int letterLength = dictionary.begin()->second.size();

    std::string line;
    for (int i = 0; i < letterLength; i++){
        line = "";
        for(char& c : currentTime) {
            line+= dictionary.find("e")->second.at(i);
        }
        printf("%s\n", line.c_str());
    }
}