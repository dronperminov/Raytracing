#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <iostream>
#include "../Material.hpp"
#include "../Geometry/Vec.hpp"
#include "../Geometry/Ray.hpp"

class Primitive {
protected:
    Material material; // материал
public:
    virtual double Intersect(const Ray &ray) = 0; // поиск пересечения
    virtual Vec GetNormal(const Vec &point) = 0; // нормаль
    virtual Material GetMaterial(const Vec &point); // получение материала в точке
    virtual Vec GetColor(const Vec &point); // получение цвета в точке
    virtual void UpdateBbox(Vec& min, Vec &max) {} // обновление ограничивающего объёма
    virtual ~Primitive() {};
};

// получение материала
Material Primitive::GetMaterial(const Vec &point) {
	return material;
}

// получение цвета в точке
Vec Primitive::GetColor(const Vec &point) {
	return GetMaterial(point).color;
}

#endif