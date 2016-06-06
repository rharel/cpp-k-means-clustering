#include "../lib/catch.hpp"
#include "../../core/include/Vector.hpp"


using namespace cluster;


typedef cluster::Vector<float, 2> Vector2;

TEST_CASE("Vector", "[vector]")
{
    SECTION("constructor")
    {
        const Vector2 v_default,
                  v_uniform(1.0f),
                  v_list{1.0f, 2.0f};

        REQUIRE(v_default[0] == 0);
        REQUIRE(v_default[1] == 0);
        REQUIRE(v_uniform[0] == 1);
        REQUIRE(v_uniform[1] == 1);
        REQUIRE(v_list[0] == 1);
        REQUIRE(v_list[1] == 2);
    }
    
    const Vector2 a{1.0f, 2.0f},
                  b{3.0f, 4.0f};
    Vector2 c;

    SECTION("comparison")
    {
        REQUIRE(a == a);
        REQUIRE_FALSE(a == b);
        REQUIRE(a != b);
        REQUIRE_FALSE(a != a);
    }
    SECTION("unary")
    {
        c = -a;
        REQUIRE(c[0] == -a[0]);
        REQUIRE(c[1] == -a[1]);
    }
    SECTION("binary")
    {
        c = a + b;
        REQUIRE(c[0] == a[0] + b[0]);
        REQUIRE(c[1] == a[1] + b[1]);

        c = a - b;
        REQUIRE(c[0] == a[0] - b[0]);
        REQUIRE(c[1] == a[1] - b[1]);

        c = a * b;
        REQUIRE(c[0] == a[0] * b[0]);
        REQUIRE(c[1] == a[1] * b[1]);

        c = a / b;
        REQUIRE(c[0] == a[0] / b[0]);
        REQUIRE(c[1] == a[1] / b[1]);
    }
    SECTION("assignment")
    {
        c = a;
        REQUIRE(c[0] == a[0]);
        REQUIRE(c[1] == a[1]);

        SECTION("addition")
        {
            c += b;
            REQUIRE(c[0] == a[0] + b[0]);
            REQUIRE(c[1] == a[1] + b[1]);
        }
        SECTION("subtraction")
        {
            c -= b;
            REQUIRE(c[0] == a[0] - b[0]);
            REQUIRE(c[1] == a[1] - b[1]);
        }
        SECTION("multiplication")
        {
            c *= b;
            REQUIRE(c[0] == a[0] * b[0]);
            REQUIRE(c[1] == a[1] * b[1]);
        }
        SECTION("division")
        {
            c /= b;
            REQUIRE(c[0] == a[0] / b[0]);
            REQUIRE(c[1] == a[1] / b[1]);
        }
    }
    SECTION("scale")
    {
        c = Vector2{1.0f, 2.0f}.scale(3.0f);
        REQUIRE(c[0] == 3.0f);
        REQUIRE(c[1] == 6.0f);
    }
    SECTION("dot")
    {
        REQUIRE(a.dot(b) == (a[0] * b[0] + a[1] * b[1]));
    }
}
