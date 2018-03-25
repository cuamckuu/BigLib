#include "include/big_p.h"

std::ostream& operator<<(std::ostream &stream, const BigPol &pol){
    for (int i = pol.coefs.size() - 1; i >= 0; --i) {
        stream << pol.coefs[i] << ' ';
    }
    return stream;
}

BigPol::BigPol(std::string str) {
    int size;
    for (int i = str.length() - 1; i >= 0; i-=(size + 2)){

        size = 0;

        std::string s = "";

        while(str[i - size] != ' '){
            s += str[i - size];
            size++;
        }

        BigInt denom(s);

        s = "";
        while(i - size - 1 >= 0 && str[i - size - 1] != ' '){
            s += str[i - size - 1];
            size++;
        }
        BigInt num(s);

        coefs.push_back(BigFra(num, denom));
    }
}

BigPol ADD_PP_P(BigPol lhs, BigPol rhs) {
    BigPol result = lhs;
    int max_len = std::max(result.coefs.size(), rhs.coefs.size());
    for(int i = 0; i < max_len; i++){

        if(i < result.coefs.size())
            result.coefs[i] = result.coefs[i] + (i < rhs.coefs.size() ? rhs.coefs[i] : BigFra(BigInt("0"), BigInt("1")));
        else
            result.coefs.push_back(rhs.coefs[i]);
    }
    return result;
}

BigPol MUL_PQ_P(BigPol lhs, BigFra rhs) {
    for(int i = 0; i < lhs.coefs.size(); i++){
        lhs.coefs[i] = lhs.coefs[i] * rhs;
    }

    return lhs;
}

BigPol SUB_PP_P(BigPol lhs, BigPol rhs) {
    BigFra temp(BigInt("-1"), BigInt("1"));
    rhs = rhs * temp;
    return ADD_PP_P(lhs, rhs);
}

BigPol MUL_Pxk_P(BigPol lhs, int k) {

    int size = lhs.coefs.size();
    for (int j = 0; j < k; ++j) {
        lhs.coefs.push_back(BigFra(BigInt("0"), BigInt("1")));
    }
    for (int i = size + k - 1; i >= k; --i) {
            lhs.coefs[i] = lhs.coefs[i - k];
            lhs.coefs[i - k] = BigFra(BigInt("0"), BigInt("1"));
    }
    return lhs;
}

BigPol MUL_PP_P(BigPol lhs, BigPol rhs) {

    BigPol result = lhs * rhs.coefs[0];

    for (int i = 1; i < rhs.coefs.size(); ++i) {

        BigPol anotherPol = lhs * rhs.coefs[i];
        anotherPol = anotherPol * i;
        result = result + anotherPol;
    }
    return result;
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

BigPol BigPol::operator*(const int &rhs) {
    return MUL_Pxk_P(*this, rhs);
}

BigPol BigPol::operator*(const BigPol &rhs) {
    return MUL_PP_P(*this, rhs);
}
