#include <sstream>
#include <algorithm>
#include <string>
#include "../include/big_p.h"

std::ostream& operator<<(std::ostream &stream, BigPol pol){
	BigFra zero = BigFra("0 1");
	
	int nextSign = 0;
	bool wasSign = false;
	bool wasSmth = false;
	
	for (int i = pol.coefs.size() - 1; i >= 0; --i) {
    	if(pol.coefs[i] != zero){
    		//Abs coef, for cout
			BigFra curr = (pol.coefs[i] < zero ? pol.coefs[i] * BigFra("-1 1") : pol.coefs[i]); 

			stream << curr;
			if(i != 0){
				std::cout << " * x^" << i;
			}
    		wasSign = false;
    		wasSmth = true;
		}
		
		//Find next sign
		int j = i;
		do{
			j--;
		}while(j >= 0 && pol.coefs[j] == zero);
		
		if(j == -1){
			nextSign = 0;
		}else if(pol.coefs[j] > zero){
			nextSign = 1;
		}else if(pol.coefs[j] < zero){
			nextSign = -1;
		}
		
		//Output sign
		if(wasSmth && !wasSign && i != 0){
			if(nextSign == 1 ){
				stream << " + ";
			}else if(nextSign == -1){
				stream << " - ";
			}
			wasSign = true;
		}
    }
    
    if(!wasSmth){
    	stream << "0/1";
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

BigPol MOD_PP_P(BigPol lhs, BigPol rhs){
	/* Returns (lhs mod rhs) */
	
	
	BigPol temp = lhs / rhs;
	//std::cout << lhs << " - " << temp << "\n";
	if(DEG_P_D(lhs) == 0 && DEG_P_D(rhs) == 0){
		temp.coefs[0] = temp.coefs[0].intPart();
	}
	//std::cout << lhs << " - " << temp << "\n";
	temp = temp * rhs;
	//std::cout << lhs << " - " << temp << "\n";
	
	return (lhs - temp);
}

BigPol ADD_PP_P(BigPol lhs, BigPol rhs) {
	/* Adds lhs to rhs, returns resutl */
	
	//STRANGE BEHAVIOUR!!!!
	if(lhs.coefs.size() > rhs.coefs.size()){
		std::swap(lhs, rhs);
	} 
	
	BigFra zero = BigFra("0 1");
    int max_len = std::max(lhs.coefs.size(), rhs.coefs.size());
    
    for(int i = 0; i < max_len; i++){
        if(i < lhs.coefs.size()){
        	//std::cout << lhs.coefs[i] << "asd" << rhs.coefs[i] << "\n";
        	lhs.coefs[i] = lhs.coefs[i] + (i < rhs.coefs.size() ? rhs.coefs[i] : zero);
			//std::cout << lhs.coefs[i] << "asd" << rhs.coefs[i] << "\n";
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

int DEG_P_D(BigPol lhs) {
	/* Returns degree of polynom */
	
	for(int i = lhs.coefs.size() - 1; i >= 0; i--){
		if(lhs.coefs[i] != BigFra("0 1")){
			return i;
		}
	}
	return -1;
}

BigPol DIV_PP_P(BigPol lhs, BigPol rhs){

    BigPol result("0 1");
    int lhs_deg = DEG_P_D(lhs);
    int rhs_deg = DEG_P_D(rhs);
	
    while(lhs_deg >= rhs_deg && lhs.coefs[lhs_deg] != BigFra("0 1")){
        int k = lhs_deg - rhs_deg;
		
		BigFra coef = lhs.coefs[lhs_deg] / rhs.coefs[rhs_deg];
        
		BigPol temp = BigPol("1 1") * coef;
        
        if(k > 0){
        	temp = MUL_Pxk_P(temp, k);	
		}
		
        BigPol toSub = MUL_PP_P(rhs, temp);
        //std::cout << lhs << " - " << toSub << "\n";
        
		lhs = lhs - toSub;
		
        result = result + temp;
    	
    	lhs_deg = DEG_P_D(lhs);
    	rhs_deg = DEG_P_D(rhs);
	}

    return result;
}

BigPol BigPol::operator+(const BigPol &rhs) {
    return ADD_PP_P(*this, rhs);
}

BigPol BigPol::operator*(const BigFra &rhs) {
    return MUL_PQ_P(*this, rhs);
}

BigPol BigPol::operator/(const BigPol &rhs) {
    return DIV_PP_P(*this, rhs);
}

BigPol BigPol::operator-(const BigPol &rhs) {
    return SUB_PP_P(*this, rhs);
}

BigPol BigPol::operator*(const BigPol &rhs) {
    return MUL_PP_P(*this, rhs);
}

BigPol BigPol::operator%(const BigPol &rhs) {
    return MOD_PP_P(*this, rhs);
}
