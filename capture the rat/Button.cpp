#include"button.h"

RButton::RButton() {

}

Axis RButton::getPosition() {
	return position;
}

Axis RButton::getSize() {
	return size;
}

bool RButton::Clicked(double x, double y) {

	return true;
}	