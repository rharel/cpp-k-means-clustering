#ifndef K_MEANS_DISTANCE_H
#define K_MEANS_DISTANCE_H
/**
 * @file distance.hpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Distance functions.
 */


#include "Vector.hpp"


namespace cluster 
{ 
    /*
     * Distance function signature.
     *
     * @tparam NumericType Data type.
     * @tparam Dimension   Data dimension.
     */
    template<typename NumericType, size_t Dimension>
    using DistanceFunction = float (*) (const Vector<NumericType, Dimension>& a, 
                                        const Vector<NumericType, Dimension>& b);

    /**
     * Container namespace for common distance functions.
     */
    namespace distance 
    {
        /**
         * Computes Euclidean distance squared.
         *
         * @see DistanceFunction
         */
        template<typename NumericType, size_t Dimension>
        float euclidean2(const Vector<NumericType, Dimension>& a, 
                         const Vector<NumericType, Dimension>& b);
        /**
         * Computes Manhattan distance.
         *
         * @see DistanceFunction
         */
        template<typename NumericType, size_t Dimension>
        float manhattan(const Vector<NumericType, Dimension>& a, 
                        const Vector<NumericType, Dimension>& b);
    }
}


#include "distance.cpp"


#endif  // K_MEANS_DISTANCE_H
