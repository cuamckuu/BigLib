#include "big_n.h"

#ifndef BIG_Z_H
#define BIG_Z_H 

enum Sign : int {zero, negative, positive};

class BigInt : public BigNat{

private:	
	bool isNegative;
	
public:
	//=====MODULES=====
	//Author: Alex Kosh 7301
	friend std::ostream& operator<< (std::ostream &stream, const BigInt &num);
	friend std::istream& operator>> (std::istream &stream, BigInt &num);
	
	friend BigNat ABS_Z_N(BigInt lhs); 				 
	friend int POZ_Z_D(BigInt lhs); 				 
	friend BigInt MUL_ZM_Z(BigInt lhs); 			 
	friend BigInt TRANS_N_Z(BigNat lhs); 			 
	friend BigNat TRANS_Z_N(BigInt lhs); 			 
	friend BigInt ADD_ZZ_Z(BigInt lhs, BigInt rhs);  
	friend BigInt SUB_ZZ_Z(BigInt lhs, BigInt rhs);  
	friend BigInt MUL_ZZ_Z(BigInt lhs, BigInt rhs);  
	friend BigInt DIV_ZZ_Z(BigInt lhs, BigInt rhs);  
	friend BigInt MOD_ZZ_Z(BigInt lhs, BigInt rhs);  
	
	//====Friends for BigFra======
	friend BigFra TRANS_Z_Q(BigInt lhs);
	
	//====Extra modules==========
	friend BigInt POW_ZZ_Z(BigInt lhs, BigInt rhs);
	
	//============================
	//======Operators support======
	BigInt operator+(const BigInt &rhs);
	BigInt operator-(const BigInt &rhs);
	BigInt operator-();
	BigInt operator*(const BigInt &rhs);
	BigInt operator/(const BigInt &rhs);
	BigInt operator%(const BigInt &rhs);
	
	bool operator<(const BigInt &rhs);
	bool operator>(const BigInt &rhs);
	bool operator<=(const BigInt &rhs); 
	bool operator>=(const BigInt &rhs);
	bool operator==(const BigInt &rhs);
	bool operator!=(const BigInt &rhs);
	
	//=============================
	
	BigInt();
	BigInt(std::string str);
	BigInt(BigNat num, bool isNegative);
};



#endif
