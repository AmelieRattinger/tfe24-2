#include <catch2/catch_all.hpp>
#include "myvector.hpp"

#include <string>
#include <type_traits>

using tfe24::myvector;

// ---------- Hilfsfunktionen ----------
template <typename V>
static void fill_sequential(V& v, int n, int start = 0) {
    for (int i = 0; i < n; ++i) v.push_back(start + i);
}

// ===============================================================
// Basis: Konstruktoren, Grundzustand, Operatoren
// ===============================================================
TEST_CASE("default constructed vector has size==0 and capacity==0", "[myvector][ctor][basic]") {
    myvector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);
}

TEST_CASE("count constructor initializes size and default values", "[myvector][ctor][init]") {
    SECTION("int elements are value-initialized to 0") {
        myvector<int> v(5);
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() >= 5);        // Implementierung darf >=5 reservieren
        for (std::size_t i = 0; i < v.size(); ++i) {
            REQUIRE(v[i] == 0);
        }
    }

    SECTION("std::string elements are default constructed to empty") {
        myvector<std::string> v(3);
        REQUIRE(v.size() == 3);
        for (std::size_t i = 0; i < v.size(); ++i) {
            REQUIRE(v[i].empty());
        }
    }
}

TEST_CASE("operator[] provides read/write access (no bounds checks)", "[myvector][index]") {
    myvector<int> v;
    v.push_back(10);
    v.push_back(20);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 20);

    v[0] = 99;
    REQUIRE(v[0] == 99);
}

// ===============================================================
// push_back & Wachstumsverhalten
// ===============================================================
TEST_CASE("push_back increases size and triggers capacity growth as needed",
          "[myvector][push_back][growth]") {
    myvector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == 0);

    // Nach erstem push_back muss capacity >= 1 sein
    v.push_back(42);
    REQUIRE(v.size() == 1);
    REQUIRE(v.capacity() >= 1);
    REQUIRE(v[0] == 42);

    // Allgemeines Wachstumsverhalten:
    // - capacity darf nie kleiner als size sein
    // - wenn size die vorherige capacity überschreitet, MUSS capacity wachsen
    std::size_t previous_capacity = v.capacity();
    for (int i = 1; i <= 100; ++i) {
        const std::size_t old_cap = v.capacity();
        const std::size_t old_size = v.size();
        v.push_back(i);

        REQUIRE(v.size() == old_size + 1);
        REQUIRE(v.capacity() >= v.size());

        // Wenn wir über die alte Kapazität hinausgegangen sind, muss es gewachsen sein
        if (old_size >= old_cap) {
            REQUIRE(v.capacity() > old_cap);
        }

        // Kapazität ist monoton nicht fallend
        REQUIRE(v.capacity() >= previous_capacity);
        previous_capacity = v.capacity();
    }

    // Datenerhalt prüfen (inkl. erstes Element 42)
    REQUIRE(v[0] == 42);
    for (int i = 1; i <= 100; ++i) {
        REQUIRE(v[static_cast<std::size_t>(i)] == i);
    }
}

// ===============================================================
// at() – Bounds Checking
// ===============================================================
TEST_CASE("at throws std::out_of_range on invalid index (non-const and const)",
          "[myvector][at][bounds]") {
    myvector<int> v;

    SECTION("empty vector throws on any access") {
        REQUIRE_THROWS_AS(v.at(0), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
    }

    SECTION("within range does not throw; out of range throws") {
        v.push_back(1);
        v.push_back(2);

        REQUIRE_NOTHROW(v.at(0));
        REQUIRE_NOTHROW(v.at(1));
        REQUIRE_THROWS_AS(v.at(2), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(99), std::out_of_range);

        // const-Qualifizierte Variante
        const myvector<int>& cv = v;
        REQUIRE(cv.at(0) == 1);
        REQUIRE(cv.at(1) == 2);
        REQUIRE_THROWS_AS(cv.at(2), std::out_of_range);
    }
}

// ===============================================================
// resize()
// ===============================================================
TEST_CASE("resize larger fills with default-constructed values", "[myvector][resize][grow]") {
    myvector<int> v;
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);

    const std::size_t old_cap = v.capacity();
    v.resize(6);

    REQUIRE(v.size() == 6);
    REQUIRE(v.capacity() >= 6);      // darf wachsen
    REQUIRE(v[0] == 7);
    REQUIRE(v[1] == 8);
    REQUIRE(v[2] == 9);

    // neu hinzugefügte Elemente sind 0 (Default-Konstruktion für int)
    REQUIRE(v[3] == int{});
    REQUIRE(v[4] == int{});
    REQUIRE(v[5] == int{});

    // Kapazität kann wachsen, muss aber nicht kleiner werden
    REQUIRE(v.capacity() >= old_cap);
}

TEST_CASE("resize smaller reduces size and prevents access beyond new size", "[myvector][resize][shrink]") {
    myvector<int> v;
    for (int i = 0; i < 6; ++i) v.push_back(i + 1); // 1..6
    const std::size_t old_cap = v.capacity();

    v.resize(2);
    REQUIRE(v.size() == 2);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);

    // at() muss außerhalb der neuen Größe werfen
    REQUIRE_THROWS_AS(v.at(2), std::out_of_range);

    // Kapazität darf erhalten bleiben (kein Zwang zum Freigeben)
    REQUIRE(v.capacity() == old_cap);
}

// ===============================================================
// clear()
// ===============================================================
TEST_CASE("clear sets size to 0 while capacity is retained", "[myvector][clear]") {
    myvector<int> v;
    fill_sequential(v, 10);
    const std::size_t old_cap = v.capacity();

    v.clear();
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() == old_cap); // Capacity bleibt in der Regel erhalten
    // Nach clear kann wieder eingefügt werden
    v.push_back(123);
    REQUIRE(v.size() == 1);
    REQUIRE(v[0] == 123);
}

// ===============================================================
// Copy-Semantik: Rule of Three
// ===============================================================
TEST_CASE("copy constructor and copy assignment create independent deep copies",
          "[myvector][copy][rule-of-three]") {
    myvector<int> a;
    for (int i = 0; i < 5; ++i) a.push_back(10 + i); // 10..14

    // Copy-Konstruktor
    myvector<int> b = a;
    REQUIRE(b.size() == a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        REQUIRE(b[i] == a[i]);
    }

    // Copy-Zuweisung (auch von leer -> nicht leer & umgekehrt)
    myvector<int> c;
    c = a;
    REQUIRE(c.size() == a.size());
    for (std::size_t i = 0; i < a.size(); ++i) {
        REQUIRE(c[i] == a[i]);
    }

    // Änderungen am Original dürfen Kopien nicht beeinflussen
    a[0] = 99;
    REQUIRE(b[0] != a[0]);
    REQUIRE(c[0] != a[0]);

    // Änderungen an Kopien dürfen Original nicht beeinflussen
    b[1] = 77;
    REQUIRE(a[1] != 77);
    REQUIRE(c[1] != 77);

    // Self-Assignment muss stabil sein
    const std::size_t old_size = a.size();
    const std::size_t old_cap  = a.capacity();
    a = a; // self-assign
    REQUIRE(a.size() == old_size);
    REQUIRE(a.capacity() == old_cap);
    // Inhalte noch gültig (nur spot-check)
    REQUIRE(a[0] == 99);
}

// ===============================================================
// Zusätzlicher Typ-Test: std::string
// ===============================================================
TEST_CASE("works with non-POD types like std::string", "[myvector][string]") {
    myvector<std::string> vs;
    vs.push_back("hello");
    vs.push_back("world");
    REQUIRE(vs.size() == 2);
    REQUIRE(vs.at(0) == "hello");
    REQUIRE(vs.at(1) == "world");

    vs.resize(4);
    REQUIRE(vs.size() == 4);
    // neu hinzugefügte strings sind leer
    REQUIRE(vs[2].empty());
    REQUIRE(vs[3].empty());

    // Kopie unabhängig machen
    auto copy = vs;
    vs[0] = "changed";
    REQUIRE(copy[0] == "hello");
}
