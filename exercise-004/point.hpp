#ifndef POINT_HPP
#define POINT_HPP


#include <fmt/core.h> // fmt-Bibliothek für die Ausgabe

class Point {
public:
    Point();                         // Standardkonstruktor
    Point(double x, double y);       // Konstruktor mit Parametern
    ~Point();                        // Destruktor

    void move(double dx, double dy); // Methode zum Verschieben
    void print() const;              // Methode zur Ausgabe
private:
    double m_x;
    double m_y;
};

#endif // POINT_HP
