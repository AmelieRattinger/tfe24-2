#include <fmt/chrono.h>
#include <fmt/format.h>

#include <nlohmann/json.hpp>

#include "CLI/CLI.hpp"
#include "config.h"

#include "point.hpp"
#include "point_fmt.hpp"


// for convenience
using json = nlohmann::json;

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    /* INSERT YOUR CODE HERE */
    Point<int> p1(3, 4);
    Point<int> p2(0, 0);

    fmt::print("Punkt 1: {}\n", p1);
    fmt::print("Punkt 2: {}\n", p2);

    auto dist = p1.distance_to(p2);
    fmt::print("Distanz zwischen Punkt 1 und Punkt 2: {:.2f}\n", dist);

    p1.move(1, -2);
    fmt::print("Punkt 1 nach Verschiebung: {}\n", p1);

    return 0; /* exit gracefully*/
}
