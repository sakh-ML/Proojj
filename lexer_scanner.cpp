#include <iostream>
#include <string>

// int x = 5; 5 + 7 ---->
enum TokenType{
	INT,
	IDENTIFIER,
	ASSIGN,
	SEMICOLON,
	PLUS
};

struct Token{
	TokenType type;
	std::string value_of_token;
};

class Scanner{};

int main(){ 

std::cout << "Hello" << std::endl;

	return 0;
}
