#include <iostream>
#include <windows.h>
#include "include/big_n.h"
#include "include/big_z.h"
#include "include/big_q.h"
#include "include/big_p.h"

int main(){
	std::string a, b, c, d, e, f;
	
//	std::cin >> a >> b >> c >> d;
//
//	BigFra temp1(a,b), temp2(c, d);

    e = "";
    f = "";

    getline(std::cin, e);
    //getline(std::cin, f);
    BigPol temp3(e);
    //BigPol temp4{f};

//    std::cin >> a >> b;
//    BigFra temp5(a, b);


    //std::cout << temp3 - temp4;
    std::cout << temp3 * 2;


//    std::cout << temp1 << " " << temp2  << std::endl;
//    std::cout << temp1 + temp2  << std::endl;
//    std::cout << temp1 - temp2  << std::endl;
//    std::cout << temp1 / temp2  << std::endl;
//    std::cout << temp1 * temp2  << std::endl;
	
	system("pause");
}
