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

	bool NearZero()const {
		auto s = 1e-8;
		return(std::fabs(i[0]) < s) && (std::fabs(i[1]) < s) && (std::fabs(i[2]) < s);
	}

	static Vector3 random() {
		return Vector3(random_double(), random_double(), random_double());
	}

	static Vector3 random(double min, double max) {
		return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

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

inline Vector3 RandomUnitVector() {
	while (true) {
		Vector3 point = Vector3::random(-1, 1);
		double len = point.LengthSquared();
		if (1e-160 < len && len <= 1)
			return point / std::sqrt(len);
	}
}

inline Vector3 RandomOnHemisphere(const Vector3& normal) {
	Vector3 onUnitSphere = RandomUnitVector();
	if (Dot(onUnitSphere, normal) > 0.0)
		return onUnitSphere;
	else
		return -onUnitSphere;
}

inline Vector3 reflect(const Vector3& v, const Vector3& n) {
	return v - 2 * Dot(v, n) * n;
}