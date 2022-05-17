#ifndef ROBOT
#define ROBOT

#include <iostream>
#include <vector>

#include "map.h"

using namespace std;

// Ayth h klash einai ena geniko Robot, ta eidikeymena Robot klhronomoyne apo
// ayth. H synarthsh leitoyrgia() einai afhrhmenh ( pure virtual ).
// Mia synarthsh symbolo() epistrefei ena ektypwsimo symbolo gia thn probolh
// toy Robot sthn konsola entolwn kai einai epishs virtual.
// Gia eykolh ektyposh kaname kai mia synarthsh print() epishs virtual.
class Robot {
public:
	Robot(Map & myMap);

	// Anathesh idiothtwn
	void set_taxythta(int poso)   { taxythta = poso; }
	void set_leitoyrgei(bool l)   {
		// Edw metrame kai tis blabes an kapoios mas leei oti de leitoyrgoyme...
		leitoyrgei = l;
		if (l)
			xronos_xalasmeno = 0;
		else {
			n_blabes++;
			blabes_synolo++;
		}
	}
	void set_prosbash(float poso) { prosbash = poso; }
	void set_x(int x)             { my_x = x; }
	void set_y(int y)			  { my_y = y; }

	// Prosbash se idiothtes
	int get_taxythta() const    { return taxythta; }
	bool get_leitoyrgei() const { return leitoyrgei; }
	float get_prosbash() const  { return prosbash; }
	int get_x() const           { return my_x; }
	int get_y()	const 		    { return my_y; }

	// Elegxos gia aposyrsh
	// Ikanothtes enos Robot
	void metakinhsh();
	virtual void leitoyrgia() = 0;
	virtual char symbolo() { return 'R'; }

	bool gia_aposyrsh() { return xronos_xalasmeno > 15; }
	// Ektypwsh toy Robot. Einai virtual giati px to robot analyshs tha mas pei
	// kai poso fortio exei ktl...
	virtual void print() {
		cout << this->symbolo() << "-" << id << ": Taxythta: " << taxythta;
		cout << ", Leitoyrgei: " << leitoyrgei << ", Ikanothta prosbashs: " << prosbash << endl;
		cout << "Thesh: (" << my_x << ", " << my_y <<"), Arithmos kinhsewn: " << n_kinhseis << ", Arithmos blabwn: " << n_blabes << endl;
	}
	// Katastrofeas.
	// Prepei na einai virtual panta otan yparxoyn virtual synarthseis, akoma kai
	// an den kanei tipota.
	virtual ~Robot() {}

	// Statistika toy stoloy. Ta afhnoyme public gia eykolia prosbashs.
	static int blabes_synolo;
	static int palladio_synolo;
	static int iridio_synolo;
	static int leykoxrysos_synolo;
	static int shmaies_synolo;

protected:	// Boithaei na exoyn prosbash oi ypoklaseis toy Robot stis akoloythes metablites.
	// H thesh mas sto xarth.
	int my_x, my_y;

	// O xarths poy brisketai to Robot.
	Map & map;

	// Enas kodikos gia na einai ksexwristo to Robot apo ta alla.
	int id;

	// Arithmos kinhsewn kai blabwn
	int n_kinhseis, n_blabes;

private:
	int taxythta;		// Poses theseis metakineite se kathe gyro
	bool leitoyrgei;	// Katastash leitoyrgias
	float prosbash;		// Ikanothta prosbashs

	int xronos_xalasmeno;	// Posoys gyroys einai xalasmeno?

	static int next_id;	// Epomenos kodikos gia neo Robot.
};

// Klash Robot eksereynhshs.
class RobotExplore : public Robot {
public:
	RobotExplore(Map & myMap) : Robot(myMap) { }
	void leitoyrgia();
	char symbolo() { return 'E'; }
	void print() {
		cout << "Eksereynhtiko oxhma ";
		Robot::print();
	}
};

// Klash Robot analyshs.
class RobotAnalyze : public Robot {
public:
	RobotAnalyze(Map & myMap) : Robot(myMap) { fortio_iridioy = fortio_palladioy = fortio_leykoxrysoy = 0;}

	void leitoyrgia();
	char symbolo() { return 'A'; }
	void print() {
		cout << "Oxhma Analyshs ";
		Robot::print();
		cout << "Fortio: " << get_synoliko_fortio() << "/" << megisto_fortio << endl;
	}

	// Epipleon synarthseis gia fortio kai xoro.
	void set_megisto_fortio(int poso) { megisto_fortio = poso; }
	int get_synoliko_fortio() { return fortio_iridioy + fortio_palladioy + fortio_leykoxrysoy; }
	int get_eleytheros_xoros() { return megisto_fortio - get_synoliko_fortio(); }

private:
	int megisto_fortio;
	int fortio_palladioy;
	int fortio_iridioy;
	int fortio_leykoxrysoy;
};

// Klash Robot diaswshs.
class RobotRescue : public Robot {
public:
	RobotRescue(Map & myMap) : Robot(myMap) { }
	void leitoyrgia();
	char symbolo() { return 'S'; }
	void print() {
		cout << "Oxhma Diaswshs ";
		Robot::print();
	}
	// Mia synarthsh gia na syndeetai to robot me ta ypoloipa yparxonta robot.
	void set_robot_list(vector<Robot *> *lp) { robot_list_p = lp; }
private:
	// H lista me ola ta Robot, giati ta Robot diaswshs prepei na epenergoyn
	// se ayta.
	vector<Robot *> *robot_list_p;
};

// Synarthsh dhmioyrgias tyxaioy Robot apo ta diathesima. An de dothei typos,
// dhmioyrgei ena tyxaio typo.
Robot * make_robot(Map & map, int typos = -1);

#endif /*ROBOT*/
