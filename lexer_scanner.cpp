#include <iostream>
#include <unordered_set>

bool is_whitesapce(char c){
	if(c == '\n' || c == '\t' || c == '\r' || c == ' '){
		return true;
	}
	return false;
}

std::unordered_set<std::string> operators = {"+", "-", "*", "/", "%","<", ">", "<=", ">=", "!=", "=="};

bool is_operator(char c){
	std::string str(1,c);
	if(operators.count(str) > 0){
		return true;
	}
	else{
		return false;
	}
}



// i have to build the enum and the token class


//make all the helper functions !! that check if somethign somethign is !!.




// then i have to make the heleor function that scann if somethign really something else like by iterare from start to end



// i have to make the class scanner than the last function


int main(){

	std::cout << "Hello" << std::endl;

	return 0;
}
