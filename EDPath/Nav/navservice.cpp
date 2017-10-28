#include "stdafx.h"
#include "navservice.h"
#include "../Models/star.h"

using namespace std;

navservice::navservice()
{
	//report.str(string());

	string line;
	string name;

	stars = new vector<star>();

	/*try
	{
		ifstream infile("stardata.txt");
	}
	catch (...)
	{
		cout << "Error loading file!";
		return;
	}*/

	
	ifstream infile("stardata.txt");
	int tline = 0;
	size_t chars;
	float x, y, z;

	

	while (getline(infile, line))
	{
		if (tline == 0) 
			name = line;
		else if (tline == 1) 
			x = stof(line, &chars);
		else if (tline == 2) 
			y = stof(line, &chars);
		else if (tline == 3) 
			z = stof(line, &chars);
		
		if (tline == 4)
		{
			tline = 0;
			stars->push_back(star({ x = x, y = y, z = z }, name));
		}
		else
			tline++;
	}
}

int navservice::find_path(string start, string target, float jumprng)
{
	if (jumprng > 50 || jumprng < 5)
	{
		cout << "Jump range out of bounds <5, 50>." << endl;
		return -1;
	}

	std::vector<star>::iterator it;
	std::vector<star>::iterator it_current = stars->end();
	std::vector<star>::iterator it_target = stars->end();
	std::vector<star>::iterator it_next = stars->end();
	float dist;
	point vec, endpoint;
	clock_t t1, t2;

	t1 = clock();

	for (it = stars->begin(); it != stars->end(); ++it)
	{
		if (it->get_name() == start)
			it_current = it;
			
		if (it->get_name() == target)
			it_target = it;		
	}

	if (it_current == stars->end() || it_target == stars->end())
	{
		report << "ERROR: Star system not found." << endl;
		return -1;
	}

	path = new vector<path_element>();
	
	while (true)
	{
		vec = get_vec(it_current->get_position(), it_target->get_position());
		dist = get_dist(0, 0, 0, vec.x, vec.y, vec.z);
		path->push_back(path_element(dist, it_current->get_name()));
		if (dist <= jumprng)
		{
			path->push_back(path_element((float) 1e-9, it_target->get_name()));
			break;
		}

		endpoint = get_vec_endpoint(it_current->get_position(), &vec, dist / jumprng);
		it_next = find_nearest_star(&endpoint, jumprng, it_current);
		
		if (it_next == stars->end())
		{
			report << "ERROR: No reachable star found." << endl;
			path->clear();
			delete path;
			return -1;
		}

		it_current = it_next;

		if (!path_convergence())
		{
			report << "ERROR: Distance to target does not converge." << endl;
			path->clear();
			delete path;
			return -1;
		}
	}

	t2 = clock();

	report << "SUCCESS! Path found." << endl;
	report << fixed << setprecision(4) << "CPU Time: " << ((float)(t2 - t1)) / CLOCKS_PER_SEC << " seconds." << endl;
	report << "Jump | " << "Distance to Target | " << "System" << endl;
	report << "====================================================" << endl;
	std::vector<path_element>::iterator itp;
	
	report << fixed << setprecision(1);
	int c = 0;
	for (itp = path->begin(); itp != path->end(); ++itp)
	{
		report << setfill('0') << setw(2);
		report << c << "   | ";
		report << setfill('0') << setw(5);
		report << itp->get_dtt() << " ly           | " << itp->get_name() << endl;
		c++;
	}

	path->clear();
	delete path;

	return 0;

}

vector<star>::iterator navservice::find_nearest_star(const point *loc, const float jumprng, const vector<star>::iterator& itc)
{
	std::vector<star>::iterator it;
	std::vector<star>::iterator minit = stars->end();
	float dist = (float) 10e20, mindist = (float) 10e20;

	for (it = stars->begin(); it != stars->end(); ++it)
	{
		dist = get_dist(loc, it->get_position());
		if (dist < mindist && dist <= jumprng && get_dist(it->get_position(), itc->get_position()) <= jumprng)
		//if (dist < mindist && get_dist(it->get_position(), itc->get_position()) <= jumprng)
		{
			minit = it;
			mindist = dist;
		}
	}
	
	return minit; // if the functions returns it->end(): no star within the range
}

bool navservice::path_convergence()
{
	/* The path might get to the point where the next endpoint of the navigation vector is outside the Bubble. 
	   This means that there is no star satysfing all the conditions (1) in the find_nearest_path() (the only 
	   viable star is the current one and it cannot be reached because of the dist < jumprng condition). The 
	   program then exits with the "No reachable star found" error. 
	   
	   If we remove the condition, the algorithm will stay in the current star forever, the program will exit 
	   with the "Distance to target does not converge" error after the convergence threshhold (100) is reached.

	   (1) Why?
	   If the navigation endpoint is in the "deep space void", the closest star (mindist) is the current one.
	   There is probably some issue with comparison and arithmetics of floats meaning that dist <= jumprng
	   returns false (dist is the distance between the current star and navigation endpoint).

	   There might be cases where the navigation vector has a narrow anggle with the edge of the Bubble; the
	   program then might exit via the convergence threshold. (Santos Dumont -> Sol)
	*/


	std::vector<path_element>::iterator itp;

	if (path->size() < 5)
		return true;

	int diffc = 0;

	for (itp = path->begin() + 1; itp != path->end(); ++itp)
	{
		if (itp->get_dtt() - (itp - 1)->get_dtt() >= 0.0)
			diffc++;
	}

	if (diffc > 100)
		return false;
	else
		return true;
}

void navservice::print_report()
{
	cout << report.str();
}

navservice::~navservice()
{

	stars->clear(); // deletes elements of stars vector
	delete stars; // deletes stars vector object
}