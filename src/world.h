#ifndef WORLD
#define WORLD

#include <vector>

using namespace std;

#include "robot.h"
#include "map.h"

// H klash poy anaparista olo ton kosmo. Tis periplokes synarthseis tis grafoyme
// sto world.cpp gia na einai pio katharo to arxeio ayto kai na fainetai kalytera
// h klash. Tis poly aples synarthseis tis afhnoyme edw.
class World {
public:
	// Times poy mporei na exei h trexoysa katastash toy kosmoy
	enum { FAILURE, SUCCESS, RUNNING };

	// Arithmos Robot ston kosmo.
	enum { ROBOT_MIN = 100, ROBOT_MAX = 220 };

	// Dhmioyrgos toy kosmoy. H perissoterh doyleia ginetai sthn initialize()
	World();

	// Arxikopoihsh toy kosmoy, dhmioyrgei to xarth kai ta robot.
	void initialize();

	// Synarthseis gia thn ektelesh diaforwn gegonotwn ston kosmo
	void stoixeia_oxhmatos();
	void stoixeia_edafoys();
	void statistika();
	void next_round();
	void neo_oxhma();
	void allagh_theshs();
	void proklhsh_blabhs();
	void diorthosh_blabhs();

	// Ti katastash exei o kosmos tora?
	int status() const { return cur_status; }

private:
	int cur_status;	// Trexoysa katastash toy kosmoy.
	Map map;		// O xarths toy kosmoy.
	// Ta Robot apothikeyontai se ena vector.
	// Kratame deikth pros ayta giati diaforetika de doyleyoyn
	// oi polymorphikes klhseis.
	vector <Robot*> robots;

	void print_map();
};

#endif /*WORLD*/
