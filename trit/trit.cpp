#include <iostream>
#include "trit.h"

const int uintSize = sizeof(uint) * 8 / 2;

//----------------misc--------------------

std::ostream& operator<<(std::ostream& out, ProxyTrit trit) {
	return out << trit.get();
}

std::ostream& operator<<(std::ostream& out, TritSet& set) {
	for (int i = 0; i < set.getSize(); i++) {
		out << set[i] << ' ';
	}
	out << std::endl;
	return out;
}

//-------------TritSet--------------------


TritSet::TritSet(int size) {
	container = {};
	int uint_amo = size / uintSize;
	if (size % uintSize != 0) uint_amo++;
	container.resize(uint_amo);
	this->size = size;
}

TritSet::TritSet(const TritSet& set) : container(set.container), size(set.size) {
//    std::cout << "copy constructor" << std::endl;
}

TritSet& TritSet::operator=(const TritSet& set) {
	container = set.container;
	size = set.size;
	return *this;
}

size_t TritSet::getSize() const {
	return size;
}

ProxyTrit TritSet::operator[](size_t index) {
	if (index > size) return ProxyTrit(nullptr, index);
	return ProxyTrit(&container[index / uintSize], index % uintSize);
}

size_t TritSet::getCapacity() const {
	return container.size();
}

void TritSet::resize(size_t index) {
	int newUintAmo = index / uintSize;
	if (index % uintSize != 0) newUintAmo++;
	container.resize(newUintAmo);
	this->size = index;
}

/*
| u f t
u u u t
f u f t
t t t t
*/

TritSet operator|(TritSet& set1, TritSet& set2) {
	size_t size1 = set1.getSize();
	size_t size2 = set2.getSize();
	size_t totalSize = size1 > size2 ? size1 : size2;

	set1.resize(totalSize);
	set2.resize(totalSize);

	TritSet result(totalSize);
	int valuesTable[3][3] = {{0,0,2},{0,1,2},{2,2,2}};
	for (int i = 0; i < totalSize; i++) {
		result[i] = valuesTable[set1[i]][set2[i]];
	}
	return result;
}

/*
& u f t
u u f u
f f f f
t u f t
*/

TritSet operator&(TritSet& set1, TritSet& set2) {
	size_t size1 = set1.getSize();
	size_t size2 = set2.getSize();
	size_t totalSize = size1 > size2 ? size1 : size2;

	set1.resize(totalSize);
	set2.resize(totalSize);

	TritSet result(totalSize);
	int valuesTable[3][3] = {{0,1,0},{1,1,1},{0,1,2}};
	for (int i = 0; i < totalSize; i++) {
		result[i] = valuesTable[set1[i]][set2[i]];
	}
	return result;
}

/*
u f t
u t f
*/

TritSet TritSet::operator~() {
	TritSet result(*this);

	int valuesTable[3] = {0, 2, 1};
	for (int i = 0; i < size; i++) {
		result[i] = valuesTable[result[i]];
	}

    return result;
}

//-------------ProxyTrit------------------

void ProxyTrit::operator=(const int trit) {
	try {
		if (subContainer == nullptr && trit != Unknown) throw -1;
		if (subContainer == nullptr && trit == Unknown) throw -2;
	}
	catch (int i) {
		if (i == -1) {
			std::cout << "index out of range" << std::endl;
			std::cout << "aborting function" << std::endl;
			return;
		}
		if (i == -2) {
			return;
		}
	}

	switch (trit) {
		case Unknown:
			CLR_BIT(*subContainer, index * 2);
			CLR_BIT(*subContainer, index * 2 + 1);
			// std::cout << "false set" << std::endl;
			break;
		case False:
			SET_BIT(*subContainer, index * 2);
			CLR_BIT(*subContainer, index * 2 + 1);
			// std::cout << "unknown set" << std::endl;
			break;
		case True:
			CLR_BIT(*subContainer, index * 2);
			SET_BIT(*subContainer, index * 2 + 1);
			break;
		default:
			std::cout << "error" << std::endl;
			break;
	}
}

ProxyTrit::operator int() {
	if (subContainer == nullptr) return Unknown;
	int trit = 0;
	SET_CON(trit, 0, GET_BIT(*subContainer, index * 2));
	SET_CON(trit, 1, GET_BIT(*subContainer, index * 2 + 1));
	return trit;
}

char ProxyTrit::get() {
    if (subContainer == nullptr) return 'U';
	uint value = GET_BIT(*subContainer, index * 2 + 1) << 1;
	value += GET_BIT(*subContainer, index * 2);
	switch (value) {
		case True:
			return 'T';
			break;
		case False:
			return 'F';
			break;
		case Unknown:
			return 'U';
			break;
		default:
			std::cout << "error" << std::endl;
			break;
	}
}