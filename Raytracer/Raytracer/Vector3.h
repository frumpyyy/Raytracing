#pragma once

#include <cmath>
#include <iostream>

class Vector3 {
public:
	//using double over float due to double precision (64-bit over 32-bit float)
	double i[3];

	//default constructor
	Vector3() : i{ 0,0,0 } {}

	//constructor that takes in values to store within the Vector 3
	Vector3(double i0, double i1, double i2) : i{ i0,i1,i2 } {}


	//get functions
	double x() const;
	double y() const;
	double z() const;

	//negate vector
	Vector3 operator-() const;

	//use index as get instead of x,y or z function
	double operator[](int i) const;
	double& operator[](int i);

	//mathematical operators
	Vector3& operator+=(const Vector3& in);
	Vector3& operator*=(double scalar);
	Vector3& operator/=(double scalar);

	//vector unique functions
	double Length() const;
	double LengthSquared() const;
};
