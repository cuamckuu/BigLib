#include <assert.h>
#include <sstream>
#include "../include/big_q.h"

BigFra::BigFra(): numerator("0"), denominator("1") {
	/* Initializer */
}

BigFra::BigFra(std::string str){
	/* Initializer from string */
	
	std::stringstream ss(str);
	ss >> numerator >> denominator;
}

BigFra::BigFra(BigInt numerator, BigInt denominator): numerator(numerator), denominator(denominator)  {
	/* Initializer from two BigInt */
	*this = RED_Q_Q(*this);
}

std::ostream& operator<< (std::ostream &stream, BigFra num){
    /* Function prints current number to stream output */
	
    num = RED_Q_Q(num);
    
    stream << num.numerator << "/" << num.denominator;

    return stream;
}

std::istream& operator>> (std::istream &stream, BigFra &num){
	/* Function read number from stream */
	
	std::string numer, denom;
	stream >> numer >> denom;
	
	if(!(numer == "" || numer == "")){
		num = BigFra(numer + " " + denom);
	}
		
	return stream;
}

std::string BigFra::to_float(int precision){
	/* Return float representation (as string) with set precision */
	
	std::stringstream ss;
	
	BigFra temp = *this;
	
	// Integer part
	ss << (temp.numerator / temp.denominator) << ".";
	temp.numerator = temp.numerator % temp.denominator;
	
	// Float part
	for(int i = 0; i < precision; i++){
		ss << (temp.numerator * BigInt("10"))  / temp.denominator;
		temp.numerator = (temp.numerator * BigInt("10")) % temp.denominator;
	}
	
	std::string result;
	ss >> result;
	
	return result;
};

BigFra GCD_VecQ_Q(std::vector<BigFra> coefs){
	/* Returns gcd of all numerators / lcm of all denominatorsû */
	
    if(coefs.size() == 1){
        return coefs[0];
    }else{
        BigNat denom_lcm(LCM_NN_N(coefs[0].denominator, coefs[1].denominator));
        BigNat num_gcd(GCD_NN_N(coefs[0].numerator, coefs[1].numerator));
        
        for(int i = 2; i < (int)coefs.size(); i++){
        	num_gcd = (GCD_NN_N(num_gcd, coefs[i].numerator));
            denom_lcm = (LCM_NN_N(denom_lcm, coefs[i].denominator));
		}
		
        return BigFra(BigInt(num_gcd, false), BigInt(denom_lcm, false));
    }
};

bool INT_Q_B(BigFra lhs) {
    /* Checks if fraction is integer */
    
	if(lhs.denominator == BigInt("1")){
		return true;
	}else{
		return false;
	}
}

BigFra TRANS_Z_Q(BigInt lhs) {
    /* Transform integer to fraction fith denum is equal to one, returns fraction */

    return BigFra(lhs, BigInt("1"));
}

BigInt TRANS_Q_Z(BigFra lhs) {
	/* Transform fraction to integer returns integer result */
	
    if(INT_Q_B(lhs) == true){
        return lhs.numerator;
    }
    return lhs.numerator / lhs.denominator;
}

BigFra BigFra::intPart(){
	/* Returns integer part of division as fraction */
	return BigFra(numerator / denominator, BigInt("1")); 
}

BigFra MUL_QQ_Q(BigFra lhs, BigFra rhs) {
    /* Miltiply lhs to rhs, returns result */

    lhs.numerator = MUL_ZZ_Z(lhs.numerator, rhs.numerator);
    rhs.denominator = MUL_ZZ_Z(lhs.denominator, rhs.denominator);
    
    return RED_Q_Q(BigFra(lhs.numerator,rhs.denominator));
}

BigFra DIV_QQ_Q(BigFra lhs, BigFra rhs) {
    /* Divede lhs to rhs, returns result */
	
	assert(("DIV_QQ_Q rhs is zero", rhs.numerator != BigInt("0")));

    lhs.numerator = lhs.numerator * rhs.denominator;
    rhs.denominator = lhs.denominator * rhs.numerator;
	
    return RED_Q_Q(BigFra(lhs.numerator,rhs.denominator));
}

BigFra RED_Q_Q(BigFra lhs) {
	/* Makes fraction irrreducable, returns new fraction */

    lhs.normalise();

    BigInt gcd = BigInt(GCD_NN_N(lhs.numerator, lhs.denominator), false);

    lhs.numerator = lhs.numerator / gcd;
    lhs.denominator = lhs.denominator / gcd;

    return lhs;
}

BigFra ADD_QQ_Q(BigFra lhs, BigFra rhs) {
	/* Adds rhs to lhs, returns result */
	
    BigInt lcm = lhs.denominator * rhs.denominator;

    lhs.numerator = lhs.numerator * rhs.denominator;
    rhs.numerator = rhs.numerator * lhs.denominator;
	
    BigFra temp(lhs.numerator + rhs.numerator, lcm);

    return RED_Q_Q(temp);
}

BigFra SUB_QQ_Q(BigFra lhs, BigFra rhs) {
    /* Substract rhs from lhs, returns result */
    
    rhs.numerator = -rhs.numerator;

    return ADD_QQ_Q(lhs, rhs);
}

void BigFra::normalise(){
	/* Makes numerator signed */
	
    int num_sign = POZ_Z_D(numerator);
    int denom_sign = POZ_Z_D(denominator);
    
    if(num_sign == denom_sign || num_sign == Sign(zero)){
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

bool BigFra::operator<(const BigFra &rhs){
	BigFra sub = *this - rhs;
	sub.normalise();
	
	return (sub.numerator < BigInt("0"));
};

bool BigFra::operator>(const BigFra &rhs){
	BigFra sub = *this - rhs;
	sub.normalise();
	
	return (sub.numerator > BigInt("0"));
};

bool BigFra::operator==(const BigFra &rhs){
	BigFra sub = *this - rhs;
	sub.normalise();
	
	return sub.numerator == BigInt("0");
};

bool BigFra::operator<=(const BigFra &rhs){
	return (*this < rhs) || (*this == rhs);
};

bool BigFra::operator>=(const BigFra &rhs){
	return (*this > rhs) || (*this == rhs);
};

bool BigFra::operator!=(const BigFra &rhs){
	return !(*this == rhs);
};

