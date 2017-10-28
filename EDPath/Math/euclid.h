#pragma once
#include <cmath>

struct point
{
	float x;
	float y;
	float z;
};

float get_dist(float x1, float y1, float z1, float x2, float y2, float z2);

float get_dist(const point *star1, const point *star2);

point get_vec(const point *current, const point *next);

point get_vec_endpoint(const point *current, const point *vec, const float factor);