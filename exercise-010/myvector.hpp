#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

namespace tfe24 {

template <typename T>
class myvector {
public:
    // Konstruktoren
    myvector() noexcept : m_data(nullptr), m_size(0), m_capacity(0) {}
    
    explicit myvector(std::size_t count)
        : m_data(count ? new T[count]() : nullptr), 
          m_size(count), 
          m_capacity(count) {}

    // Destruktor
    ~myvector() { delete[] m_data; }

    // Rule of Three
    myvector(const myvector& other)
        : m_data(other.m_capacity ? new T[other.m_capacity] : nullptr),
          m_size(other.m_size),
          m_capacity(other.m_capacity) {
        if (m_data) {
            std::copy(other.m_data, other.m_data + other.m_size, m_data);
        }
    }

    myvector& operator=(const myvector& other) {
        if (this != &other) {
            T* new_data = other.m_capacity ? new T[other.m_capacity] : nullptr;
            try {
                if (new_data) {
                    std::copy(other.m_data, other.m_data + other.m_size, new_data);
                }
            } catch (...) {
                delete[] new_data;
                throw;
            }
            delete[] m_data;
            m_data = new_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
        }
        return *this;
    }

    // Basis-Methoden
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        m_data[m_size++] = value;
    }

    T& at(std::size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    const T& at(std::size_t index) const {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    // KORRIGIERT: Vollständige operator[] Überladungen
    T& operator[](std::size_t index) {
        return m_data[index];
    }

    const T& operator[](std::size_t index) const {
        return m_data[index];
    }

    std::size_t size() const noexcept { return m_size; }
    std::size_t capacity() const noexcept { return m_capacity; }

    void resize(std::size_t new_size) {
        if (new_size > m_capacity) {
            reserve(new_size);
        }
        // Neue Elemente mit Default-Wert initialisieren
        if (new_size > m_size) {
            std::fill(m_data + m_size, m_data + new_size, T());
        }
        m_size = new_size;
    }

    void clear() noexcept { m_size = 0; }

    void reserve(std::size_t new_cap) {
        if (new_cap > m_capacity) {
            T* new_data = new T[new_cap]();  // Mit Wertinitialisierung
            try {
                // KORRIGIERT: std::copy statt std::move für Sicherheit
                if (m_data) {
                    std::copy(m_data, m_data + m_size, new_data);
                }
            } catch (...) {
                delete[] new_data;
                throw;
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_cap;
        }
    }

private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
};

} // namespace tfe24

#endif // MYVECTOR_HPP