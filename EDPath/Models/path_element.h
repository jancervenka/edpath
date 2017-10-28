#pragma once

using namespace std;

class path_element
{
    private:
		string name;
		float dtt;

    public:
		path_element(float _dtt, string _name);
		virtual ~path_element();
		float get_dtt();
		string get_name();
};