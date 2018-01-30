#pragma once
#include<gl\glut.h>
#include<iostream>
using namespace std;
#include"axis.h"
class RButton {
private:
	Axis position;
	Axis size;
	int state;
public:
	RButton();
	Axis getPosition();
	Axis getSize();
	bool Clicked(double x, double y);
};