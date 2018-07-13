#pragma once

#ifndef _TRANGLE_H
#define _TRANGLE_H

#include <vector>
using namespace::std;

class point;
class Vector;
class matrix;
class triangle;
class color;

void readfile();
void InitCamera();
void World2View();
void View2Screen();
void init_z();
void init_c();
void z_buffer(int i,int j);

class Vector
{
public:
	Vector();
	//Vector(point A, point B);
	Vector(double x, double y, double z);
	Vector cross(Vector v,int f);
	double mult(Vector v);
	Vector mult(matrix m);
	//point start;
	void extend(double w);
	void cut();
	double x;
	double y;
	double z;
	double w;
};

class point
{
public:
	point();
	point(double x, double y, double z);
	//point(point &p);
	double x;
	double y;
	double z;
	//这里的xyz记录的是再世界坐标中的位置
	Vector v;
};




class matrix
{
public:
	matrix();
	void init_m_t(point view);
	void init_m_b(Vector N, Vector V, Vector U);
	void init_m_v2s(double A, double B, double with_A, double with_B, double high_A, double high_B);
	matrix mult(matrix m);
	Vector mult(Vector v);
	double m[4][4];
};


class color
{
public:
	color();
	color(double R, double G, double B);
	double R;
	double G;
	double B;

};

class triangle
{
public:
	triangle();
	triangle(point A, point B, point C,color c);
	triangle(point A, point B, point C);
	void setColor(color c);
	point A;
	point B;
	point C;
	color surfColor;
	string color_str;
};

#endif
