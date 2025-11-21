#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main(){
    std::ifstream f("part1.txt");
    std::set<std::string> words;


    std::string line;
    while(getline(f, line)){
        if(words.find(line) == words.end()){
            words.insert(line);
        }
    }

    f.close();

    std::cout << "This is your list of words in alphabetical order: " << std::endl;
    for(std::string word : words){
        std::cout << word << std::endl;
    }

    return 0;
}