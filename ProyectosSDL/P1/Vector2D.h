#pragma once
#include "checkML.h"
#include <iostream>

using namespace std;

class Vector2D{
private:
	double x;
	double y;

public:
	Vector2D(double x, double y) : x(x), y(y) {};
	~Vector2D() {};

	double getX() const;
	double getY() const;

	void normalize();

	Vector2D operator+(const Vector2D& u);
	Vector2D operator-(const Vector2D& u);
	double operator*(const Vector2D& u);
	Vector2D operator*(double num);
	
	friend istream& operator>>(istream& in, Vector2D& v);
	friend ostream& operator<<(ostream& out, const Vector2D& v);
};

