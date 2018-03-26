#include "big_q.h"

class BigPol{
private:
    std::vector<BigFra> coefs;

public:
    friend std::ostream& operator<<(std::ostream &stream, const BigPol &pol);

    //=====MODULES=====
    //Author:

    //======================
    //==EXTRA MODULES==
    BigFra calculate(BigFra x); // Calculate polynom value, returns result
    friend BigPol ADD_PP_P(BigPol lhs, BigPol rhs);
    friend BigPol MUL_PQ_P(BigPol lhs, BigFra rhs);
    friend BigPol SUB_PP_P(BigPol lhs, BigPol rhs);
    friend BigPol MUL_Pxk_P(BigPol lhs, int k);
    friend BigPol MUL_PP_P(BigPol lhs, BigPol rhs);


    //==Demid's sheet==========
    friend BigFra FAC_P_Q(BigPol lhs);

    //======Operators support======
    BigPol operator+(const BigPol &rhs);
    BigPol operator-(const BigPol &rhs);
    BigPol operator*(const BigFra &rhs);
    BigPol operator*(const BigPol &rhs);
    BigPol operator*(const int &rhs);
    //BigPol operator*(const BigPol &rhs);

    BigPol operator/(const BigPol &rhs);
    BigPol operator%(const BigPol &rhs);
    bool operator==(const BigPol &rhs);

    //=============================

    BigPol(std::string str);

};