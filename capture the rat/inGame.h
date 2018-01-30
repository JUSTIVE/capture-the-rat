#pragma once
#include<gl\glut.h>
#include<iostream>
using namespace std;
#include"Animal.h"
#include"BenList.h"
int Window;
#define CAT_SIZE 5
Cheese cheese;
Rat rat;
Cat cat[CAT_SIZE];
int arrow[4] = { 0,0,0,0 };

BenList<int> wall;
void renderWall() {
	glTranslatef(10, -10, 0);
	//for (int i = 0; i < wall.getSize(); i++) {
	Node<int> *currentNode = wall.List;
	for(int i=0;i<wall.getSize();i++){
		glPushMatrix();{
			glScalef(1, 1, 1.0 / 20.0);
			glColor4f(1, 1, 1,1);
			glTranslatef((currentNode->data%50)*20,1000- (currentNode->data /50)*20,0);
			glutSolidCube(20);
		}
		glPopMatrix();
		currentNode = currentNode->Link;
	}
}




void initIngame() {
	cheese.position.x = 500;
	cheese.position.y = 500;
	for (int i = 0; i < 50; i++) {
		wall.append(i);
	}
	for (int i = 0; i < 50; i++) {
		wall.append(i+2450);
	}
	for (int i = 0; i < 2500; i+=50) {
		wall.append(i);
	}
	for (int i = 49; i < 2500; i += 50) {
		wall.append(i);
	}
	for (int i = 380; i < 1000; i += 50) {
		wall.append(i);
	}
	/*for (int i = 0; i < 50; i++) {
		wall.append((int)((rand() / (double)RAND_MAX) * 2500));
	}*/
}

void renderGame() {

	renderWall();
	cheese.render();
	rat.render();
	for(int i=0;i<CAT_SIZE;i++)
		cat[i].render();
}

void inKeyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(1);
		break;
	case 'a':
		rat.holdCheese(&cheese);
		
		break;
	default:
		break;
	}

}


void inMouse(int button, int state, int x, int y) {

}

void inPassive(int x, int y) {
	rat.update(x, y,wall);
	cheese.nearRat(rat.getPosition());
	//rat.MoveTo(x, y);
	for (int i = 0; i<CAT_SIZE; i++)
		if(cat[i].search(rat.getPosition().x, rat.getPosition().y))
			cat[i].MoveTo(rat.getPosition().x,1000-rat.getPosition().y,wall);
}

void inSpecialKey(unsigned char key, int x, int y) {
	
	switch (key)
	{
	case GLUT_KEY_UP:
		arrow[0] = 1;
		break;
	case GLUT_KEY_DOWN:
		arrow[1] = 1;
		break;
	case GLUT_KEY_LEFT:
		arrow[2] = 1;
		break;
	case GLUT_KEY_RIGHT:
		arrow[3] = 1;
		break;
	default:
		break;
	}

	rat.Move(arrow);
}
void inSpecialKeyUp(unsigned char key, int x, int y) {

	switch (key)
	{
	case GLUT_KEY_UP:
		arrow[0] = 0;
		break;
	case GLUT_KEY_DOWN:
		arrow[1] = 0;
		break;
	case GLUT_KEY_LEFT:
		arrow[2] = 0;
		break;
	case GLUT_KEY_RIGHT:
		arrow[3] = 0;
		break;
	default:
		break;
	}
	rat.Move(arrow);
}