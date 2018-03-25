#include <iostream>

#include "include/big_n.h"
#include "include/big_z.h"
#include "include/big_q.h"


int parse_args(int argc, char *argv[]){
	std::string type(argv[1]);
	
	if(type == "N" || type == "I"){
		std::string num1(argv[2]);
		std::string op(argv[3]);
		std::string num2(argv[4]);
		
		if(type == "N"){
	
			BigNat a(num1), b(num2);
			
			if(op == "+"){
				std::cout << a + b;	
			}else if(op == "-"){
				std::cout << a - b;
			}else if(op == "*"){
				std::cout << a * b;
			}else if(op == "/"){
				std::cout << a / b;
			}else if(op == "%"){
				std::cout << a % b;
			}
		
		}else if(type == "I"){
			
			BigInt a(num1), b(num2);
			
			if(op == "+"){
				std::cout << a + b;	
			}else if(op == "-"){
				std::cout << a - b;
			}else if(op == "*"){
				std::cout << a * b;
			}else if(op == "/"){
				std::cout << a / b;
			}else if(op == "%"){
				std::cout << a % b;
			}
	
		}
	}else if(type == "F"){
		std::string num1(argv[2]);
		std::string denom1(argv[3]);
		std::string op(argv[4]);
		std::string num2(argv[5]);
		std::string denom2(argv[6]);
		
		BigFra a(num1, denom1), b(num2, denom2);
		
		if(op == "+"){
			BigFra result = a + b;
			std::cout << result << "=" << result.to_float(5);
		}else if(op == "-"){
			BigFra result = a - b;
			std::cout << result << "=" << result.to_float(5);
		}else if(op == "*"){
			BigFra result = a * b;
			std::cout << result << "=" << result.to_float(5);
		}else if(op == "/"){
			BigFra result = a / b;
			std::cout << result << "=" << result.to_float(5);
		}
		
	}else if(type == "P"){
		//Missing part
	}else{
		std::cout << "UNKNOWN TYPE";
	}
	
	return 0;
}
