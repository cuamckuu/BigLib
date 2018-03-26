#include "big_z.h"

#ifndef BIG_Q_H
#define BIG_Q_H

class BigFra{

private:
	BigInt numerator;
	BigInt denominator;

public:
	friend std::ostream& operator<< (std::ostream &stream, BigFra num);
	friend std::istream& operator>> (std::istream &stream, BigFra &num);

	//=====MODULES=====
	//Author: Demid Tremp 7301

	friend bool INT_Q_B(BigFra lhs);
	friend BigFra TRANS_Z_Q(BigInt lhs);
	friend BigInt TRANS_Q_Z(BigFra lhs);
	friend BigFra MUL_QQ_Q(BigFra lhs, BigFra rhs);
	friend BigFra DIV_QQ_Q(BigFra lhs, BigFra rhs);

	//Author: Stepan Fed
	friend BigFra RED_Q_Q(BigFra lhs);
	friend BigFra ADD_QQ_Q(BigFra lhs, BigFra rhs);
	friend BigFra SUB_QQ_Q(BigFra lhs, BigFra rhs);
	friend BigFra support_fac_p_q(std::vector<BigFra> elem);

	//======Operators support======
	BigFra operator+(const BigFra &rhs);
	BigFra operator-(const BigFra &rhs);
	BigFra operator/(const BigFra &rhs);
	BigFra operator*(const BigFra &rhs);

	bool operator<(const BigFra &rhs);
	bool operator>(const BigFra &rhs);
	bool operator<=(const BigFra &rhs);
	bool operator>=(const BigFra &rhs);
	bool operator==(const BigFra &rhs);
	bool operator!=(const BigFra &rhs);

	//===================
	BigFra();
	BigFra(BigInt numenator, BigInt denuminator);
	BigFra(std::string str);
	void normalise();
	std::string to_float(int precision);
};

#endif
