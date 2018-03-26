#include <iostream>
#include <sstream>
#include "big_n.h"
#include "big_z.h"
#include "big_q.h"
#include "big_p.h"

void test_all();

namespace API{
	
template<class T>
void result_int_nat(T a, std::string op, T b){
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

void result_fra(BigFra a, std::string op, BigFra b){
	BigFra result;
	if(op == "+"){
		result = a + b;
		std::cout << result << "=" << result.to_float(5);
	}else if(op == "-"){
		result = a - b;
		std::cout << result << "=" << result.to_float(5);
	}else if(op == "*"){
		result = a * b;
		std::cout << result << "=" << result.to_float(5);
	}else if(op == "/"){
		result = a / b;
		std::cout << result << "=" << result.to_float(5);
	}
}

void result_pol(BigPol a, std::string op, BigPol b){
	if(op == "+"){
		std::cout << a + b;	
	}else if(op == "-"){
		std::cout << a - b;
	}else if(op == "*"){
		std::cout << a * b;
	}
}

int parse_args(int argc, char *argv[]){
	if(argc == 1){
		std::cout << "Use --test or API with such format: 'FILENAME.EXE TYPE NUM1 OPERATOR NUM2'.\n";
		std::cout << "---------------\n";
		std::cout << "TYPE can be one from (N, I, F, P).\n";
		std::cout << "NUM1 and NUM2 will go to strign constructors for needed format.\n"; 
		std::cout << "OPERATOR is usual in use, except for unary operators, even if it's unary, NUM2 must be something correct.";
		
		char temp;
		std::cin >> std::noskipws >> temp;
		
		return 0;
	}
	
	std::string type(argv[1]);
	
	if(type == "--test"){
		test_all();
		return 0;
	}
	
	if(type == "N" || type == "I"){
		std::string num1(argv[2]);
		std::string op(argv[3]);
		std::string num2(argv[4]);
		
		if(type == "N"){
	
			BigNat a(num1), b(num2);
			result_int_nat(a, op, b);
		
		}else if(type == "I"){
			
			BigInt a(num1), b(num2);
			
			result_int_nat(a, op, b);
			
		}
		
	}else if(type == "F"){
		std::string num1(argv[2]), denom1(argv[3]);
		std::string op(argv[4]);
		std::string num2(argv[5]), denom2(argv[6]);
		
		BigFra a(num1, denom1), b(num2, denom2);
		result_fra(a, op, b);
		
	}else if(type == "P"){
		std::string all_args = "";
		
		for(int i = 1; i < argc; i++){
			all_args += argv[i];
			all_args += " ";
		}
		
		std::stringstream ss(all_args);
		
		std::string pol_str1 = "";
		std::string pol_str2 = "";
		std::string op;
		
		//skip type P;
		ss >> op;
		op = "";
		
		std::string temp;
		while(ss >> temp){
			if(temp == "+" || temp == "-" || temp == "*"){
				op = temp;
				break;
			}
			pol_str1 += temp;
			pol_str1 += " ";
		}
	
		while(ss >> temp){
			pol_str2 += temp;
			pol_str2 += " ";
		}


		BigPol a(pol_str1);
		BigPol b(pol_str2);
		
		
		result_pol(a, op, b);
		
	}else{
		std::cout << "UNKNOWN TYPE";
	}
	
	return 0;
}

}
