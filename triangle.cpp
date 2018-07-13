
#include "triangle.h"
point::point(){}
Vector::Vector(){}
color::color(){}
triangle::triangle(){}
matrix::matrix(){}

void matrix::init_m_t(point view)
{
	m[0][0] = 1;		 m[0][1] = 0;		   m[0][2] = 0;		 m[0][3] = 0;
	m[1][0] = 0;		 m[1][1] = 1;		   m[1][2] = 0;		 m[1][3] = 0;
	m[2][0] = 0;		 m[2][1] = 0;		   m[2][2] = 1;		 m[2][3] = 0;
	m[3][0] =-view.x;    m[3][1] = -view.y;    m[3][2] = -view.z;  m[3][3] = 1;
}

void matrix::init_m_b(Vector N, Vector V, Vector U)
{
	m[0][0] = V.x;   m[0][1] = U.x;   m[0][2] = N.x;   m[0][3] = 0.0f;
	m[1][0] = V.y;   m[1][1] = U.y;   m[1][2] = N.y;   m[1][3] = 0.0f;
	m[2][0] = V.z;   m[2][1] = U.z;   m[2][2] = N.z;   m[2][3] = 0.0f;
	m[3][0] = 0;	 m[3][1] = 0;	  m[3][2] = 0;	   m[3][3] = 1;
}

void matrix::init_m_v2s(double A,double B,double with_A,double with_B,double high_A,double high_B)
{
	m[0][0] = with_A;   m[0][1] = 0;		m[0][2] = with_B;   m[0][3] = 0;
	m[1][0] = 0;		m[1][1] = high_A;   m[1][2] = high_B;   m[1][3] = 0;
	m[2][0] = 0;		m[2][1] = 0;		m[2][2] = A;		m[2][3] = B;
	m[3][0] = 0;		m[3][1] = 0;		m[3][2] = -1;		m[3][3] = 0;
}

matrix matrix::mult(matrix mat)
{
	matrix _m = matrix();

	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			_m.m[i][j] = m[i][0] * mat.m[0][j] + m[i][1] * mat.m[1][j] + m[i][2] * mat.m[2][j] + m[i][3] * mat.m[3][j];
		}
	}
	return _m;
}

Vector matrix::mult(Vector v)
{
	Vector _v = Vector();
	_v.x = v.x*m[0][0] + v.y*m[0][1] + v.z*m[0][2] + v.w*m[0][3];
	_v.y = v.x*m[1][0] + v.y*m[1][1] + v.z*m[1][2] + v.w*m[1][3];
	_v.z = v.x*m[2][0] + v.y*m[2][1] + v.z*m[2][2] + v.w*m[2][3];
	_v.w = v.x*m[3][0] + v.y*m[3][1] + v.z*m[3][2] + v.w*m[3][3];
	return _v;
}



point::point(double x, double y, double z) {
	point::x = x;
	point::y = y;
	point::z = z;
	point::v = Vector(x,y,z);
}

//point::point(point & p)
//{
//	x = p.x;
//	y = p.y;
//	z = p.z;
//}




//Vector::Vector(point A, point B) {
//	Vector::x = B.x - A.x;
//	Vector::y = B.y - A.y;
//	Vector::z = B.z - A.z;
//	Vector::start = A;
//}
Vector::Vector(double x, double y, double z) {
	Vector::x = x;
	Vector::y = y;
	Vector::z = z;
}



Vector Vector::cross(Vector v,int flag)
{
	double _x = y * v.z - z * v.y;
	double _y = z * v.x - x * v.z;
	double _z = x * v.y - y * v.x;
	if (flag == 1) {
		double Length = sqrt(_x * _x + _y * _y + _z * _z);
		return Vector(_x / Length, _y / Length, _z / Length);
	}
	
	return Vector(_x,_y,_z);
}

double Vector::mult(Vector v)
{
	double _v;
	_v = x*v.x + y*v.y + z*v.z;
	return _v;
}

Vector Vector::mult(matrix m)
{

	Vector _v = Vector();
	_v.x = x*m.m[0][0] + y*m.m[1][0] + z*m.m[2][0] + w*m.m[3][0];
	_v.y = x*m.m[0][1] + y*m.m[1][1] + z*m.m[2][1] + w*m.m[3][1];
	_v.z = x*m.m[0][2] + y*m.m[1][2] + z*m.m[2][2] + w*m.m[3][2];
	_v.w = x*m.m[0][3] + y*m.m[1][3] + z*m.m[2][3] + w*m.m[3][3];
	return _v;
}

void Vector::extend(double w)
{
	this->w = w;
	this->x = this->x / w;
	this->y = this->y / w;
	this->z = this->z / w;
}

void Vector::cut()
{
	this->x = this->x / this->w;
	this->y = this->y / this->w;
	this->z = this->z / this->w;
}

triangle::triangle(point A, point B, point C,color c){
	triangle::A = A;
	triangle::B = B;
	triangle::C = C;
	triangle::surfColor = c;

}

void triangle::setColor(color c) {
	triangle::surfColor = c;
}

triangle::triangle(point A, point B, point C) {
	triangle::A = A;
	triangle::B = B;
	triangle::C = C;

}
color::color(double R, double G, double B){
	color::R = R;
	color::G = G;
	color::B = B;
}



