#include <iostream>
#include <windows.h>
#include "include/big_n.h"
#include "include/big_z.h"
#include "include/big_q.h"

int main(){
	std::cout << "fork is started" << "\n";
	std::string a, b;
	bool boo = 0;

	std::cin >> a >> b;
	
	BigInt temp1(a), temp2(b);
	BigFra temp3(a,b);
    TRANS_Z_Q(temp1);

    std::cout << "what what what" << std::endl;

	std::cout << temp1 + temp2 << "\n";
	std::cout << temp1 - temp2 << "\n";
	std::cout << temp1 * temp2 << "\n";
	std::cout << temp1 / temp2 << "\n";
	std::cout << temp1 % temp2 << "\n";
	
	system("pause");
}
