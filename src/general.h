// Genikes boithitikes synarthseis

#ifndef GENERAL
#define GENERAL

#include <iostream>
#include <limits>

#include <cstdlib>

// Dhmioyrgei ena tyxaio akeraio >=min kai mikrotero apo max.
inline int rand_int(int min, int max) {
	int range = max - min;
	int val = rand() % range;
	return min+val;
}

// Dhmioyrgei ena tyxaio float >= mina kai mikrotero apo max.
inline float rand_float(float min, float max) {
	float range = max - min;
	float val = rand();
	val = range*val/RAND_MAX;
	return min+val;
}

// Diabazei ena arithmo apo to cin me orio min, max kai xeirismo lathos eisodou.
// Apo: http://www.parashift.com/c++-faq-lite/istream-and-ignore.html
inline int read_cin(const char * message, int minv, int maxv) {
	int result;
	while (	(std::cout << message << "[" << minv << " - " << maxv << "] ? ") &&
			(!(std::cin >> result) || result < minv || result > maxv))
	{
		std::cout << "Parakalw eisagete akeraio apo " << minv << " ews " << maxv << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return result;
}

#endif /* GENERAL */
