#ifndef MAP
#define MAP

#include <iostream>
using namespace std;
#include "square.h"

// Klash poy anaparista to xarth poy ekselissetai h prosomoiwsh.
// Oysiastika einai enas aplos disdiastatos pinakas, alla prosferei kai kapoies
// epipleon leitoyrgies.
class Map {
public:
	// Times gia tis diastaseis toy xarth
	enum { PLATOS = 50, YPSOS = 15 };

	// Fortio mexri na gemisei h bash
	enum { PALLADIO_MAX = 100000, IRIDIO_MAX = 50000, LEYKOXRYSOS_MAX = 25000 };

	// Dhmioyrgei ena keno xarth. Ta tetragwna exoyn typikes times (0...).
	// Epishs mhdenizei to periexomeno ths bashs.
	Map() { base_palladio = base_iridio = base_leykoxrysos = 0; }

	// Epistrefei mia anafora sto tetragwno stis syntetagmenes x,y.
	Square & get_square(int x, int y) { return squares[x][y]; }

	// Elegxei an yparxei tetragwno poy na mhn einai "markarismeno" gyro apo to x,y.
	bool yparxei_amarkaristo(int x, int y) const {
		for (int mx = x - 1; mx <= x + 1; mx++)
			for (int my = y - 1; my <= y + 1; my++)
			{
				if (mx >=0 && mx < PLATOS && my >=0 && my < YPSOS && (mx != x || my != y))
					if (squares[mx][my].get_flag() == false)
						return true;
			}
		return false;
	}

	// Topothethsh ths bashs sto xarth
	void set_base_x(int x) { base_x = x; }
	void set_base_y(int y) { base_y = y; }

	// Thesh ths bashs sto xarth
	int get_base_x() const { return base_x; }
	int get_base_y() const { return base_y; }

	// Ksefortoma porwn sth bash. Kaleitai sth leitoyrgia() enos RobotAnalyze.
	void ksefortoma(int palladio, int iridio, int leykoxrysos) {
		base_palladio += palladio;
		base_iridio += iridio;
		base_leykoxrysos += leykoxrysos;
	}

	// Xrhsimopoioyntai apo ta RobotAnalyze gia na mh metaferoyn axrhstoys poroys sth bas
	bool bash_palladio_full()    { return base_palladio >= PALLADIO_MAX; }
	bool bash_iridio_full()      { return base_iridio >= IRIDIO_MAX; }
	bool bash_leykoxrysos_full() { return base_leykoxrysos >= LEYKOXRYSOS_MAX; }

	// Elegxei an gemise h bash
	bool bash_gemath() {
		cout << "Bash Palladio: " << base_palladio << ", Iridio: " << base_iridio << ", Leykoxrysos: " << base_leykoxrysos << endl;
		return bash_palladio_full() && bash_iridio_full() && bash_leykoxrysos_full();
	}

private:
	Square squares[PLATOS][YPSOS];
	// Thesh ths bashs.
	int base_x, base_y;
	// Fortio sth bash
	int base_palladio, base_iridio, base_leykoxrysos;
};

#endif /* MAP */
