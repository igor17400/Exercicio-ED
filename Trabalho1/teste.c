#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "igao.c"
// "Copyright [year] <Copyright Owner>"

// -fprofile-arcs -ftest-coverage
TEST_CASE("Teste Igao" , "bora") {
    REQUIRE(valida("2 + 2") == true);
}