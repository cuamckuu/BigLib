#include "big_z.h"

#ifndef BIG_Q_H
#define BIG_Q_H

class BigFra{
	BigInt numerator;
	BigInt denominator;

public:

    BigFra RED_Q_Q(BigFra &lhs);
    bool INT_Q_B(BigInt lhs, BigInt rhs); //checked
	BigFra TRANS_Z_Q(BigInt lhs);
	BigInt TRANS_Q_Z(BigFra lhs);
    BigFra ADD_QQ_Q(BigFra lhs, BigFra rhs);
    BigFra SUB_QQ_Q(BigFra lhs, BigFra rhs);
    BigFra MUL_QQ_Q(BigFra lhs, BigFra rhs);
    BigFra DIV_QQ_Q(BigFra lhs, BigFra rhs);

	BigFra(BigInt numenator, BigInt denuminator); //no realisation;

};

#endif
