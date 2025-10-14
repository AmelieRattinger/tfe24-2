#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

void changeValueByParameter(int value){
    value = 99;
    fmt::print("{}\n",value);
}
auto main(int argc, char **argv) -> int
{

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tfe24::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */

    int x = 10;
    int& r = x;
    fmt::print("{}\n",x);
    fmt::print("{}\n",r);
    r = 42;
    fmt::print("{}\n",x);
    fmt::print("{}\n",r);
    changeValueByParameter(x);
    changeValueByParameter(r);
    fmt::print("{}\n",x);
    fmt::print("{}\n",r);   
    
    
    return 0; /* exit gracefully*/
}
