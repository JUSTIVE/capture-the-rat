#include"Animal.h"

Cheese::Cheese() {
	IsnearRat = false;
	able = true;
}
void Cheese::render() {
	glPushMatrix();
		if(able){
			glPushMatrix();
				glColor4f(1, 1, 0, 1);
				glTranslatef(position.x, position.y, 0);
				glutSolidCircle(15, 10);
			glPopMatrix();

			if (IsnearRat) {
				glColor4f(1, 1, 1, 1);
				glTranslatef(-20, 20, 0);
				glutDrawBitmapText("press 'a' to hold cheese", this->position.x, this->position.y);
			}
		}
	glPopMatrix();
}
void Cheese::nearRat(Axis position)
{
	double dist = sqrt(pow(this->position.x - position.x, 2) + pow(this->position.y - position.y, 2));
	if (dist < 10) {
		IsnearRat = true;
	}
	else {
		IsnearRat = false;
	}
}

Animal::Animal() {
	position.x=position.y= 150;
	prevPosition.x = prevPosition.y = 150;
}
void Animal::setPosition(double x, double y) {
	this->position.x = x;
	this->position.y = y;
}

void Animal::setSize(double width, double height) {
	this->Size.x = width;
	this->Size.y = height;
}
void Animal::MoveTo(double x, double y,BenList<int>wall) {
	y =1000-y;
	double dist = sqrt(pow(x-position.x,2)+ pow(y - position.y, 2));
	//double dx = (x - position.x) / (dist*velo);
	//double dy = (y - position.y) / (dist*velo);
	double dx = x - position.x;
	double dy = y - position.y;
	dx /= dist;
	dy /= dist;
	dx *= velo;
	dy *= velo;

	Axis temp;
	temp.x= position.x + dx;
	temp.y = position.y + dy;
	//cout << temp.x << " " << temp.y << endl;
	if (Collision(wall, temp)) {
		cout << "why" << endl;
	}
	else {
		//cout << getAddress(position) << endl;;
		prevPosition.x = position.x;
		prevPosition.y = position.y;
		position = temp;
	}
}

int Animal::getAddress(Axis position) {
	return (int)((position.x / 20)) + (int)(50 * ((int)((1000 - position.y) / 20)));
}

bool Animal::Collision(BenList<int> wall,Axis position) {
	Node<int>*currentNode = wall.List;
	for (int i = 0; i < wall.getSize();i++) {
		if (currentNode->data == getAddress(position)|| currentNode->data-1 == getAddress(position)|| currentNode->data -50 == getAddress(position)){
			//cout << "Address = " << getAddress(position);
			//cout << "Collision = " <<currentNode->data<< endl;
			return true;
		}
		currentNode = currentNode->Link;
	}
	return false;
}

Rat::Rat() {
	velo = 1.5;
	nearCheese = false;
	holdingCheese = false;
}

void Rat::Move(int key[]) {
	position.y += key[0];
	position.y -= key[1];
	position.x -= key[2];
	position.x += key[3];
	cout << "x = " << position.x << " y=" << position.y << endl;
}

void Rat::holdCheese(Cheese* cheese) {
	if (holdingCheese == true)
	{
		cheese->able = true;
		holdingCheese = false;
		this->velo=1.5;
		cheese->position.x = this->position.x;
		cheese->position.y = this->position.y;
	}
	if (cheese->IsnearRat==true&&cheese->able==true) {
		if (holdingCheese==false){//치즈를 든다
			holdingCheese = true;
			this->velo=1.0;
			cheese->able = false;

		}
		
	}
	
}
void Rat::update(double x, double y,BenList<int>wall) {
	MoveTo(x, y,wall);
	//sniff(cheesePosition);
}
void Rat::render() {
	glPushMatrix(); {
		glPushMatrix();
		glColor4f(1, 1, 1.0, 0.5);
		glTranslatef(position.x, position.y, 0);
		glRotatef(-atan((prevPosition.x - position.x) / (prevPosition.y - position.y)) * 180 / M_PI, 0, 0, 1);
		if (prevPosition.y - position.y > 0) {
			glRotatef(180, 0, 0, 1);
		}
		//cout << atan((prevPosition.x - position.x) / (prevPosition.y - position.y)) * 90 << endl;

		glColor4f(1, 1, 0.0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(0, 10, 0);
		glVertex3f(-5, 0, 0);
		glVertex3f(-5, -10, 0);
		glVertex3f(5, -10, 0);
		glVertex3f(5, 0, 0);
		glEnd();

		glPopMatrix();
		glColor4f(1, 1, 1,0.5);
		glTranslatef(-8, 0, 0);
		glutDrawBitmapText("(' y ')", this->position.x, this->position.y);

		
	}
	glPopMatrix();
}

Axis Rat::getPosition() {
	return position;
}




Cat::Cat() {
	
	position.x = prevPosition.x =target.x= 550;
	position.y = prevPosition.y =target.y= 550;
	velo = 1.0+(rand()/(double)RAND_MAX*0.4);
	cout << velo << endl;
	search_range = 40 + (rand() / (double)RAND_MAX)*50.0;
	counter = 0;
}

void Cat::render() {
	glPushMatrix(); 

		glPushMatrix();
			glColor4f(1, 1, 1.0, 0.5);
			glTranslatef(position.x, position.y, 0);
			glRotatef(-atan((prevPosition.x - position.x) / (prevPosition.y - position.y)) * 180 / M_PI, 0, 0, 1);
			if (prevPosition.y - position.y > 0) {
				glRotatef(180, 0, 0, 1);
			}
			//cout << atan((prevPosition.x - position.x) / (prevPosition.y - position.y)) * 90 << endl;

			glColor4f(1, 0.5, 0.0, 1);
			glBegin(GL_POLYGON);
				glVertex3f(0, 20, 0);
				glVertex3f(-10, 0, 0);
				glVertex3f(-10, -15, 0);
				glVertex3f(10, -15, 0);
				glVertex3f(10, 0, 0);
			glEnd();

		glPopMatrix();
		glPushMatrix();
			glColor4f(1, 1, 0.0, 0.2);
			glTranslatef(position.x, position.y, 0);
			glutWireCircle(search_range, 100);
			glColor4f(1, 1, 0.0, 0.1);
			//glutSolidCircle(search_range, 100);
		glPopMatrix();
		
		
		
		glTranslatef(-15, 0, 0);
		glColor4f(1, 1, 1, 0.5);
		glTranslatef(0, 15, 1);
		glutDrawBitmapText("  ^     ^", this->position.x, this->position.y);
		glTranslatef(0, -5, 0);
		glutDrawBitmapText("( \" w \" )", this->position.x, this->position.y);
		

	
	glPopMatrix();
}
bool Cat::search(double x, double y) {
	double dist = sqrt(pow(x - position.x, 2) + pow(y - position.y, 2));
	if (dist < search_range)
		return true;
	return false;
}

//void Cat::MoveTo(double x, double y, BenList<int>wall) {
//	
//	double dist = sqrt(pow(target.x - position.x, 2) + pow(1000-target.y - position.y, 2));
//	double dx = (target.x - position.x) / (dist*velo);
//	double dy = (1000-target.y - position.y) / (dist*velo);
//
//
//	counter++;
//	if (counter == 60) {
//		counter = 0;
//		target.x = x;
//		target.y = y;
//	}
//	Axis temp;
//	temp.x = position.x + dx;
//	temp.y = position.y + dy;
//	//cout << temp.x << " " << temp.y << endl;
//	if (Collision(wall, temp)) {
//		//cout << "why" << endl;
//	}
//	else {
//		//cout << getAddress(position) << endl;;
//		prevPosition.x = position.x;
//		prevPosition.y = position.y;
//		position.x += dx;
//		position.y += dy;
//	}
//}