#include "big_q.h"

class BigPol{
private:
	std::vector<BigFra> coefs;
	
public:
	friend std::ostream& operator<<(std::ostream &stream, const BigFra &pol);
	
	//=====MODULES=====
	//Author: 
	
	//======================
	//==EXTRA MODULES==
	BigFra calculate(BigFra x); // Calculate polynom value, returns result 
	
	//======Operators support======
	BigPol operator+(const BigPol &rhs);
	BigPol operator-(const BigPol &rhs);
	BigPol operator*(const BigPol &rhs);
	BigPol operator*(const int &rhs);
	BigPol operator/(const BigPol &rhs);
	BigPol operator%(const BigPol &rhs);
	
	bool operator==(const BigPol &rhs);
	
	//=============================
	
		
};
