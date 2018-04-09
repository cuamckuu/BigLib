#include "big_q.h"

class BigPol{
private:
	std::vector<BigFra> coefs;
	
public:
	//=====MODULES=====
	//Author: Step Fed
	
	friend BigPol ADD_PP_P(BigPol lhs, BigPol rhs);
    friend BigPol SUB_PP_P(BigPol lhs, BigPol rhs);
	friend BigPol MUL_PQ_P(BigPol lhs, BigFra rhs);
    friend BigPol MUL_Pxk_P(BigPol lhs, unsigned int k);
    friend BigPol MUL_PP_P(BigPol lhs, BigPol rhs);
    friend BigPol DIV_PP_P(BigPol lhs, BigPol rhs);
    
    //=====MODULES=====
	//Author: Demid Trem
	friend BigFra LED_P_Q(BigPol lhs);
	friend BigPol DER_P_P(BigPol lhs);
	friend int DEG_P_D(BigPol lhs);
	friend BigPol NMR_P_P(BigPol lhs);

	//=====MODULES=====
	//Author: Alex Kosh
	friend std::ostream& operator<<(std::ostream &stream, BigPol pol);
	friend BigPol MOD_PP_P(BigPol lhs, BigPol rhs);
	BigFra calculate(BigFra x);
	friend BigPol GCD_PP_P(BigPol lhs, BigPol rhs);
	friend BigFra FAC_P_Q(BigPol lhs);
	
	//======Operators support======
	BigPol operator+(const BigPol &rhs);
	BigPol operator-(const BigPol &rhs);
	BigPol operator*(const BigPol &rhs);
	BigPol operator*(const BigFra &rhs);
	BigPol operator/(const BigPol &rhs);
	BigPol operator%(const BigPol &rhs);
	
	bool operator==(const BigPol &rhs);
	
	//=============================
	
	BigPol(std::string str);
	
};
