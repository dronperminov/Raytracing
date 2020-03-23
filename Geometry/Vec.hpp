#ifndef VEC_HPP
#define VEC_HPP

#include <iostream>
#include <cmath>
#include "Constants.hpp"

class Vec {
	double x;
	double y;
	double z;
public:
	Vec(); // нулевой вектор
	Vec(double x, double y, double z); // вектор из координат
	Vec(std::istream &is); // вектор из потока

	double Norm() const; // получение нормы вектора
	double Dot(const Vec& vec) const; // скалярное произведение векторов

	Vec Normalized() const; // получение нормализованного вектора
	Vec Cross(const Vec& vec) const; // векторное произведение векторов
	Vec Reflect(const Vec& normal) const; // отражение относительно нормали
	Vec Transform(const double matrix[3][3]) const; // матричное преобразование

	Vec RotateX(double alpha) const; // вращение относительно Z
	Vec RotateY(double alpha) const; // вращение относительно Z
	Vec RotateZ(double alpha) const; // вращение относительно Z

	Vec Min(const Vec& vec) const; // покоординатный минимум
	Vec Max(const Vec& vec) const; // покоординатный максимум

	Vec operator+(const Vec& vec) const; // сложение векторов
	Vec operator-(const Vec& vec) const; // разность векторов
	Vec operator*(const Vec& vec) const; // покоординатное умножение
	Vec operator*(double a) const; // умножение на число

	void Clamp(double min, double max); // обрезка значение по интервалу [min, max]
	double GetX() const;
	double GetY() const;
	double GetZ() const;

	friend std::istream& operator>>(std::istream& is, Vec& vec);
	friend std::ostream& operator<<(std::ostream& os, const Vec& vec);
};

// нулевой вектор
Vec::Vec() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

// вектор из координат
Vec::Vec(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

// вектор из потока
Vec::Vec(std::istream &is) {
	is >> x >> y >> z;
}

// получение нормы вектора
double Vec::Norm() const {
	return sqrt(x*x + y*y + z*z);
}

// скалярное произведение векторов
double Vec::Dot(const Vec& vec) const {
	return x*vec.x + y*vec.y + z*vec.z;
}

// получение нормализованного вектора
Vec Vec::Normalized() const {
	double norm = Norm();

	return norm < EPSILON ? Vec() : Vec(x / norm, y / norm, z / norm);
}

// векторное произведение векторов
Vec Vec::Cross(const Vec& vec) const {
	return Vec(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

// отражение относительно нормали
Vec Vec::Reflect(const Vec& normal) const {
	return *this - normal * (2 * normal.Dot(*this));
}

// матричное преобразование
Vec Vec::Transform(const double matrix[3][3]) const {
	double x1 = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z;
	double y1 = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z;
	double z1 = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z;
	return Vec(x1, y1, z1);
}

// вращение относительно X
Vec Vec::RotateX(double alpha) const {
    return Vec(x, cos(alpha) * y - sin(alpha) * z, sin(alpha) * y + cos(alpha) * z);
}

// вращение относительно Y
Vec Vec::RotateY(double alpha) const {
    return Vec(cos(alpha) * x - sin(alpha) * z, y, sin(alpha) * x + cos(alpha) * z);
}

// вращение относительно Z
Vec Vec::RotateZ(double alpha) const {
    return Vec(cos(alpha) * x - sin(alpha) * y, sin(alpha) * x + cos(alpha) * y, z);
}

// покоординатный минимум
Vec Vec::Min(const Vec& vec) const {
	return Vec(std::min(x, vec.x), std::min(y, vec.y), std::min(z, vec.z));
}

// покоординатный максимум
Vec Vec::Max(const Vec& vec) const {
	return Vec(std::max(x, vec.x), std::max(y, vec.y), std::max(z, vec.z));
}

// сложение векторов
Vec Vec::operator+(const Vec& vec) const {
	return Vec(x + vec.x, y + vec.y, z + vec.z);
}

// разность векторов
Vec Vec::operator-(const Vec& vec) const {
	return Vec(x - vec.x, y - vec.y, z - vec.z);
}

// покоординатное умножение
Vec Vec::operator*(const Vec& vec) const {
	return Vec(x * vec.x, y * vec.y, z * vec.z);
}

// умножение на число
Vec Vec::operator*(double a) const {
	return Vec(x * a, y * a, z * a);
}

// обрезка значение по интервалу [min, max]
void Vec::Clamp(double min, double max) {
	x = std::max(min, std::min(max, x));
	y = std::max(min, std::min(max, y));
	z = std::max(min, std::min(max, z));
}

double Vec::GetX() const {
	return x;
}

double Vec::GetY() const {
	return y;
}

double Vec::GetZ() const {
	return z;
}

std::istream& operator>>(std::istream& is, Vec& vec) {
	return is >> vec.x >> vec.y >> vec.z;
}

std::ostream& operator<<(std::ostream& os, const Vec& vec) {
	return os << "[" << vec.x << " " << vec.y << " " << vec.z << "]";
}

#endif