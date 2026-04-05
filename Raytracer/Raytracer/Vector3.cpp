#include "Vector3.h"

double Vector3::x() const {
	return i[0];
}

double Vector3::y() const {
	return i[1];
}

double Vector3::z() const {
	return i[2];
}

Vector3 Vector3::operator-() const {
	return Vector3(-i[0], -i[1], -i[2]);
}

double Vector3::operator[](int i) const {
	return this->i[i];
}

double& Vector3::operator[](int i) {
	return this->i[i];
}

Vector3& Vector3::operator+=(const Vector3& in) {
	i[0] += in.i[0];
	i[1] += in.i[1];
	i[2] += in.i[2];
	return *this;
}

Vector3& Vector3::operator*=(double scalar) {
	i[0] *= scalar;
	i[1] *= scalar;
	i[2] *= scalar;
	return *this;
}

Vector3& Vector3::operator/=(double scalar) {
	return *this *= 1 / scalar;
}

double Vector3::Length() const {
	return std::sqrt(LengthSquared());
}

double Vector3::LengthSquared() const {
	return i[0] * i[0] + i[1] * i[1] + i[2] * i[2];
}

//tutorial states that this is an alias for vector3 that is useful for gemoetry clarity within the codebase
using point = Vector3;

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
