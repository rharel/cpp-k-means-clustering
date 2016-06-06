#include "../lib/catch.hpp"
#include "../../core/include/seeder.hpp"

#include <vector>


using namespace cluster::seeder;


typedef cluster::Vector<float, 1> Vector1;

TEST_CASE("seeder: forgy", 
          "[seeder-functions][seeder-forgy]")
{
    Vector1 observations[2]
    {
        Vector1{0.0f},
        Vector1{10.0f}
    };
    std::vector<Vector1> result(1);
    forgy<float, 1>
    (
        1, 
        &observations[0], &observations[2],
        result.begin()
    );
    const bool is_observation =
    (
        result.at(0) == observations[0] || 
        result.at(0) == observations[1]
    );
    
    REQUIRE(result.size() == 1);
    REQUIRE(is_observation);
}

TEST_CASE("seeder: random-partition", 
          "[seeder-functions][seeder-random-partition]")
{
    Vector1 observations[2]
    {
        Vector1{0.0f},
        Vector1{10.0f}
    };
    std::vector<Vector1> result(1);
    random_partition<float, 1>
    (
        1, 
        &observations[0], &observations[2],
        result.begin()
    );
    const Vector1 expected_result = (observations[0] + observations[1]).scale(0.5f);

    REQUIRE(result.size() == 1);
    REQUIRE(result.at(0) == expected_result);
}
