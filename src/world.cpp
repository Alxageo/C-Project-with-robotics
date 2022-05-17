#include "world.h"
#include "robot.h"
#include "general.h"

// public synarthseis

World::World()
{
	cur_status = RUNNING;
}

void World::initialize()
{
	int x, y;
	// Arxikopoihsh toy xarth.
	for (y=0; y<Map::YPSOS;  y++)
		for (x=0; x<Map::PLATOS; x++)
		{
			map.get_square(x,y).set_palladio( rand_int(Square::PALLADIO_MIN, Square::PALLADIO_MAX) );
			map.get_square(x,y).set_iridio( rand_int(Square::IRIDIO_MIN, Square::IRIDIO_MAX) );
			map.get_square(x,y).set_leykoxrysos( rand_int(Square::LEYKOXRYSOS_MIN, Square::LEYKOXRYSOS_MAX) );
			map.get_square(x,y).set_danger( rand_float(0.0f, 0.9f) );
		}
	// Epilogh mias theshs gia th bash
	map.set_base_x(rand_int(0, Map::PLATOS));
	map.set_base_y(rand_int(0, Map::YPSOS));
	// Topothetisi merikwn Robot.
	int n_robots = rand_int(ROBOT_MIN, ROBOT_MAX);
	while (n_robots--)
	{
		Robot * robot = make_robot(map);
		RobotRescue * res;
		if ( ( res = dynamic_cast<RobotRescue *>(robot)) != 0)
			res->set_robot_list(&robots);
		robots.push_back( robot );
	}

}

void World::stoixeia_oxhmatos()
{
	int n;
	cout << "Yparxoyn ayth th stigmh: " << robots.size() << " oxhmata" << endl;
	n = read_cin("Arithmos oxhmatos?", 1, robots.size());
	robots[n-1]->print();
}

void World::stoixeia_edafoys()
{
	int x, y;
	x = read_cin("Syntetagmenh X ", 0, Map::PLATOS - 1);
	y = read_cin("Syntetagmenh Y ", 0, Map::YPSOS - 1);
	map.get_square(x, y).print();
}

void World::statistika()
{
	// Ektyposh statistikwn toy stoloy
	cout << "Statistika stoloy kai kosmoy." << endl << endl;
	cout << "Arithmos blabwn ws twra      : " << Robot::blabes_synolo << endl;
	cout << "Arithmos shmaiwn kindynoy    : " << Robot::shmaies_synolo << endl;
	cout << "Palladio (kgr)               : " << Robot::palladio_synolo << endl;
	cout << "Iridio (kgr)                 : " << Robot::iridio_synolo << endl;
	cout << "Leykoxrysos (kgr)            : " << Robot::leykoxrysos_synolo << endl;
	// Ypologismos statistikwn gia to xarth
	float danger_sum = 0.0f;
	int palladio = 0;
	int iridio = 0;
	int leykoxrysos = 0;
	for (int x = 0; x < Map::PLATOS; ++x)
		for (int y = 0; y < Map::YPSOS; ++y)
		{
			danger_sum += map.get_square(x,y).get_danger();
			palladio += map.get_square(x,y).get_palladio();
			iridio += map.get_square(x,y).get_iridio();
			leykoxrysos += map.get_square(x,y).get_leykoxrysos();
		}
	// Ektyposh statistikwn toy xarth
	cout << endl;
	cout << "Mesos kindynos               : " << danger_sum/(Map::PLATOS*Map::YPSOS) << endl;
	cout << "Palladio sto xarth           : " << palladio << endl;
	cout << "Iridio sto xarth             : " << iridio << endl;
	cout << "Leykoxrysos sto xarth        : " << leykoxrysos << endl;
}

void World::next_round()
{
	// Kinoyme kai leitoyrgoyme kathe Robot.
	for (size_t i = 0; i < robots.size(); ++i)
	{
		robots[i]->metakinhsh();
		robots[i]->leitoyrgia();
	}
	// Kanoyme aposyrsh se Robot poy emeinan poly kairo akinhta
	for (size_t i = 0; i < robots.size(); ++i)
	{
		if (robots[i]->gia_aposyrsh())
		{
			robots.erase(robots.begin() + i);
		}
	}
	print_map();
	// An gemise h bash tote h prosomoiwsh exei epityxia.
	if (map.bash_gemath())
		cur_status = SUCCESS;
	else {
		// An ola ta robot einai ektos leitoyrgias h prosomoiwsh exei apotyxia.
		bool all_fail = true;
		for (size_t i = 0; i < robots.size(); ++i)
			if (robots[i]->get_leitoyrgei())
				all_fail = false;
		if (all_fail)
			cur_status = FAILURE;
	}
}

void World::neo_oxhma()
{
	int x, y;
	cout << "Dhmioyrgia neoy oxhmatos" << endl;
	x = read_cin("Syntetagmenh X ", 0, Map::PLATOS - 1);
	y = read_cin("Syntetagmenh Y ", 0, Map::YPSOS - 1);
	int typos;
	typos = read_cin("1. Eksereynhshs, 2. Analyshs, 3. Diasoshs ", 1, 3);
	Robot * robot = make_robot(map, typos);
	robot->set_x(x);
	robot->set_y(y);
	// Ta robot diaswshs xreiazontai mia anafora sth lista me ola ta alla robot.
	if (typos == 3) {
		dynamic_cast<RobotRescue *>(robot)->set_robot_list(&robots);
	}
	robots.push_back(robot);
	print_map();
}

void World::allagh_theshs()
{
	int x, y;
	x = read_cin("Syntetagmenh X ", 0, Map::PLATOS - 1);
	y = read_cin("Syntetagmenh Y ", 0, Map::YPSOS - 1);
	map.get_square(x, y).print();
	int val;
	val = read_cin("Palladio ", Square::PALLADIO_MIN, Square::PALLADIO_MAX);
	map.get_square(x, y).set_palladio(val);
	val = read_cin("Iridio ", Square::IRIDIO_MIN, Square::IRIDIO_MAX);
	map.get_square(x, y).set_iridio(val);
	val = read_cin("Leykoxrysos ", Square::LEYKOXRYSOS_MIN, Square::LEYKOXRYSOS_MAX);
	map.get_square(x, y).set_leykoxrysos(val);
	val = read_cin("Kindynos (%) ", 0, 90);
	map.get_square(x, y).set_danger(val/100.0f);

}

void World::proklhsh_blabhs()
{
	int n;
	cout << "Yparxoyn ayth th stigmh: " << robots.size() << " oxhmata" << endl;
	n = read_cin("Arithmos oxhmatos?", 1, robots.size());
	n--;
	if (robots[n]->get_leitoyrgei())
		robots[n]->set_leitoyrgei(false);
	else
		cout << "Ayto to oxhma einai hdh xalasmeno!" << endl;
}

void World::diorthosh_blabhs()
{
	int n;
	cout << "Yparxoyn ayth th stigmh: " << robots.size() << " oxhmata" << endl;
	n = read_cin("Arithmos oxhmatos?", 1, robots.size());
	n--;
	if (!robots[n]->get_leitoyrgei())
		robots[n]->set_leitoyrgei(true);
	else
		cout << "Ayto to oxhma leitoyrgei apsoga!" << endl;}

// private synarthseis

// Typwnei to xarth ths prosomoiwshs
void World::print_map()
{
	for (int y = 0; y<Map::YPSOS; ++y)
	{
		for (int x = 0; x<Map::PLATOS; ++x)
		{
			if (x == map.get_base_x() && y == map.get_base_y())
				cout << "B";
			else {
				size_t i;
				// Anazhthsh gia Robot sth thesh x,y
				for (i = 0; i < robots.size(); ++i)
					if (robots[i]->get_x() == x && robots[i]->get_y() == y)
						break;
				// An yparxei Robot typwnetai to symbolo toy
				if (i < robots.size()) {
					cout << robots[i]->symbolo();
				}
				else {
					// Alliws typwnetai ! an exei shmaia to tetragwno ws epikindyno,
					// enw typwnetai 'keno' an den exei shmaia (mporei kai na
					// einai epikindyno apla ta robot den to kseroyn akoma)
					if (map.get_square(x,y).get_flag())
						cout << "!";
					else
						cout << " ";
				}
			}
		}
		cout << endl;
	}
}
