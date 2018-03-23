#include <iostream>
//#include <windows.h>
#include "include/big_n.h"
#include "include/big_z.h"

int main(){
	std::string a, b;
	
	std::cin >> a >> b;
	
	BigInt temp1(a), temp2(b);
	
	std::cout << temp1 + temp2 << "\n";
	std::cout << temp1 - temp2 << "\n";
	std::cout << temp1 * temp2 << "\n";
	std::cout << temp1 / temp2 << "\n";
	std::cout << temp1 % temp2 << "\n";
	
	system("pause");
}
