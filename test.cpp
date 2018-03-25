template<class T>
bool check(T expectation, T reality){
	return expectation == reality;
}

bool testNat(){
	BigNat zero("0"), one("1"), a("145"), b("45");
	
	bool isOK = true;
	
	isOK &= check<BigNat>(a + b, BigNat("190"));
	isOK &= check<BigNat>(a - b, BigNat("100"));
	isOK &= check<BigNat>(a / b, BigNat("3"));
	isOK &= check<BigNat>(a * b, BigNat("6525"));
	
	isOK &= check<BigNat>(a + zero, a);
	isOK &= check<BigNat>(a - zero, a);
	//isOK &= check(a / zero, BigNat("3"));
	isOK &= check<BigNat>(a * zero, zero);
	
	isOK &= check<BigNat>(a + one, BigNat("146"));
	isOK &= check<BigNat>(a - one, BigNat("144"));
	isOK &= check<BigNat>(a / one, a);
	isOK &= check<BigNat>(a * one, a);
	
	return isOK;
}

void testAll(){
	std::cout << "Naturals test: " << testNat();
}
