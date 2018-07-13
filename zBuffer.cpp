#include "triangle.h"
#include "globals.h"
using namespace::std;



point trangle_point(int i, int j, vector<triangle>::iterator it) {
	point p = point((double)i,(double)j,10);
	Vector e1 = Vector(it->B.x - it->A.x, it->B.y - it->A.y, it->B.z - it->A.z);
	Vector e2 = Vector(it->C.x - it->A.x, it->C.y - it->A.y, it->C.z - it->A.z);
	Vector n = e1.cross(e2,0);

	double plain_D = n.x*(it->A.x) + n.y*(it->A.y) + n.z*(it->A.z);
	double z = (plain_D - n.x*(i) + n.y*(j))/n.z;


	double d = n.mult(Vector(it->A.x,it->A.y,it->A.z));
	double a = e1.mult(e1);
	double b = e1.mult(e2);
	double c = e2.mult(e2);
	double D = a*c - b*b;
	double A = a / D;
	double B = b / D;
	double C = c / D;

	Vector uB = Vector(e1.x*C - e2.x*B, e1.y*C - e2.y*B, e1.z*C - e2.z*B);
	Vector uR = Vector(e2.x*A - e1.x*B, e2.y*A - e1.y*B, e2.z*A - e1.z*B);

	//(i,j,z)
	Vector r = Vector(i- it->A.x,j- it->A.y,z- it->A.z);
	double beta = uB.mult(r);
	double gama = uR.mult(r);
	double alpha = 1 - beta - gama;
	if (beta >= 0 && gama >= 0 && alpha >= 0) {
		point temp = point((double)i, (double)j, z);
		return temp;
	}
	return p;
}

void init_z() {
	int i, j;
	for (i = 0; i < 600; i++) {
		for (j = 0; j < 600; j++) {
			zBuffer[i][j] = 1;//先初始化为最深
		}
	}
}

void init_c() {
	color c = color(0,0,0);
	int i, j;
	for (i = 0; i < 600; i++) {
		for (j = 0; j < 600; j++) {
			screen_c[i][j]=c;
		}
	}
}

void z_buffer(int i, int j) {
	color current_c = color();
	point p;
	vector<triangle>::iterator it;
	map<string, color>::iterator mc;

	Vector e1;
	Vector e2;
	Vector n;
	double plain_D;
	double z;


	double d;
	double a;
	double b;
	double c;
	double D;
	double A;
	double B;
	double C;

	Vector uB;
	Vector uR;

	//(i,j,z)
	Vector r;
	double beta;
	double gama;
	double alpha;
	it = trangles.begin();
	for (; it != trangles.end(); it++) {
		//计算和所有三角形的交点
		//point = trangle_point(i,j,it);

		p  = point((double)i, (double)j, 10000);
		e1 = Vector(it->B.v.x - it->A.v.x, it->B.v.y - it->A.v.y, it->B.v.z - it->A.v.z);
		e2 = Vector(it->C.v.x - it->A.v.x, it->C.v.y - it->A.v.y, it->C.v.z - it->A.v.z);
		n = e1.cross(e2,0);

		plain_D = n.x*(it->A.v.x) + n.y*(it->A.v.y) + n.z*(it->A.v.z);
		z = (plain_D - n.x*(i)-n.y*(j)) / n.z;


		d = n.mult(Vector(it->A.v.x, it->A.v.y, it->A.v.z));
		a = e1.mult(e1);
		b = e1.mult(e2);
		c = e2.mult(e2);
		D = a*c - b*b;
		A = a / D;
		B = b / D;
		C = c / D;

		uB = Vector(e1.x*C - e2.x*B, e1.y*C - e2.y*B, e1.z*C - e2.z*B);
		uR = Vector(e2.x*A - e1.x*B, e2.y*A - e1.y*B, e2.z*A - e1.z*B);

		//(i,j,z)
		r = Vector(i - it->A.v.x, j - it->A.v.y, z - it->A.v.z);
		beta = uB.mult(r);
		gama = uR.mult(r);
		alpha = 1 - beta - gama;
		if (beta >= 0 && gama >= 0 && alpha >= 0) {
			point temp = point((double)i, (double)j, z);
			p= temp;
		}

		if (p.z <= zBuffer[j][i]) {
			zBuffer[j][i] = p.z;
			mc = colorLib.find(it->color_str);
			screen_c[j][i] = mc->second;
		}
	}

}