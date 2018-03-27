#include <iostream>
//#include <windows.h>
#include "include/big_n.h"
#include "include/big_z.h"
#include "include/big_q.h"
#include "include/API.h"

int main(int argc, char *argv[]){
    BigPol t1("4 1"), t2("2 1");

    std::cout << t1 << "      " << t2 << "\n";
    std::cout << GCD_PP_P(t1, t2);

	API::parse_args(argc, argv);
}
