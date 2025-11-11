#include <fmt/chrono.h>
#include <fmt/format.h>
#include "config.h"

#include <fmt/core.h>
#include <CLI/CLI.hpp>
#include "myvector.hpp"

int main(int argc, char** argv) {
    int N = 10;
    double growth = 2.0;

    CLI::App app{"myvector demo"};
    app.add_option("-n,--count", N, "Anzahl der Inserts");
    app.add_option("-g,--growth", growth, "Wachstumsfaktor");
    CLI11_PARSE(app, argc, argv);

    fmt::println("Running with N={} growth={}", N, growth);

    tfe24::myvector<int> vec;
    for (int i = 0; i < N; ++i) {
        vec.push_back(i);
    }

    fmt::println("Size: {}, Capacity: {}", vec.size(), vec.capacity());
    fmt::println("Element at 5: {}", vec.at(5));

    vec.resize(20);
    fmt::println("After resize -> Size: {}, Capacity: {}", vec.size(), vec.capacity());

    vec.clear();
    fmt::println("After clear -> Size: {}", vec.size());

    return 0;
}