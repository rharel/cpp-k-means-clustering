/**
 * @file distance.cpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Distance functions.
 */


#include "distance.hpp"


template<typename T, size_t D>
float cluster::distance::euclidean2<T, D>(

    const Vector<T, D>& a, const Vector<T, D>& b
)
{
    float dot = 0;
    for (size_t i = 0; i < D; ++i)
    {
        dot += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return dot;
}
template<typename T, size_t D>
float cluster::distance::manhattan<T, D>(

    const Vector<T, D>& a, const Vector<T, D>& b
)
{
    float sum = 0;
    for (size_t i = 0; i < D; ++i)
    {
        sum += std::abs(a[i] - b[i]);
    }
    return sum;
}
