//#include "euclid.h"
#include "stdafx.h"

float get_dist(float x1, float y1, float z1, float x2, float y2, float z2)
{
	return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2) + pow((z1 - z2), 2));
}

float get_dist(const point *star1, const point *star2)
{
	return sqrt(pow((star1->x - star2->x), 2) + pow((star1->y - star2->y), 2) + pow((star1->z - star2->z), 2));
}

point get_vec(const point *current, const point *next)
{
	point v;
	v.x = next->x - current->x;
	v.y = next->y - current->y;
	v.z = next->z - current->z;


	return v;
}

point get_vec_endpoint(const point *current, const point *vec, const float factor)
{
	point endpoint;
	endpoint.x = current->x + vec->x / factor;
	endpoint.y = current->y + vec->y / factor;
	endpoint.z = current->z + vec->z / factor;

	return endpoint;

}