#include "triangle.h"
#include <vector>
#include <map>
#include <string>
#include <math.h>


using namespace::std;

vector<string>  point_xyz;
vector<point>   points;
vector<string>  indexs;
vector<triangle> trangles;
vector<string>  colors;
vector<string>	color_RGB;
map<string, color>  colorLib;

point ViewPoint = point(50, 50, 50);
Vector N = Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);//view_z
Vector V = Vector(sqrt(2) / 2, 0, sqrt(2) / -2);//view_x
//Vector U = Vector(sqrt(6) / 6, sqrt(6) / 3, sqrt(6) / -6);//view_y
Vector U = N.cross(V,1);
matrix m_E = matrix();
matrix m_V2S = matrix();

//记录摄像头参数
double D=50;
double F=100;
double width_left=-50;//x
double width_right =50;
double height_top=50;//y
double height_buttom = -50;

double A = -(F + D) / (F - D);
double B = 2 * F*D / (D - F);
double with_A = 2 * D / (width_right - width_left);
double with_B = (width_left + width_right) / (width_right - width_left);
double high_A = 2 * D / (height_top - height_buttom);
double high_B = (height_top + height_buttom) / (height_top - height_buttom);

double zBuffer[600][600] = {};
color screen_c[600][600] = {};