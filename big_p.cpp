#include <sstream>
#include <algorithm>
#include <string>
#include "include/big_p.h"

std::ostream& operator<<(std::ostream &stream, BigPol pol){
	BigFra zero = BigFra(BigInt("0"), BigInt("1"));
	
	for (int i = pol.coefs.size() - 1; i > 0; --i) {
    	if(pol.coefs[i] != zero){
    		stream << pol.coefs[i] << " * x^" << i;
    		
    		if(pol.coefs[i-1] > zero){
    			stream << " + ";
			}else if(pol.coefs[i-1] < zero){
				stream << " - ";
			}
		}
    }
    
	if(pol.coefs[0] != zero){
    	stream << pol.coefs[0];
	}
    
    return stream;
}

BigPol::BigPol(std::string str) {
    /* Initializer. Takes all fractions as num and denom */
	
	std::stringstream ss(str);
	
    BigFra temp_coef;
	while(ss >> temp_coef){
		coefs.push_back(temp_coef);
	}
	std::reverse(coefs.begin(), coefs.end());
}

BigPol ADD_PP_P(BigPol lhs, BigPol rhs) {
	/* Adds lhs to rhs, returns resutl */
	
	BigFra zero = BigFra(BigInt("0"), BigInt("1"));
    int max_len = std::max(lhs.coefs.size(), rhs.coefs.size());
    
    for(int i = 0; i < max_len; i++){
        if(i < lhs.coefs.size()){
        	 lhs.coefs[i] = lhs.coefs[i] + (i < rhs.coefs.size() ? rhs.coefs[i] : zero);
		}else{
			lhs.coefs.push_back(rhs.coefs[i]);
		}
    }
    
    return lhs;
}

BigPol MUL_PQ_P(BigPol lhs, BigFra rhs) {
	/* Multyply all coefs by rhs, returns result */
	
    for(int i = 0; i < lhs.coefs.size(); i++){
        lhs.coefs[i] = lhs.coefs[i] * rhs;
    }

    return lhs;
}

BigPol SUB_PP_P(BigPol lhs, BigPol rhs) {
	/* Substract rhs from lhs, returns result */
	
    BigFra minus_one(BigInt("-1"), BigInt("1"));
    rhs = rhs * minus_one;
    
    return ADD_PP_P(lhs, rhs);
}

BigPol MUL_Pxk_P(BigPol lhs, unsigned int k){
	/* Multiply all x'es by x^k, where k is natural */

    int size = lhs.coefs.size() - 1;
    BigFra zero = BigFra(BigInt("0"), BigInt("1"));
    
    //Initialize new elements with zero
    for (int j = 0; j < k; ++j) {
        lhs.coefs.push_back(zero);
    }
    
    //Move all coeffs by k steps
    for(int i = size + k; i >= k; --i) {
        lhs.coefs[i] = lhs.coefs[i - k];
        lhs.coefs[i - k] = zero;
    }
    
    return lhs;
}

BigPol MUL_PP_P(BigPol lhs, BigPol rhs){
	/* Multiply lhs by rhs, returns result */
	
    BigPol result = BigPol("0 1");
	
    for (int i = 0; i < rhs.coefs.size(); ++i) {
        //Multiply by coeff and x^i for every x
		BigPol temp_pol = lhs * rhs.coefs[i];
		
		if(i != 0){
        	temp_pol = MUL_Pxk_P(temp_pol, i);
		}
		
		result = result + temp_pol;
    }
    
    return result;
}

BigFra LED_P_Q(BigPol lhs){
	/* Returns coef before x with higher power */ 
    return (lhs.coefs[lhs.coefs.size()]);
}

BigPol DER_P_P(BigPol lhs) {
	/* Returns derivative of polynom */
	
    for(int i = 1; i < lhs.coefs.size(); i++){
        BigFra temp = BigFra(BigInt(std::to_string(i)), BigInt("1"));
        
		lhs.coefs[i-1] = lhs.coefs[i];
        lhs.coefs[i-1] = lhs.coefs[i-1] * temp;
    }
   
    BigFra zero = BigFra(BigInt("0"), BigInt("1"));
	lhs.coefs[lhs.coefs.size() - 1] = zero;
    
    return lhs;
}

BigNat DEG_P_N(BigPol lhs) {
	/* Returns degree of polynom */
	
    return BigNat(std::to_string(lhs.coefs.size()));
}

BigPol BigPol::operator+(const BigPol &rhs) {
    return ADD_PP_P(*this, rhs);
}

BigPol BigPol::operator*(const BigFra &rhs) {
    return MUL_PQ_P(*this, rhs);
}

BigPol BigPol::operator-(const BigPol &rhs) {
    return SUB_PP_P(*this, rhs);
}

BigPol BigPol::operator*(const BigPol &rhs) {
    return MUL_PP_P(*this, rhs);
}
