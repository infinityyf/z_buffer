#pragma once
#include "triangle.h"
#include <vector>
#include <map>
#include <string>
#include <math.h>


extern vector<string>  point_xyz;
extern vector<point>   points;


extern vector<string>  indexs;
extern vector<triangle> trangles;


extern vector<string>  colors;
extern vector<string>	color_RGB;
extern map<string, color>  colorLib;
extern point ViewPoint;
extern Vector N;//view_z
extern Vector V;//view_y
extern Vector U;//view_x


extern matrix m_E;
extern matrix m_V2S;

extern double D;
extern double F;

extern double width_left;//x
extern double width_right;
extern double height_top;//y
extern double height_buttom;

extern double A;
extern double B;
extern double with_A;
extern double with_B;
extern double high_A;
extern double high_B;

//深度映射的时候，近的是-1，远的是1

extern double zBuffer[600][600];
extern color screen_c[600][600];