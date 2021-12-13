#include <iostream>
#include <vector>
#include "trit.h"
#include <cassert>



int main() {

	TritSet set(10);

	//----------getSize()--------------
	assert(set.getSize() == 10);
	// std::cout << set.getSize() << std::endl;


	//---------operator<<--------------
	std::cout << set << std::endl;
	for (int i = 0; i < set.getSize(); i++) {
		std::cout << set[i] << ' ';
	}
	std::cout << std::endl;

	//----------setting getting trits----
	set[3] = Unknown;
	set[5] = True;
	assert(set[3] == Unknown);
	assert(set[5] == True);
	assert(set[6] == Unknown);
	assert(set[1000000] == Unknown);


	int trit1 = 0;
	int trit2 = 0;
	trit1 = set[3];
	trit2 = set[5];
	assert(trit1 == Unknown);
	assert(trit2 == True);

	//--------resize------------------
	assert(set.getCapacity() >= 10 * 2 / 8 / sizeof(uint));
	assert(set.getSize() == 10);

	set.resize(12);
	assert(set.getCapacity() >= 12 * 2 / 8 / sizeof(uint));
	assert(set.getSize() == 12);

	set.resize(43);
	assert(set.getCapacity() >= 43 * 2 / 8 / sizeof(uint));
	assert(set.getSize() == 43);

	set.resize(3);
	assert(set.getCapacity() >= 3 * 2 / 8 / sizeof(uint));
	assert(set.getSize() == 3);
	
	//-------------copy---------------
	set = TritSet(10);
	TritSet set2(5);

	set[10] = False;

	set2 = set;
	assert(set.getSize() == set2.getSize());
	assert(set.getCapacity() == set2.getCapacity());
	assert(set[10] == set2[10]);

	set2[10] = True;

	assert(set[10] != set2[10]);
	
	//------------- |, &, ~ ------------------

	TritSet test1(9);
	TritSet test2(5);

	test1[0] = False;
	test1[1] = False;
	test1[2] = False;
	test1[3] = True;
	test1[4] = True;
	test1[5] = True;

	test2[0] = Unknown;
	test2[2] = False;
	test2[3] = Unknown;
	test2[4] = True;	

	TritSet res(3);

	res = test1 & test2;

	std::cout << test1 << std::endl << test2 << std::endl << res << std::endl;

	assert(res.getSize() == 9);
	assert(res[0] == False);
	assert(res[2] == False);
	assert(res[3] == Unknown);


	res = test1 | test2;
	
	assert(res.getSize() == 9);
	assert(res[0] == Unknown);
	assert(res[2] == False);
	assert(res[3] == True);

	res = ~res;

	assert(res[0] == Unknown);
	assert(res[2] == True);
	assert(res[3] == False);

	//-----------???------------------

	size_t allocd = res.getCapacity();
	size_t size = res.getSize();

	res[10000] = Unknown;

	assert(allocd == res.getCapacity());
	assert(size == res.getSize());

	return 0;
}
