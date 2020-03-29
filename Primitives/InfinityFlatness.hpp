#pragma once

#include <iostream>
#include "Primitive.hpp"

// бесконечная плоскость
class InfinityFlatness : public Primitive {
protected:
    Vec normal; // нормаль
    double bias; // смещение

public:
    InfinityFlatness(std::istream &is, Material material); // конструктор из потока

    Primitive* Intersect(const Ray &ray, double &t); // пересечение с лучём
    Vec GetNormal(const Vec &point); // получение нормали
};

// конструктор из потока
InfinityFlatness::InfinityFlatness(std::istream &is, Material material) {
    this->material = material;
    is >> normal >> bias;
    normal.Normalize();
}

// пересечение с лучём
Primitive* InfinityFlatness::Intersect(const Ray &ray, double &t) {
    double denom = ray.direction.Dot(normal);

    if (fabs(denom) < EPSILON){
        t = INF;
        return nullptr;
    }

    t = -(bias + ray.origin.Dot(normal)) / denom;
    return this;
}

// получение нормали
Vec InfinityFlatness::GetNormal(const Vec &point) {
    return normal;
}