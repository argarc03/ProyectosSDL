#include "Vector2D.h"
#include <math.h>

using namespace std;

double Vector2D::getX() const{
	return x;
}

double Vector2D::getY() const{
	return y;
}

void Vector2D::normalize() {
	double modulo = sqrt(pow(x, 2) + pow(y, 2));
	x = x / modulo;
	y = y / modulo;
}

Vector2D Vector2D::operator+(const Vector2D& u) {
	return Vector2D(x + u.x, y + u.y);
}

Vector2D Vector2D::operator-(const Vector2D& u) {
	return Vector2D(x - u.x, y - u.y);
}

double Vector2D::operator*(const Vector2D& u) {
	return x*u.x+y*u.y;
}

Vector2D Vector2D::operator*(double num) {
	return Vector2D(x * num, y *num);
}

istream& operator>>(istream& in, Vector2D& v) {
	in >> v.x >> v.y;
	return in;
}

ostream& operator<<(ostream& out, const Vector2D& v) {
	out << v.x << " " << v.y;
	return out;
}
