
#include "include/big_q.h"

BigFra::BigFra(BigInt numerator, BigInt denominator): numerator(numerator), denominator(denominator)  {}

/*BigFra BigFra::RED_Q_Q(BigFra &lhs) {
 	
	
    BigInt num = lhs.numerator;
    BigInt denom = lhs.denominator;
    BigNat i = GCD_NN_N( ABS_Z_N(num), ABS_Z_N(denom));
    BigInt temp4(i, false);
    lhs.numerator = DIV_ZZ_Z(num, temp4);
    lhs.denominator = DIV_ZZ_Z(denom, temp4);

    return lhs;
}*/

BigFra RED_Q_Q(BigFra &lhs) {
    /* œ≈–≈œ»—¿À */
	BigFra temp = *this;
	
    BigInt gcd = BigInt(GCD_NN_N(temp.numerator, temp.denominator), false);
    
    temp.numerator = temp.numerator / gcd;
    temp.denominator = temp.denominator / gcd;

    return temp;
}


bool BigFra::INT_Q_B(BigInt lhs, BigInt rhs) {

	/* ÃÓÎÓ‰Âˆ */
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

BigFra BigFra::MUL_QQ_Q(BigFra lhs, BigFra rhs) {
    lhs.numerator = (MUL_ZZ_Z(lhs.numerator, rhs.numerator));
    rhs.denominator = (MUL_ZZ_Z(lhs.denominator, rhs.denominator));
    return BigFra(lhs.numerator,rhs.denominator);
}

BigFra BigFra::DIV_QQ_Q(BigFra lhs, BigFra rhs) {
    
}






