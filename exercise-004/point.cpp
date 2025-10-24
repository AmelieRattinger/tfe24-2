#include "point.hpp"
#include <fmt/core.h>

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