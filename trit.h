#ifndef TRIT_H
#define TRIT_H

#include <vector>
#include <iostream>

#define SET_CON(a,n,b) ( (a) = ((a) & (~(1 << (n)))) | ((b) << (n)) ) //set conditionaly bit
#define SET_BIT(a,n)   ( (a) |= (1 << (n))    ) //set bit
#define GET_BIT(a,n)   ( ((a) >> (n)) & 1     ) //get bit
#define CLR_BIT(a,n)   ( (a) &= (~(1 << (n))) ) //clear bit

enum tritValues {Unknown, False, True};

class ProxyTrit {
private:
	uint* subContainer;
	int index;
public:
	ProxyTrit(uint* _subContainer, int _index) : subContainer(_subContainer), index(_index) {}
	void operator=(const int trit);
	operator int();
	char get();
	friend std::ostream& operator<<(std::ostream& out, ProxyTrit set);
};

class TritSet {
private:
	std::vector<uint> container;
	size_t size;
public:
	friend std::ostream& operator<<(std::ostream& out, TritSet& set);
	explicit TritSet(int size);
	TritSet(const TritSet& set);
	size_t getSize() const;
	void resize(size_t index);
	size_t getCapacity() const;
	ProxyTrit operator[](size_t index);
	TritSet& operator=(const TritSet& set);
	friend TritSet operator|(TritSet& set1, TritSet& set2);
	friend TritSet operator&(TritSet& set1, TritSet& set2);
	TritSet operator~();
};

#endif