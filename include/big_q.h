#include "big_z.h"

#ifndef BIG_Q_H
#define BIG_Q_H

class BigFra{
	BigInt numerator;
	BigInt denominator;

public:
	friend std::ostream& operator<< (std::ostream &stream, BigFra num);

    //=====MODULES=====
    //Author: Alex Kosh 7301
    //Problems witr cout function return

    friend BigFra RED_Q_Q(BigFra lhs); //cheched c:
    friend bool INT_Q_B(BigInt lhs, BigInt rhs); //checked c:
	friend BigFra TRANS_Z_Q(BigInt lhs);
	friend BigInt TRANS_Q_Z(BigFra lhs);
    friend BigFra ADD_QQ_Q(BigFra lhs, BigFra rhs);
    friend BigFra SUB_QQ_Q(BigFra lhs, BigFra rhs);
    friend BigFra MUL_QQ_Q(BigFra lhs, BigFra rhs);
    friend BigFra DIV_QQ_Q(BigFra lhs, BigFra rhs);

    friend void toString(std::ostream &stream, BigFra lhs, int digits);
    void normalise();
    
    BigFra operator+(const BigFra &rhs);
    BigFra operator-(const BigFra &rhs);
    BigFra operator/(const BigFra &rhs);
    BigFra operator*(const BigFra &rhs);
    
	BigFra(BigInt numenator, BigInt denuminator);
	BigFra(std::string str);

};

#endif
