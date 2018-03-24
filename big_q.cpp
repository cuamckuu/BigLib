
#include "include/big_q.h"

BigFra::BigFra(BigInt numerator, BigInt denominator): numerator(numerator), denominator(denominator)  {}


BigFra RED_Q_Q(BigFra &lhs) {

    /*function became greatest common multiple of num and denum*/
    /*after that it devide num and denum on gcd, and returns it*/
	BigFra temp = lhs;

    BigInt gcd = BigInt(GCD_NN_N(temp.numerator, temp.denominator), false);

    temp.numerator = temp.numerator / gcd;
    temp.denominator = temp.denominator / gcd;

    return temp;
}


bool INT_Q_B(BigInt lhs, BigInt rhs) {
    /*function returns 1 if remaider lhs%rhs*/

    return (lhs % rhs == BigInt("0"));
}

BigFra TRANS_Z_Q(BigInt lhs) {
    /*          */

    BigInt denum("1");
    std::cout << "forsacen: " << lhs << "  " << denum << std::endl;
    return BigFra(lhs, denum);
}

BigInt TRANS_Q_Z(BigFra lhs) {


    if(lhs.denominator == BigInt("1")){
        return lhs.numerator;
    }
    return BigInt("0");
}

BigFra MUL_QQ_Q(BigFra lhs, BigFra rhs) {
    /* */

    lhs.numerator = (MUL_ZZ_Z(lhs.numerator, rhs.numerator));
    rhs.denominator = (MUL_ZZ_Z(lhs.denominator, rhs.denominator));
    return BigFra(lhs.numerator,rhs.denominator);
}

BigFra DIV_QQ_Q(BigFra lhs, BigFra rhs) {
    /* */

    if(rhs.numerator == BigInt("0")){
        //Here isn't error message
    } else {
        lhs.numerator = (MUL_ZZ_Z(lhs.numerator, rhs.denominator));
        rhs.denominator = (MUL_ZZ_Z(lhs.denominator, rhs.numerator));
    }
    return BigFra(lhs.numerator,rhs.denominator);
}







