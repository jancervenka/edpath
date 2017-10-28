#include "stdafx.h"
#include "path_element.h"


path_element::path_element(float _dtt, string _name)
{
	name = _name;
	dtt = _dtt;
	
}

string path_element::get_name()
{
	return name;
}

float path_element::get_dtt()
{
	return dtt;
}


path_element::~path_element()
{

}