#include "../lib/catch.hpp"
#include "../../core/include/distance.hpp"


using namespace cluster::distance;


typedef cluster::Vector<float, 2> Vector2;

TEST_CASE("distance: euclidean2", 
          "[distance-functions][distance-euclidean2]")
{
    auto dist = euclidean2<float, 2>;
    const Vector2 a{0.0f, 0.0f},
                  b{3.0f, 4.0f};

    REQUIRE(dist(a, a) == 0);
    REQUIRE(dist(b, b) == 0);
    REQUIRE(dist(a, b) == dist(b, a));
    REQUIRE(dist(a, b) == 25);
}

TEST_CASE("distance: manhattan", 
          "[distance-functions][distance-manhattan]")
{
    auto dist = manhattan<float, 2>;
    const Vector2 a{0.0f, 0.0f},
                  b{3.0f, 4.0f};

    REQUIRE(dist(a, a) == 0);
    REQUIRE(dist(b, b) == 0);
    REQUIRE(dist(a, b) == dist(b, a));
    REQUIRE(dist(a, b) == 7);
}
