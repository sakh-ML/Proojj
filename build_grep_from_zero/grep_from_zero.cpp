#include <stdio.h>
#include <iostream>
#include <fstream> 
#include <vector>

bool find_pattern_in_line(std::string line, std::string pattern){

    if(pattern.length() == 1){
        for(int i = 0; i < line.length(); ++i){
            if(line[i] == pattern[0]){
                return true;
            }
        }
    }

    return false;
}

std::vector<std::string> pattern_matching(std::string pattern, std::string file_name){

    std::ifstream file(file_name);
    std::vector<std::string> result;

	if(!file){
		std::cerr << "Die Datei könnte nicht geöffnet werden !!, bitte Geben Sie eine Datei ein.";
        return result;
	}
    
    if (pattern.length() == 1){

       std::string line;

       while(std::getline(file, line)){
           if(find_pattern_in_line(line, pattern)){
            std::cout << line << std::endl;
            result.push_back(line);
           }

        }   
    }
    
    return result;
}


int main(int argc, char* argv[]){

	if(argc < 3){
		std::cerr << "Fehler, bitte geben Sie suchmuster und Dateiname ein";
        return -1;
	}

	std::string pattern = argv[1];
	std::string file_name = argv[2];

	pattern_matching(pattern, file_name);
	
	return 0;
}
