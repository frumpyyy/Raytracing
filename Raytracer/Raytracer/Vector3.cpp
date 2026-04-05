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
