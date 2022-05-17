#include "robot.h"
#include "general.h"

int Robot::next_id = 0;
int Robot::blabes_synolo = 0;
int Robot::palladio_synolo = 0;
int Robot::iridio_synolo = 0;
int Robot::leykoxrysos_synolo = 0;
int Robot::shmaies_synolo = 0;

// Topothethsh arxikwn timwn gia ola ta Robot.
Robot::Robot(Map & myMap) : map(myMap)
{
	taxythta = 1;
	leitoyrgei = true;
	prosbash = 0.5f;
	next_id++;
	id = next_id;
	xronos_xalasmeno = 0;
	n_kinhseis = 0;
	n_blabes = 0;
}

void Robot::metakinhsh()
{
	// Xalasmeno Robot den metakineitai.
	if (get_leitoyrgei() == false)
	{
		xronos_xalasmeno++;
		return;
	}
	int num_squares = taxythta;
	while (num_squares--)
	{
		// Kanonika metakinoymaste tyxaia, omws an yparxei shmaia den pame se
		// ayth th thesh. Yparxei mia periptosh oles oi gyro theseis na exoyne
		// shmaia. Se ayth thn periptosh, riskaroyme.
		bool exei_kinhsh = map.yparxei_amarkaristo(my_x, my_y);
		bool ektos_map;
		int dx, dy;
		do {
			dx = rand_int(-1, 2); // -1, 0 h 1
			dy = rand_int(-1, 2);
			ektos_map = my_x + dx < 0 || my_x + dx >= Map::PLATOS || my_y + dy < 0 || my_y + dy >= Map::YPSOS;
		} while (ektos_map || (exei_kinhsh && !ektos_map && map.get_square(my_x+dx, my_y+dy).get_flag()));
		my_x += dx;
		my_y += dy;
		n_kinhseis++;
	}
	// Koitame ton kindyno toy proorismoy.
	float p_blabhs = map.get_square(my_x, my_y).get_danger() * ( 1 - prosbash );
	if ( rand_float(0.0f, 1.0f) < p_blabhs ) {
		cout << "To oxhma " << this->symbolo() << "-" << id << " epathe blabh!!!!" << endl;
		num_squares = 0;
		set_leitoyrgei(false);
	}
	// De theloyme na typwsoyme metakinithike an typosame xalase.
	if (get_leitoyrgei())
		cout << "To oxhma " << this->symbolo() << "-" << id << " metakinithike." << endl;
}

void RobotExplore::leitoyrgia()
{
	// Xalasmeno Robot de bazei shmaies.
	if (get_leitoyrgei() == false)
		return;
	if (map.get_square(my_x, my_y).get_danger() > 0.6) {
		if (!map.get_square(my_x, my_y).get_flag()) {
			map.get_square(my_x, my_y).set_flag(true);
			shmaies_synolo++;
		}
	}
}

void RobotAnalyze::leitoyrgia()
{
	// Xalasmeno Robot den kanei eksoryksh.
	if (get_leitoyrgei() == false)
		return;
	Square & sq = map.get_square(my_x, my_y);
	// H bash thelei palladio kai to tetragono exei palladio
	if (!map.bash_palladio_full() && sq.get_palladio() > 0)
	{
		// Mporoyme na fortosoyme to poly eleytheros_xoros(), alla oxi panw apo
		// to poso palladio exei to tetragono, ara kratame to min. To idio tha
		// kanoyme kai gia toys alloys poroys.
		int for_pal = min(get_eleytheros_xoros(), sq.get_palladio());
		// Kanoyme thn eksoryksh kai to fortonoyme.
		sq.set_palladio( sq.get_palladio() - for_pal );
		fortio_palladioy += for_pal;
		palladio_synolo += for_pal;
		cout << "To oxhma " << this->symbolo() << "-" << id << " eksorykse " << for_pal << " kila palladio" << endl;
	}
	// H bash thelei iridio kai to tetragono exei iridio
	if (!map.bash_iridio_full() && sq.get_iridio() > 0 && get_eleytheros_xoros() > 0 )
	{
		int for_iri = min(get_eleytheros_xoros(), sq.get_iridio());
		sq.set_iridio( sq.get_iridio() - for_iri );
		fortio_iridioy += for_iri;
		iridio_synolo += for_iri;
		cout << "To oxhma " << this->symbolo() << "-" << id << " eksorykse " << for_iri << " kila iridio" << endl;
	}
	// H bash thelei leykoxryso kai to tetragono exei leykoxryso
	if (!map.bash_leykoxrysos_full() && sq.get_leykoxrysos() > 0 && get_eleytheros_xoros() > 0)
	{
		// Mporoyme na fortosoyme to poly eleytheros_xoros(), alla oxi panw apo
		// to poso palladio exei to tetragono, ara kratame to min. To idio tha
		// kanoyme kai gia toys alloys poroys.
		int for_ley = min(get_eleytheros_xoros(), sq.get_leykoxrysos());
		// Kanoyme thn eksoryksh kai to fortonoyme.
		sq.set_leykoxrysos( sq.get_leykoxrysos() - for_ley );
		fortio_leykoxrysoy += for_ley;
		leykoxrysos_synolo += for_ley;
		cout << "To oxhma " << this->symbolo() << "-" << id << " eksorykse " << for_ley << " kila leykoxryso" << endl;
	}
	// An gemisame pame aytomata sth bash
	if ( get_eleytheros_xoros() == 0 ) {
		my_x = map.get_base_x();
		my_y = map.get_base_y();
		cout << "To oxhma " << this->symbolo() << "-" << id << " ksefortose sth bash B" << endl;
		map.ksefortoma(fortio_palladioy, fortio_iridioy, fortio_leykoxrysoy);
		fortio_palladioy = fortio_iridioy = fortio_leykoxrysoy = 0;
	}
}

void RobotRescue::leitoyrgia()
{
	// Xalasmeno Robot den kanei episkeyh.
	if (get_leitoyrgei() == false)
		return;
	vector<Robot *> & robot_list = *robot_list_p;
	for (size_t i = 0; i<robot_list.size(); ++i)
	{
		int rx = robot_list[i]->get_x();
		int ry = robot_list[i]->get_y();
		int dx = rx > my_x ? rx - my_x : my_x - rx;
		int dy = ry > my_y ? ry - my_y : my_y - ry;
		// Einai geitoniko to robot i? To diorthonoyme an exei xalasei.
		if (dx <= 1 && dy <= 1)
		{
			if (!robot_list[i]->get_leitoyrgei()) {
				robot_list[i]->set_leitoyrgei(true);
				cout << "To oxhma " << this->symbolo() << "-" << id << " ekane diaswsh !!!" << endl;
			}
		}
	}
}

Robot * make_robot(Map & map, int typos)
{
	Robot * robot;
	if (typos <0)
		typos = rand_int(1, 4);
	switch (typos)
	{
		case 1:	// Robot eksereynhshs
		{
			robot = new RobotExplore(map);
			break;
		}
		case 2: // Robot Analyshs
		{
			RobotAnalyze * ra = new RobotAnalyze(map);
			ra->set_megisto_fortio (rand_int(1000, 2000));
			robot = ra;
			break;
		}
		case 3: // Robot Diaswshs
		{
			robot = new RobotRescue(map);
			break;
		}
	}
	// Idiothtes taxythta, thesh kai prosbash toy neoy robot.
	robot->set_taxythta(rand_int(1,3));
	robot->set_x(rand_int(0, Map::PLATOS));
	robot->set_y(rand_int(0, Map::YPSOS));
	robot->set_prosbash(rand_float(0.1f, 1.0f));
	return robot;
}
