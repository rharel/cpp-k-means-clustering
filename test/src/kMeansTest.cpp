#define CATCH_CONFIG_MAIN

#include "../lib/catch.hpp"
#include "../../core/include/kmeans.hpp"

#include <array>


using namespace cluster;


typedef Vector<float, 1> Vector1;

TEST_CASE("kMeans", "[kMeans]")
{
    const size_t k = 2, n = 4;
    const Vector1 observations[n] 
    {
        Vector1{1.0f},
        Vector1{2.0f},

        Vector1{8.0f},
        Vector1{9.0f}
    };
    kMeans
    <
        float, 1, 
        distance::euclidean2<float, 1>
    > 
        solver(k, &observations[0], n);

    REQUIRE(solver.k() == k);
    REQUIRE(solver.n() == n);

    for (size_t i = 0; i < n; ++i) 
    {
        REQUIRE(solver.observation(i) == observations[i]);
        REQUIRE(solver.cluster(i) == 0);
    }

    Vector1 initial_means[k]
    {
        Vector1{ 4.5f },
        Vector1{ 5.5f }
    };
    solver.initialize(&initial_means[0]);

    for (size_t i = 0; i < k; ++i)
    {
        REQUIRE(solver.mean(i) == initial_means[i]);
    }
    
    SECTION("manual run")
    {
        // first iteration //

        REQUIRE(solver.assign());  // expect no convergence
        const size_t cluster_a = solver.cluster(0),
                     cluster_b = solver.cluster(2);
        Vector1 expected_means[2];
        expected_means[cluster_a] = Vector1{1.5f};
        expected_means[cluster_b] = Vector1{8.5f};
        
        REQUIRE(cluster_a < k);
        REQUIRE(cluster_b < k);
        REQUIRE(cluster_a != cluster_b);
        REQUIRE(solver.cluster(1) == cluster_a);
        REQUIRE(solver.cluster(3) == cluster_b);
        REQUIRE(solver.cluster_size(cluster_a) == 2);
        REQUIRE(solver.cluster_size(cluster_b) == 2);

        solver.update();
        REQUIRE(solver.mean(cluster_a) == expected_means[cluster_a]);
        REQUIRE(solver.mean(cluster_b) == expected_means[cluster_b]);

        // second iteration //

        REQUIRE_FALSE(solver.assign());  // expect convergence
        REQUIRE(solver.cluster(1) == cluster_a);
        REQUIRE(solver.cluster(3) == cluster_b);
        REQUIRE(solver.cluster_size(cluster_a) == 2);
        REQUIRE(solver.cluster_size(cluster_b) == 2);
    }
    SECTION("auto run")
    {
        REQUIRE(solver.run(0) == 0);
        REQUIRE(solver.run(2) == 1);

        const size_t cluster_a = solver.cluster(0),
                     cluster_b = solver.cluster(2);
        Vector1 expected_means[2];
        expected_means[cluster_a] = Vector1{1.5f};
        expected_means[cluster_b] = Vector1{8.5f};

        REQUIRE(solver.cluster(1) == cluster_a);
        REQUIRE(solver.cluster(3) == cluster_b);
        REQUIRE(solver.cluster_size(cluster_a) == 2);
        REQUIRE(solver.cluster_size(cluster_b) == 2);

        REQUIRE(solver.mean(cluster_a) == expected_means[cluster_a]);
        REQUIRE(solver.mean(cluster_b) == expected_means[cluster_b]);
    }
}
