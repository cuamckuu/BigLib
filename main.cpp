#include <iostream>
#include <windows.h>
#include "include/big_n.h"
#include "include/big_z.h"
#include "include/big_q.h"

int main(){
	std::string a, b, c, d;
	
	std::cin >> a >> b >> c >> d;
	
	BigFra temp1(a,b), temp2(c, d);

    std::cout << temp1 << " " << temp2  << std::endl;
    std::cout << temp1 + temp2  << std::endl;
    std::cout << temp1 - temp2  << std::endl;
    std::cout << temp1 / temp2  << std::endl;
    std::cout << temp1 * temp2  << std::endl;
	
	system("pause");
}
