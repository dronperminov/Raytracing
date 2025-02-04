#pragma once

#include <iostream>
#include "Primitive.hpp"

// конечная плоскость
class Flatness : public Primitive {
protected:
    Vec normal; // нормаль
    Vec center; // центр
    Vec size; // размер плоскости
public:
    Flatness(std::istream &is, Material material); // конструктор из потока

    Primitive* Intersect(const Ray &ray, double tmin, double tmax, double &t); // пересечение с лучём
    Vec GetNormal(const Vec &point); // получение нормали
};

// конструктор из потока
Flatness::Flatness(std::istream &is, Material material) {
    double sz;
    this->material = material;
    is >> normal >> center >> sz;

    normal.Normalize();

    double dx = sqrt(1 - normal.x * normal.x);
    double dy = sqrt(1 - normal.y * normal.y);
    double dz = sqrt(1 - normal.z * normal.z);

    size = Vec(dx, dy, dz) * sz;
}

// пересечение с лучём
Primitive* Flatness::Intersect(const Ray &ray, double tmin, double tmax, double &t) {
    double denom = ray.direction.Dot(normal);

    if (fabs(denom) < EPSILON)
        return nullptr;

    t = (center - ray.origin).Dot(normal) / denom; // пересечение с плоскостью

    if (t < tmin || t >= tmax)
        return nullptr;

    Vec point = ray.GetPoint(t); // находим точку на плоскости

    Vec delta = point - center;

    if (fabs(delta.x) > size.x + EPSILON || fabs(delta.y) > size.y + EPSILON || fabs(delta.z) > size.z + EPSILON)
        return nullptr;

    return this;
}

// получение нормали
Vec Flatness::GetNormal(const Vec &point) {
    return normal;
}
