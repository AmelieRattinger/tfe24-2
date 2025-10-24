#include "point.hpp"
#include <fmt/core.h>
#include <cmath>

// Standardkonstruktor
Point::Point() : m_x(0), m_y(0) {}

// Konstruktor mit Parametern
Point::Point(double x, double y) : m_x(x), m_y(y) {}

// Destruktor
Point::~Point() {}

// Methode zum Verschieben
void Point::move(double dx, double dy) {
    m_x += dx;
    m_y += dy;
}

// Methode zur Ausgabe
void Point::print() const {
    fmt::print("({}, {})\n", m_x, m_y);
}


// Methode zur Berechnung des Abstands
double Point::distance_to(const Point& other) const {
    double dx = m_x - other.m_x;
    double dy = m_y - other.m_y;
    return std::sqrt(dx * dx + dy * dy);
}
