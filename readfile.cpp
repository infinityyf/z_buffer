#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include "triangle.h"
#include "globals.h"

using namespace::std;

void readfile() {
	string objfile = "test2.obj";
	string mtlfile = "test2.mtl";
	string obj_line=" ";
	string mtl_line=" ";
	char buffer[1024];
	char *tmpStr;
	string current_color;
	vector<string>::iterator ic;



	ifstream obj_in(objfile);
	while (!obj_in.eof()) {
		obj_in.getline(buffer,50);
		if (buffer[0] == 'v') {
			if(point_xyz.size()>0)point_xyz.clear();
			tmpStr = strtok(buffer," ");
			while (tmpStr != NULL){
				point_xyz.push_back(string(tmpStr));
				tmpStr = strtok(NULL, " ");
			}
			point p = point(atof(point_xyz[1].c_str()), atof(point_xyz[2].c_str()), atof(point_xyz[3].c_str()));
			points.push_back(p);
		}
		
		if (buffer[0] == 'f') {
			if(indexs.size()>0)indexs.clear();
			tmpStr = strtok(buffer, " ");
			while (tmpStr != NULL) {
				indexs.push_back(string(tmpStr));
				tmpStr = strtok(NULL, " ");
			}
			triangle t = triangle(points[atoi(indexs[1].c_str())-1], points[atoi(indexs[2].c_str())-1], points[atoi(indexs[3].c_str())-1]);
			t.color_str = current_color;
			trangles.push_back(t);
		}

		if (buffer[0] == 'u') {
			tmpStr = strtok(buffer, " ");
			while (tmpStr != NULL) {
				colors.push_back(string(tmpStr));
				tmpStr = strtok(NULL, " ");
			}
			ic = colors.end()-1;
			current_color = *ic;
		}
		//obj_line = string(buffer);

		//cout <<buffer << endl;
	}
	obj_in.close();


	ifstream mtl_in(mtlfile);
	while (!mtl_in.eof()) {
		mtl_in.getline(buffer, 50);
		if (buffer[0] == 'n') {
			tmpStr = strtok(buffer, " ");
			while (tmpStr != NULL) {
				colors.push_back(string(tmpStr));
				tmpStr = strtok(NULL, " ");
			}
			ic = colors.end() - 1;
			current_color = *ic;
		}

		if (buffer[0] == 'K') {
			if (color_RGB.size() > 0)color_RGB.clear();
			tmpStr = strtok(buffer, " ");
			while (tmpStr != NULL) {
				color_RGB.push_back(string(tmpStr));
				tmpStr = strtok(NULL, " ");
			}
			color c = color(atof(color_RGB[1].c_str()), atof(color_RGB[2].c_str()), atof(color_RGB[3].c_str()));
			colorLib.insert(pair < string, color>(current_color,c));
		}
		//mtl_line = string(buffer);
		//cout << buffer << endl;
	}
	mtl_in.close();
}