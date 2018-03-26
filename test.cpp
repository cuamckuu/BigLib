#include <assert.h>
#include "include/big_n.h"
#include "include/big_z.h"
#include "include/big_p.h"

template<class T>
bool check(T expectation, T reality){
	bool result = (expectation == reality);
	if(result == false){
		std::cout << expectation << " != " << reality << "\n";
	}	
    return result;
}

bool testNat(){
    BigNat zero("0"), one("1"), a("145"), b("45");

    bool isOK = true;

    isOK &= check<BigNat>(a + b, BigNat("190"));
    isOK &= check<BigNat>(a - b, BigNat("100"));
    isOK &= check<BigNat>(a / b, BigNat("3"));
    isOK &= check<BigNat>(a * b, BigNat("6525"));

    isOK &= check<BigNat>(a + zero, a);
    isOK &= check<BigNat>(a - zero, a);
    //isOK &= check(a / zero, BigNat("3"));
    isOK &= check<BigNat>(a * zero, zero);

    isOK &= check<BigNat>(a + one, BigNat("146"));
    isOK &= check<BigNat>(a - one, BigNat("144"));
    isOK &= check<BigNat>(a / one, a);
    isOK &= check<BigNat>(a * one, a);

    return isOK;
}

bool testInt(){
    BigInt zero("0"), one("1"), a("145"), b("-45"), minusOne("-1"), minusA("-145"), minusB("45");

    bool isOK = true;

    isOK &= check<BigInt>(a + b, BigInt("100"));
    isOK &= check<BigInt>(a - b, BigInt("190"));
    isOK &= check<BigInt>(a / b, BigInt("-3"));
    isOK &= check<BigInt>(a * b, BigInt("-6525"));

    isOK &= check<BigInt>(a + zero, a);
    isOK &= check<BigInt>(a - zero, a);
    isOK &= check<BigInt>(zero - a, minusA);
    //isOK &= check(a / zero, BigNat("3"));
    isOK &= check<BigInt>(a * zero, zero);

    isOK &= check<BigInt>(a + one, BigInt("146"));
    isOK &= check<BigInt>(a - one, BigInt("144"));
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

/*
bool testPol(){
    BigPol zero("0 0"), one("1 1"), a("1 2 3 4"), b("1 2 3 4"), c("1 2 3 4 5 6");

    bool isOK = true;

    isOK &= check<BigPol>(a + b, BigPol("1 1 3 2"));
    isOK &= check<BigPol>(a - b, BigPol("0 1 0 1"));
    isOK &= check<BigPol>(a / b, BigPol("3"));
    isOK &= check<BigPol>(a * b, BigPol("6525"));

    isOK &= check<BigPol>(a + zero, a);
    isOK &= check<BigPol>(a - zero, a);
    //isOK &= check(a / zero, BigNat("3"));
    isOK &= check<BigPol>(a * zero, zero);

    isOK &= check<BigPol>(a + one, BigPol("146"));
    isOK &= check<BigPol>(a - one, BigPol("144"));
    isOK &= check<BigPol>(a / one, a);
    isOK &= check<BigPol>(a * one, a);

    return isOK;
}*/

void test_all(){
    std::cout << "Naturals test: " << testNat() << "\n";
    std::cout << "Integers test: " << testInt() << "\n";
    std::cout << "Fractions test: " << testFra() << "\n";
    //std::cout << "Polynomial test: " << testPol();
}
