#include "stdafx.h"
#include "star.h"

star::star(point _position, string _name)
{
	position = _position;
	name = _name;
}

int star::get_id()
{
	return id;
}

string star::get_name()
{
	return name;
}

point *star::get_position()
{
	return &position;
}

star::~star()
{

}