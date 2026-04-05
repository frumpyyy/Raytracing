#pragma once

#include "MathConstants.h"

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

	//static Vector3 random() {
	//	return Vector3(random_double())
	//}
	//static Vector3 random(double min, double max);

};

//tutorial states that this is an alias for vector3 that is useful for gemoetry clarity within the codebase
using point3 = Vector3;


//Vector utility functions

inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
	return out << v.i[0] << ' ' << v.i[1] << ' ' << v.i[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v) {
	return Vector3(u.i[0] + v.i[0], u.i[1] + v.i[1], u.i[2] + v.i[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v) {
	return Vector3(u.i[0] - v.i[0], u.i[1] - v.i[1], u.i[2] - v.i[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v) {
	return Vector3(u.i[0] * v.i[0], u.i[1] * v.i[1], u.i[2] * v.i[2]);
}

inline Vector3 operator*(double t, const Vector3& v) {
	return Vector3(t * v.i[0], t * v.i[1], t * v.i[2]);
}

inline Vector3 operator*(const Vector3& v, double t) {
	return t * v;
}

inline Vector3 operator/(const Vector3& v, double t) {
	return (1 / t) * v;
}

inline double Dot(const Vector3& u, const Vector3& v) {
	return u.i[0] * v.i[0]
		+ u.i[1] * v.i[1]
		+ u.i[2] * v.i[2];
}

inline Vector3 Cross(const Vector3& u, const Vector3& v) {
	return Vector3(u.i[1] * v.i[2] - u.i[2] * v.i[1],
		u.i[2] * v.i[0] - u.i[0] * v.i[2],
		u.i[0] * v.i[1] - u.i[1] * v.i[0]);
}

inline Vector3 UnitVector(const Vector3& v) {
	return v / v.Length();
}
