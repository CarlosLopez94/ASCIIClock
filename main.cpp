#include <iostream>
#include <string>
#include <list>
#include <map>

//Declare methods
std::map<std::string, std::list<std::string>> loadDictionaryASCII();
void printTimeASCII();

int main(){
    //Init Load ASCII Dictionary
    std::map<std::string, std::list<std::string>> dictionaryASCII = loadDictionaryASCII();

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

std::map<std::string, std::list<std::string>> loadDictionaryASCII(){
    std::map<std::string, std::list<std::string>> dictionary;
}

void printTimeASCII(){

}
