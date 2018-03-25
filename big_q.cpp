#include "include/big_q.h"

BigFra::BigFra(BigInt numerator, BigInt denominator): numerator(numerator), denominator(denominator)  {
	*this = RED_Q_Q(*this);
}

std::ostream& operator<< (std::ostream &stream, BigFra num){
    /* Function prints current number to stream output */
	
    num = RED_Q_Q(num);
    num.normalise();
    stream << num.numerator << "/" << num.denominator;

    return stream;
}

//Demid's function's
bool INT_Q_B(BigInt lhs, BigInt rhs) {
    /* Checks if fraction is integer */

    return (lhs % rhs == BigInt("0"));
}

BigFra TRANS_Z_Q(BigInt lhs) {
    /* Transform integer to fraction fith denum is equal to one, returns fraction */

    BigInt denum("1");
    //std::cout << "forsacen: " << lhs << "  " << denum << std::endl;
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


//Stepan's function's
BigFra RED_Q_Q(BigFra lhs) {
    BigFra temp = lhs;

    BigInt gcd = BigInt(GCD_NN_N(temp.numerator, temp.denominator), false);

    temp.numerator = temp.numerator / gcd;
    temp.denominator = temp.denominator / gcd;

    return temp;
}

BigFra ADD_QQ_Q(BigFra lhs, BigFra rhs) {
    BigInt lcm = lhs.denominator * rhs.denominator;

    lhs.numerator = lhs.numerator * rhs.denominator;
    rhs.numerator = rhs.numerator * lhs.denominator;

    BigFra temp(lhs.numerator + rhs.numerator, lcm);

    return RED_Q_Q(temp);
}

BigFra SUB_QQ_Q(BigFra lhs, BigFra rhs) {
    //USE ADD
    rhs.numerator = MUL_ZM_Z(rhs.numerator);

    return ADD_QQ_Q(lhs, rhs);
}

void BigFra::normalise(){
    int isNegative1 = POZ_Z_D(numerator);
    int isNegative2 = POZ_Z_D(denominator);
    if(isNegative1 == isNegative2){
        numerator = BigInt(numerator, false);
        denominator = BigInt(denominator, false);
    }else{
        numerator = BigInt(numerator, true);
        denominator = BigInt(denominator, false);
    }
}

//==OPERATORS===

BigFra BigFra::operator+(const BigFra &rhs){
    return ADD_QQ_Q(*this, rhs);
}

BigFra BigFra::operator-(const BigFra &rhs){
    return SUB_QQ_Q(*this, rhs);
}

BigFra BigFra::operator*(const BigFra &rhs){
    return MUL_QQ_Q(*this, rhs);
}

BigFra BigFra::operator/(const BigFra &rhs){
    return DIV_QQ_Q(*this, rhs);
}




