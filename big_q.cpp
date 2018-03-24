
#include "include/big_q.h"

BigFra::BigFra(BigInt numerator, BigInt denominator): numerator(numerator), denominator(denominator)  {}

BigFra BigFra::RED_Q_Q(BigFra &lhs) {
    /*Function returns  abbreviated */

    BigInt num = lhs.numerator;
    BigInt denom = lhs.denominator;
    BigNat i = GCD_NN_N( ABS_Z_N(num), ABS_Z_N(denom));
    BigInt temp4(i, false);
    lhs.numerator = DIV_ZZ_Z(num, temp4);
    lhs.denominator = DIV_ZZ_Z(denom, temp4);

    return lhs;
}

bool BigFra::INT_Q_B(BigInt lhs, BigInt rhs) {
    /*if(lhs % rhs == BigInt("0")){
    return true;
}else{
    return false;
}*/

    return lhs % rhs == BigInt("0");
}



BigFra BigFra::TRANS_Z_Q(BigInt lhs) {
    /*          */

    BigInt denum("1");
    return BigFra(lhs, denum);
}

BigInt BigFra::TRANS_Q_Z(BigFra lhs) { //what we have to do with not "1" in denum?


    if(lhs.denominator == BigInt("1")){
        return lhs.numerator;
    }
    return BigInt("0");
}






