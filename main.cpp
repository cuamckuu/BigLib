#include <iostream>
#include <windows.h>
#include "include/big_n.h"
#include "include/big_z.h"

int main(){
	std::string a, b;
	
	std::cin >> a >> b;
	
	BigInt temp1(a), temp2(b);
	
	std::cout << POW_ZZ_Z(temp1, temp2) << "\n";
	
	
	system("pause");
}
