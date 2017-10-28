#pragma once
#include "../Models/star.h"
#include "../Models/path_element.h"
#include "stdafx.h"
#include <vector>
#include <sstream>

using namespace std;

class navservice
{
    public:
	    navservice();
		int find_path(string start, string target, float jumprng);
	    virtual ~navservice();
		void print_report();
		
    private:
	    vector<star> *stars;
		vector<path_element> *path;
		vector<star>::iterator find_nearest_star(const point *loc, const float jumprng, const vector<star>::iterator& itc);
		bool path_convergence();
		stringstream report;


};
