#include <assert.h>
#include "include/big_n.h"
#include "include/big_z.h"
#include "include/big_p.h"
#include <windows.h>

template<class T>
bool check(T expectation, T reality){
	/* Compare expectation to reality of any type */
	bool result = (expectation == reality);
	if(result == false){
		std::cout << expectation << " != " << reality << "\n";
	}
		
    return result;
}

bool testNat(){
    BigNat zero("0"), one("1"), a("150"), b("50");

    bool isOK = true;

    isOK &= check<BigNat>(a + b, BigNat("200"));
    isOK &= check<BigNat>(a - b, BigNat("100"));
    isOK &= check<BigNat>(a / b, BigNat("3"));
    isOK &= check<BigNat>(a * b, BigNat("7500"));
    isOK &= check<BigNat>(a + zero, a);
    isOK &= check<BigNat>(a - zero, a);
    isOK &= check<BigNat>(zero + a, a);
    isOK &= check<BigNat>(a * zero, zero);
    isOK &= check<BigNat>(a + one, BigNat("151"));
    isOK &= check<BigNat>(a - one, BigNat("149"));
    isOK &= check<BigNat>(a / one, a);
    isOK &= check<BigNat>(a * one, a);

    return isOK;
}

bool testInt(){
    BigInt zero("0"), one("1"), a("150"), b("-50"), minusOne("-1"), minusA("-150"), minusB("50");

    bool isOK = true;

    isOK &= check<BigInt>(a + b, BigInt("100"));
    isOK &= check<BigInt>(a - b, BigInt("200"));
    isOK &= check<BigInt>(a / b, BigInt("-3"));
    isOK &= check<BigInt>(a * b, BigInt("-7500"));

    isOK &= check<BigInt>(a + zero, a);
    isOK &= check<BigInt>(a - zero, a);
    isOK &= check<BigInt>(zero + a, a);
    isOK &= check<BigInt>(zero - a, minusA);
    //isOK &= check(a / zero, BigNat("3"));
    isOK &= check<BigInt>(a * zero, zero);
    isOK &= check<BigInt>(one + minusOne, zero);
    isOK &= check<BigInt>(minusOne + one, zero);

    isOK &= check<BigInt>(a + one, BigInt("151"));
    isOK &= check<BigInt>(a - one, BigInt("149"));
    isOK &= check<BigInt>(one + a, BigInt("151"));
    isOK &= check<BigInt>(one - a, BigInt("-149"));
    isOK &= check<BigInt>(a / one, a);
    isOK &= check<BigInt>(a * one, a);

    isOK &= check<BigInt>(a * minusOne, minusA);
    isOK &= check<BigInt>(b * minusOne, minusB);

    return isOK;
}

bool testFra(){
    BigFra zero("0 1"), one("1 1"), a("145 2"), b("45 2"), minusA("-145 2"), minusB("-45 2"), minusOne("-1 1");

    bool isOK = true;

    isOK &= check<BigFra>(a + b, BigFra("95 1"));
    isOK &= check<BigFra>(a - b, BigFra("50 1"));
    isOK &= check<BigFra>(a / b, BigFra("29 9"));
    isOK &= check<BigFra>(a * b, BigFra("6525 4"));

    isOK &= check<BigFra>(a + zero, a);
    isOK &= check<BigFra>(a - zero, a);
    //isOK &= check(a / zero, BigNat("3"));
    isOK &= check<BigFra>(a * zero, zero);

    isOK &= check<BigFra>(a * minusOne, minusA);
    isOK &= check<BigFra>(zero - b, minusB);

    isOK &= check<BigFra>(a + one, BigFra("147 2"));
    isOK &= check<BigFra>(a - one, BigFra("143 2"));
    isOK &= check<BigFra>(a / one, a);
    isOK &= check<BigFra>(a * one, a);

    return isOK;
}


bool testPol(){
    BigPol zero("0 1"), one("1 1"), a("1 2 3 4"), b("1 2 3 4"), c("1 2 3 4 5 6");

    bool isOK = true;

    isOK &= check<BigPol>(a + b, BigPol("1 1 3 2"));
    isOK &= check<BigPol>(a - b, BigPol("0 1 0 1"));
    isOK &= check<BigPol>(a / b, BigPol("1 1"));
    isOK &= check<BigPol>(a * b, BigPol("1 4 6 8 9 16"));
	
    isOK &= check<BigPol>(a + zero, a);
    isOK &= check<BigPol>(a - zero, a);
    isOK &= check<BigPol>(a * zero, zero);

    isOK &= check<BigPol>(a + one, BigPol("1 2 7 4"));
    isOK &= check<BigPol>(a - one, BigPol("1 2 -1 4"));
    
	isOK &= check<BigPol>(a / one, a);
    isOK &= check<BigPol>(a * one, a);

    return isOK;
}

enum Colors{green = 10, red = 12};
void test_all(){	
    std::cout << "Naturals test: "  << testNat() << "\n";
    std::cout << "Integers test: "  << testInt() << "\n";
    std::cout << "Fractions test: " << testFra() << "\n";
    std::cout << "Polynoms test: "  << testPol() << "\n";
}
