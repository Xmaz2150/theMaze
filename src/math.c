#include "../inc/maze.h"

/**
 * precompute_lookup_tables - initializes sin an cos lookup tables
 * @math: Input, lookup tables
 *
 * Return: none
 **/
void precompute_lookup_tables(Math *math)
{
	double radian_angle;

	for (int angle = 0; angle < 360; ++angle)
	{
		radian_angle = angle * M_PI / 180.0;
		math->sin_lookup[angle] = sin(radian_angle);
		math->cos_lookup[angle] = cos(radian_angle);
	}
}

/**
 * deg_to_rad - converts degress to redii
 * @a: Input, angle
 *
 * Return: radians
 **/
float deg_to_rad(float a)
{
	return (a * (PI / 180.0));
}

/**
 * fix_ang - fixes and within 360 degrees
 * @a: Input, angle
 *
 * Return: angle
 **/
int fix_ang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}
