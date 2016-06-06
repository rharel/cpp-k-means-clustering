/**
 * @file seeder.cpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Seeder methods.
 */


#include "seeder.hpp"
#include "random.hpp"


template<typename T, size_t D, typename InIt, typename OutIt>
void
cluster::seeder::forgy(size_t k, InIt begin, InIt end, OutIt out)
{
    std::vector<Vector<T, D>> result(k);
    std::vector<Vector<T, D>> observations(begin, end);
    const size_t n = observations.size();
    for (size_t i = 0; i < k; ++i)
    {
        result.at(i) = observations[random::int_in_range<size_t>(0, n - 1)];
    }
    std::copy_n(result.begin(), k, out);
}
template<typename T, size_t D, typename InIt, typename OutIt>
void
cluster::seeder::random_partition(size_t k, InIt begin, InIt end, OutIt out)
{
    std::vector<Vector<T, D>> result(k);
    std::vector<size_t> assigned_observation_counts(k);
    std::vector<Vector<T, D>> observations(begin, end);
    const size_t n = observations.size();
    for (size_t i = 0; i < n; ++i)
    {
        const size_t cls = random::int_in_range<size_t>(0, k - 1);
        result.at(cls) += observations.at(i);
        ++ assigned_observation_counts.at(cls);
    }
    for (size_t i = 0; i < k; ++i)
    {
        result.at(i) = result.at(i).scale
        (
            1.0f / 
            static_cast<float>(assigned_observation_counts.at(i))
        );
    }
    std::copy_n(result.begin(), k, out);
}
