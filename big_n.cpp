#include <cmath>
#include <assert.h>
#include <string>
#include "include/big_n.h"
#include "include/big_z.h"

BigNat::BigNat(){
	/* Initializer. */
}

BigNat::BigNat(std::string str){
	/* Initializer. Takes string representation of big num */
	
	//Get digits from string and add to vector
	for (int i = str.length() - 1; i >= 0; i--){
		digits.push_back(str[i] - '0');
	}
	
	remove_leading_zeros();
}


BigNat::BigNat(BigInt num){
	/* Initializer. Takes unsigned num */
	digits = num.digits;
	
	remove_leading_zeros();
}

void BigNat::remove_leading_zeros(){
	/* Remove zeros from begining */
	
	while (digits.size() > 1 && digits.back() == 0){
		digits.pop_back();
	}
}

std::ostream& operator<< (std::ostream &stream, BigNat num){
	/* Function prints current number to stream output */
	
	stream << (num.digits.empty() ? 0 : num.digits.back());
	
	for(int i = (int)num.digits.size() - 2; i >= 0; --i){
		stream << num.digits[i];	
	}
	
	return stream;
}

int COM_NN_D(BigNat &lhs, BigNat &rhs){
	/* Compare two nums, returns 0 if nums are equal, 1 if lhs < rhs, 2 if lhs > rhs */
	
	//Check by amount of digits
	if(lhs.digits.size() > rhs.digits.size()){	
		return CompareNat(lhsIsBigger);
	}else if(lhs.digits.size() < rhs.digits.size()){
		return CompareNat(rhsIsBigger);
	}else{
		//If amount of digits is equal check from higher digit
		for(int i = lhs.digits.size() - 1; i >= 0; i--){
			if(lhs.digits[i] > rhs.digits[i]){
				return CompareNat(lhsIsBigger); 
			}else if(lhs.digits[i] < rhs.digits[i]){
				return CompareNat(rhsIsBigger);
			}
		}
		
		return CompareNat(equal);
	}
}

bool NZER_N_B(BigNat &lhs){
	/* If number is not equal to zero returns true, else false */
	
	for(int i = 0; i < lhs.digits.size(); i++){
		if(lhs.digits[i] != 0){
			return true;
		}
	}
	
	return false;
}

BigNat ADD_1N_N(BigNat &lhs){
	/* Adds one to lhs, returns result */
	
	//Result is copy of current num
	BigNat result = lhs;
	
	int carry = 0;
	int max_len = result.digits.size();
	
	//Loop while max length isn't reached or there is a carry
	for(int i = 0; i < max_len || carry; i++){
	
		//If max length is reached, but there is still a carry, add new digit initialized with zero
		if(i == max_len){
			result.digits.push_back(0);
		}	
		
		result.digits[i] += carry + (i == 0 ? 1 : 0);
		
		carry = result.digits[i] >= 10;
		
		if(carry){
			result.digits[i] -= 10;
		}
	}
	
	return result;
}

BigNat ADD_NN_N(BigNat &lhs, BigNat &rhs){
	/* Add two positive BigInt's returns result */
	
	//Result is copy of current num
	BigNat result = lhs;
	
	int carry = 0;
	int max_len = std::max(result.digits.size(), rhs.digits.size());
	
	//Loop while max_len isn't reached or there is a carry
	for(int i = 0; i < max_len || carry; i++){
		
		//If max_len is reached, but there is still a carry, add new digit initialized with zero
		if(i == result.digits.size()){
			result.digits.push_back(0);
		}	
		
		result.digits[i] += carry + (i < rhs.digits.size() ? rhs.digits[i] : 0);
		
		carry = result.digits[i] >= 10;
		if(carry){
			result.digits[i] -= 10;
		}
	}
	
	return result;	
}

BigNat SUB_NN_N(BigNat &lhs, BigNat &rhs){
	/* If possible, substract rhs from lhs, returns result */
	
	//Smaller num for result and birrer for toSub
	BigNat result = lhs;
	BigNat toSub = rhs;
	
	assert(("SUB_NN_N, rhs is bigger", COM_NN_D(lhs, rhs) != CompareNat(rhsIsBigger)));
	
	//Substract loop
	int carry = 0;
	for(int i = 0; i < toSub.digits.size() || carry; i++){
		result.digits[i] -= carry + (i < toSub.digits.size() ? toSub.digits[i] : 0);
		
		//If current digit is negative, carry 1 from next and add 10 to current
		carry = result.digits[i] < 0;
		if(carry){
			result.digits[i] += 10;	
		}  
	}
	
	result.remove_leading_zeros();	
	return result;	
}

BigNat MUL_ND_N(BigNat &lhs, int multiplier){
	/* Multiply lhs by natural multiplier, returns result */
	
	BigNat result = lhs;	
	
	//Multiply loop
	int carry = 0;
	for (int i = 0; i < result.digits.size() || carry; i++){
		//If there is carry and digits end, add new digit
		if (i == result.digits.size()){
			result.digits.push_back(0);	
		}
		
		long long cur = carry + result.digits[i] * multiplier * 1ll;
		
		//Current digit is last digit from current, the rest is for carry
		result.digits[i] = (int)(cur % 10);
		carry = (int)(cur / 10);
	}
	
	result.remove_leading_zeros();
	return result;
};

BigNat MUL_Nk_N(BigNat &lhs, int k){
	/* Miltiply lhs by 10^k, returns the result */
	
	//Adds k zeros to end of num
	BigNat result("0");
	result.digits = std::vector<int>(k, 0);
	
	//Adds lhs's digits after zeros (Remember that digits is in reversed order) 
	result.digits.insert(result.digits.end(), lhs.digits.begin(), lhs.digits.end());
	
	result.remove_leading_zeros();
	return result;
};

BigNat MUL_NN_N(BigNat &lhs, BigNat &rhs){
	/* Multiply lhs by rhs, returns result, not optimal 
	per amount of multiplication to save some memory */
	
	BigNat result("0");
	
	//Multiply loop
	for(int i = 0; i < rhs.digits.size(); i++){
		BigNat temp("0");
		
		temp = lhs * rhs.digits[i];
		temp = MUL_Nk_N(temp, i);
		
		result = result + temp;
	}
	
	result.remove_leading_zeros();
	return result;
}

BigNat SUB_NDN_N(BigNat &lhs, int k, BigNat &rhs){
	/* If possible, substract k*rhs from lhs, returns result */
	
	BigNat temp = rhs * k;
	assert(("SUB_NDN_N, k*rhs is bigger than lhs", COM_NN_D(lhs, temp) != CompareNat(rhsIsBigger)));
	
	BigNat result = lhs - temp;
	
	result.remove_leading_zeros();
	return result;
}

BigNat DIV_NN_Dk(BigNat &lhs, BigNat &rhs){
	/* Returns first num of lhs/rhs, miltiplied by 10^k */
	
	//Order of rhs sshould be less or equal
	assert(("DIV_NN_Dk rhs.size() > lhs.size()", lhs.digits.size() >= rhs.digits.size()));
	
	//Can't divide by zero
	assert(("DIV_NN_Dk rhs is zero", NZER_N_B(rhs) == 1));
	
	
	for(int i = lhs.digits.size() - 1; i >= 0; i--){
		for(int mul = 9; mul > 0; mul--){
			BigNat temp("0");
			temp = rhs * mul;
			temp = MUL_Nk_N(temp, i);
			
			if(COM_NN_D(lhs, temp) != CompareNat(rhsIsBigger)){
				//std::cout << lhs << " " << temp << "\n";
				BigNat result(std::to_string(mul));
				result = MUL_Nk_N(result, i);
				return result;				
			}
		}
	}
}

BigNat DIV_NN_N(BigNat lhs, BigNat rhs){
	/* Returns integer part of lhs / rhs */
	
	BigNat result("0");
	BigNat temp_to_mul("0");
	BigNat temp_to_sub("0");
	
	//While possible, substract from lhs maximum (k * rhs), which is still less than lhs.
	while(COM_NN_D(lhs, rhs) != CompareNat::rhsIsBigger){
		//Find k and add to result
		temp_to_mul = DIV_NN_Dk(lhs, rhs);
		result = result + temp_to_mul;
		
		//Find (k*rhc) and substract
		temp_to_sub = rhs * temp_to_mul;
		lhs = lhs - temp_to_sub;
	}
	
	return result;
}

BigNat MOD_NN_N(BigNat lhs, BigNat rhs){
	/* Returns (lhs mod rhs) */
	
	BigNat temp = lhs / rhs;
	temp = temp * rhs;
	BigNat result = lhs - temp;
	
	return result;
}

BigNat GCD_NN_N(BigNat lhs, BigNat rhs){
	/* Returns Greatest Common Divisor of lhs and rhs */
	
	assert(("GCD_NN_N lhs == 0 or rhs == 0", NZER_N_B(lhs) && NZER_N_B(rhs)));
	
	while(NZER_N_B(rhs)){
		lhs = lhs % rhs;
		std::swap(lhs, rhs);
	}
	return lhs;
};

BigNat LCM_NN_N(BigNat &lhs, BigNat &rhs){
	/* Returns Least Common Multipler of lhs and rhs */
	
	//LCM(A,B) = (A*B) / GCD(A,B)
	BigNat gcd = GCD_NN_N(lhs, rhs);
	
	BigNat result = lhs / gcd * rhs;

	return result;	
};

//=====Extra modules======
BigNat FACTOR_N_N(BigNat n){
	BigNat result("1");
	
	for(BigNat i("1"); i <= n; i++){
		result = result * i;		
	}
	
	return result;
};

BigNat FIB_N_N(BigNat n){
	BigNat prev("0");
	BigNat curr("1");
	
	for(BigNat i("0"); i < n; i++){
		BigNat t = prev;
		prev = curr;
		curr = curr + t; 		
	}
	
	return prev;
};

//======OPERATORS===========

BigNat BigNat::operator++(int num){
	*this = ADD_1N_N(*this);
	return *this; 
};

BigNat BigNat::operator+(BigNat &rhs){
	return ADD_NN_N(*this, rhs);
};

BigNat BigNat::operator-(BigNat &rhs){
	return SUB_NN_N(*this, rhs);
};

BigNat BigNat::operator*(BigNat &rhs){
	return MUL_NN_N(*this, rhs);
};

BigNat BigNat::operator*(int &rhs){
	return MUL_ND_N(*this, rhs);
};

BigNat BigNat::operator/(BigNat &rhs){
	return DIV_NN_N(*this, rhs);
};

BigNat BigNat::operator%(BigNat &rhs){
	return MOD_NN_N(*this, rhs);
};

bool BigNat::operator<(BigNat rhs){
	return COM_NN_D(*this, rhs) == CompareNat(rhsIsBigger);
};

bool BigNat::operator>(BigNat rhs){
	return COM_NN_D(*this, rhs) == CompareNat(lhsIsBigger);
};

bool BigNat::operator==(BigNat rhs){
	return COM_NN_D(*this, rhs) == CompareNat(equal);
};

bool BigNat::operator<=(BigNat rhs){
	return (*this < rhs) || (*this == rhs);
};

bool BigNat::operator>=(BigNat rhs){
	return (*this > rhs) || (*this == rhs);
};
