#pragma once

using namespace std;

class star
{
    
    private:
		string name;
	    int id;
	    point position;

    public:
	    star(point _position, string _name);
	    virtual ~star();
		int get_id();
		point *get_position();
		string get_name();

};

