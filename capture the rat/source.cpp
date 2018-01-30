#include<gl/glut.h>
#include<iostream>
#include"preGame.h"
#include"inGame.h"
#define SIZE_X 1000
#define SIZE_Y 1000
using namespace std;
int GameState = 1;
static Axis mouse;

void renderEnd() {
	
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluPerspective(90.0f,1.0f,1.0f,100.0f);
	glOrtho(0, SIZE_X, 0, SIZE_Y, -1, 1);
	glViewport(0, 0, SIZE_X, SIZE_Y);
	switch (GameState)
	{
	case 0:
		renderPreGame();
		break;
	case 1:
		renderGame();
		
		break;
	default:
		renderEnd();
		break;
	}
	//cout << mouse.x << "\t" << mouse.y << endl;
	glutSwapBuffers();
	//glutPostRedisplay();
}

void keyBoard(unsigned char key, int x, int y) {
	int Arrow[3] = {0,0,0};
	switch (GameState)
	{
	case 0:
		preKeyBoard(key, x, y);
		break;
	case 1:
		inKeyboard(key, x, y);
		break;
	case 2:
		break;
	default:
		break;
	}
	
	glutPostRedisplay();
}

void reshape(int x, int y) {
	glutReshapeWindow(SIZE_X, SIZE_Y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y) {
	switch (GameState)
	{
	case 0:
		preSpecial(key, x, y);
		break;
	case 1:
		inSpecialKey(key, x, y);
		break;
	case 2:
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void SpecialKeyUp(int key, int x, int y) {
	switch (GameState)
	{
	case 0:
		preSpecialUp(key, x, y);
		break;
	case 1:
		inSpecialKeyUp(key, x, y);
		break;
	case 2:
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y) {
	switch (GameState)
	{
	case 0:
		break;
	case 1:
		inMouse(button, state, x, y);
		break;
	case 2:
		break;
	default:
		break;
	}
	glutPostRedisplay();
}
void Passive(int x, int y) {
	switch (GameState)
	{
	case 0:
		break;
	case 1:
		//inPassive(x,y);
		mouse.x = x;
		mouse.y = y;
		break;
	case 2:
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Idle() {
	
	switch (GameState)
	{
	case 0:
		break;
	case 1:
		inPassive(mouse.x, mouse.y);
		break;
	case 2:
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void init() {
	glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
	glDepthFunc(GL_ALWAYS);               // The Type Of Depth Testing To Do
										  // Really Nice Perspective Calculations
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initIngame();
	
}

int main(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_ALPHA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SIZE_X, SIZE_Y);
	Window=glutCreateWindow("GET THE CHEEEZ");

	init();
	glutDisplayFunc(render);
	glutIdleFunc(Idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyBoard);
	glutSpecialUpFunc(SpecialKeyUp);
	glutSpecialFunc(SpecialKey);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(Passive);
	glutMainLoop();
	return 1;
}