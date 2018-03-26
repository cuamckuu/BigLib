#include <cmath>
#include <assert.h>
#include <string>
#include "../include/big_z.h"

BigInt::BigInt(){
	/* Initializer */
	
	*this = BigInt("0");
}

BigInt::BigInt(std::string str){
	/* Initializer. Takes string representation of big num */
	
	digits.clear();
	
	isNegative = false;
	//Get digits from string and add to vector
	for (int i = str.length() - 1; i >= 0; i--){
		if(str[i] != '-'){
			digits.push_back(str[i] - '0');	
		}else{
			isNegative = true;
		}
	}
	
	remove_leading_zeros();
}

BigInt::BigInt(BigNat num, bool isNegative) : BigNat(num){
	/* Initializer.*/
	
	this -> isNegative = isNegative;
	
	remove_leading_zeros();
}


std::ostream& operator<< (std::ostream &stream, const BigInt &num){
	/* Function prints current number to stream output */
	
	if(num.isNegative){
		stream << "-";
	}
	
	stream << (num.digits.empty() ? 0 : num.digits.back());
	
	for(int i = (int)num.digits.size() - 2; i >= 0; --i){
		stream << num.digits[i];	
	}
	
	return stream;
}

std::istream& operator>> (std::istream &stream, BigInt &num){
	/* Function read number from stream */
	
	std::string temp;
	stream >> temp;
	
	num = BigInt(temp);
	
	return stream;
}

BigNat ABS_Z_N(BigInt lhs){
	/* Returns absolute value of num by converting to natural */
	
	return BigNat(lhs);
}

int POZ_Z_D(BigInt lhs){
	/* Check number's sign */
	
	if(NZER_N_B(lhs) == false){
		return Sign::zero;
	}else if(lhs.isNegative){
		return Sign::negative;
	}else{
		return Sign::positive;
	}
}

BigInt MUL_ZM_Z(BigInt lhs){
	/* Changes sign of lhs to opposit, returns result */
	 
	lhs.isNegative ^= true;
	return lhs;
}

BigInt TRANS_N_Z(BigNat lhs){ 
	/* Transform BigNat to BigInt, returns result */
	
	return BigInt(lhs, false);
}

BigNat TRANS_Z_N(BigInt lhs){ 
	/* Transform BigInt to BigNat, returns result */
	
	return BigNat(lhs);
}

BigInt ADD_ZZ_Z(BigInt lhs, BigInt rhs){
	/* Adds two integer numbers, returns result */
	BigNat sum("0");
	BigInt result("0");

	//Signs of lhs and rhs	
	Sign left = Sign(POZ_Z_D(lhs));
	Sign right = Sign(POZ_Z_D(rhs));
	
	//If signs are the same, then result = old_sign * (abs(lhs) + abs(rhs))
	if(left == right){
		sum = ADD_NN_N(lhs, rhs);
		result = TRANS_N_Z(sum);
		
		if(left == Sign(negative)){
			result = -result;
		}
		
	}else{
		//If signs are different, make lhs positive or and rhs negative
		if((left == Sign(negative) || left == Sign(zero)) && (right == Sign(positive) || right == Sign(zero))){
			std::swap(lhs, rhs);
		}
		//Now left == Sign(positive or zero) and right == Sign(negative or zero)))
		
		CompareNat cmp = CompareNat(COM_NN_D(lhs, rhs));

		//Substract from bigger num smaller and care about sign
		if(cmp == CompareNat(lhsIsBigger)){
			// Usual substract;
			sum = SUB_NN_N(lhs, rhs);
			result = TRANS_N_Z(sum);
			
		}else if(cmp == CompareNat(rhsIsBigger)){
			//Substract lhs from rhs and set sign to negative;
			sum = SUB_NN_N(rhs, lhs);
			result = -TRANS_N_Z(sum);
			
		}else{
			//lhs == -rhs 	
		}
	}
	
	return result;	
}

BigInt SUB_ZZ_Z(BigInt lhs, BigInt rhs){
	rhs = -rhs;
	return (lhs + rhs);
};

BigInt MUL_ZZ_Z(BigInt lhs, BigInt rhs){
	/* Multiply BigInt's returns result */
	
	//Signs of lhs and rhs	
	Sign left = Sign(POZ_Z_D(lhs));
	Sign right = Sign(POZ_Z_D(rhs));
	
	//Multiply abs values
	BigNat mul = MUL_NN_N(lhs, rhs);
	BigInt result =  TRANS_N_Z(mul);
	
	//Multiply by both signs
	if(left == Sign(negative)){
		result = -result;
	}
	
	if(right == Sign(negative) && !(left == Sign(zero))){
		result = -result;
	}		
	
	return result;
}

BigInt DIV_ZZ_Z(BigInt lhs, BigInt rhs){
	/* Divide lhs by rhs, returns integer part of it */
	
	//Signs of lhs and rhs	
	Sign left = Sign(POZ_Z_D(lhs));
	Sign right = Sign(POZ_Z_D(rhs));
	
	//Divide abs values
	BigNat div = DIV_NN_N(lhs, rhs);
	BigInt result = TRANS_N_Z(div);
	
	//Multiply by both signs
	if(left == Sign(negative)){
		result = -result;
	}
	
	if(right == Sign(negative)){
		result = -result;
	}		
	
	return result;
}

BigInt MOD_ZZ_Z(BigInt lhs, BigInt rhs){
	/* Returns (lhs mod rhs) */
	 
	//Signs of lhs and rhs	
	Sign left = Sign(POZ_Z_D(lhs));
	Sign right = Sign(POZ_Z_D(rhs));
	
	//Get abs(lhs) mod abs(rhs)
	BigNat mod = MOD_NN_N(lhs, rhs);
	BigInt result = TRANS_N_Z(mod);
	
	//Multiply by lhs's sign
	if(left == Sign(negative)){
		result = -result;
	}
	
	//Make rhs positive
	if(right == Sign(negative)){
		rhs = -rhs;
	}		
	
	//If result is negative, add rhs once
	if(POZ_Z_D(result) == Sign(negative)){
		result = result + rhs;
	}
	
	return result;
}

//====Extra modules =====
BigInt POW_ZZ_Z(BigInt lhs, BigInt rhs){
	/* Fast pow lhs to rhs */
	
	assert(("POW_ZZ_Z No fraction support", rhs >= BigInt("0")));
	
	if(rhs == BigInt("0")){
		return BigInt("1");
	}else if(rhs % BigInt("2") == BigInt("1")){
		return POW_ZZ_Z(lhs, rhs - BigInt("1")) * lhs;
	}else{
		BigInt temp = POW_ZZ_Z(lhs, rhs / BigInt("2"));
		return temp * temp;
	}
}


//======OPERATORS===========


BigInt BigInt::operator+(const BigInt &rhs){
	return ADD_ZZ_Z(*this, rhs);
};

BigInt BigInt::operator-(const BigInt &rhs){
	return SUB_ZZ_Z(*this, rhs);
};

BigInt BigInt::operator-(){
	return MUL_ZM_Z(*this);
};

BigInt BigInt::operator*(const BigInt &rhs){
	return MUL_ZZ_Z(*this, rhs);
};

BigInt BigInt::operator/(const BigInt &rhs){
	return DIV_ZZ_Z(*this, rhs);
};

BigInt BigInt::operator%(const BigInt &rhs){
	return MOD_ZZ_Z(*this, rhs);
};

bool BigInt::operator<(const BigInt &rhs){
	return POZ_Z_D(*this - rhs) == Sign(negative);
};

bool BigInt::operator>(const BigInt &rhs){
	return POZ_Z_D(*this - rhs) == Sign(positive);
};

bool BigInt::operator==(const BigInt &rhs){
	return (BigNat(*this) == BigNat(rhs)) && (POZ_Z_D(*this) == POZ_Z_D(rhs));
};

bool BigInt::operator<=(const BigInt &rhs){
	return (*this < rhs) || (*this == rhs);
};

bool BigInt::operator>=(const BigInt &rhs){
	return (*this > rhs) || (*this == rhs);
};

