#pragma once
#include"BenGL.h"
using namespace std;
#include"axis.h"

#include"BenList.h"	

class Cheese {
public:
	Cheese();
	Axis position;
	bool able;
	bool IsnearRat;
	void render();
	void nearRat(Axis position);
};

class Animal {
protected:
	Axis prevPosition;
	Axis position;
	Axis Size;
	double velo;
public:
	Animal();
	void setPosition(double x, double y);
	void setSize(double width, double height);
	virtual void render() {};
	void MoveTo(double x, double y,BenList<int>wall);
	int getAddress(Axis position);
	bool Collision(BenList<int> wall,Axis position);
};

class Rat :public Animal {
private:
	Axis heading;
	bool nearCheese;
	bool holdingCheese;
	
public:
	Rat();
	virtual void Move(int arrow[]);
	void update(double x, double y,BenList<int>wall);
	void render();
	Axis getPosition();
	void sniff(Axis cheesePosition);
	void holdCheese(Cheese* cheese);
	void view();
};
class Cat : public Animal {
private :
	Axis heading;
	double search_range; 
	int counter;
	Axis target;
public:
	Cat();
	void render();
	bool search(double x, double y);
};