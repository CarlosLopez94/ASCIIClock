#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

//Declare methods
std::map<std::string, std::vector<std::string>> loadDictionaryASCII(std::string dictionaryPath);
std::vector<std::string> readFile(std::string filePath);
void printTimeASCII();

int main(){
    //Init Load ASCII Dictionary
    std::map<std::string, std::vector<std::string>> dictionaryASCII = loadDictionaryASCII("./Dictionary");

    readFile("./DictionaryASCII/Number0.txt");
    int cont=10;
    while(cont!=0){
        //Get current hour

        //Print current hour
        printTimeASCII();

        //clean screen


        cont--;
    }

    printf("finish");
    return 0;
}

std::map<std::string, std::vector<std::string>> loadDictionaryASCII(std::string dictionaryDirectoryPath){
    //inits map
    std::map<std::string, std::vector<std::string>> dictionary;
   
   //read all files from dictionary directory
  
    //dictionary.insert()
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
            std::cout<<currentLine<<std::endl;
        }
        fileStream.close();
        printf("File '%s' loaded successfully\n", filePath.c_str());
    } else {
			printf("Unable to open '%s' file\n", filePath.c_str());
	}

    return fileContent;
}

void printTimeASCII(){

}
