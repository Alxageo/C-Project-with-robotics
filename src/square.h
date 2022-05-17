#ifndef SQUARE
#define SQUARE

#include <iostream>

using namespace std;

// H klash poy anaparista mia thesh ston kosmo. Epeidh einai arketa aplh den
// dhmioyrghsame arxeio me tis ylopoihseis twn synarthsewn.
class Square {
public:
	// Oria gia tis periektikotites
	enum {PALLADIO_MIN = 300, IRIDIO_MIN = 150, LEYKOXRYSOS_MIN = 120};
	enum {PALLADIO_MAX = 3000, IRIDIO_MAX = 1500, LEYKOXRYSOS_MAX = 1200};

	// Dhmioyrgos poy ftiaxnei mia kenh thesh
	Square()
	{
		palladio = iridio = leykoxrysos = 0;
		danger = 0.0f;
		flag = false;
	}

	// Anathesh idiothtwn
	void set_palladio(int poso) { palladio = poso; }
	void set_iridio(int poso) { iridio = poso; }
	void set_leykoxrysos(int poso) { leykoxrysos = poso; }
	void set_danger(float d) { danger = d; }
	void set_flag(bool f) { flag = f; }

	// Prosbash se idiothtes
	int get_palladio() const { return palladio; }
	int get_iridio() const { return iridio; }
	int get_leykoxrysos() const { return leykoxrysos; }
	float get_danger() const { return danger; }
	bool get_flag() const { return flag; }

	// Ektypwsh
	void print() {
		cout << "Palladio: " << palladio << ", Iridio: " << iridio;
		cout << ", Leykoxrysos: " << leykoxrysos << ", Danger: " << danger << endl;
		if (get_flag())
			cout << "Yparxei shmaia kindynoy!" << endl;
	}

private:
	// Periektikothtes
	int palladio;
	int iridio;
	int leykoxrysos;
	// Epikindynothta
	float danger;
	// Shmaia kindynoy
	bool flag;

};

#endif /* SQUARE */
