#ifndef K_MEANS_SEEDER_H
#define K_MEANS_SEEDER_H
/**
 * @file seeder.hpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Seeder methods.
 */


#include "Vector.hpp"


namespace cluster
{
    /**
     * Seeder function signature.
     *
     * @tparam InputIterator  Iterator type of the observation container.
     * @tparam OutputIterator Iterator type of output container.
     *
     * @param k Number of means to seed.
     */
    template<typename NumericType, size_t Dimension, 
             typename InputIterator, typename OutputIterator>
    using SeederFunction = void (*)(size_t k, 
                                    InputIterator begin, InputIterator end,
                                    OutputIterator out);

    /**
     * Container namespace for common seeder functions.
     */
    namespace seeder
    {
        /**
         * The forgy method.
         *
         * @details Selects random observations to be initial means.
         *
         * @see SeederFunction
         */
        template<typename NumericType, size_t Dimension, 
                 typename InputIterator, typename OutputIterator>
        void forgy(size_t k, 
              InputIterator begin, InputIterator end,
              OutputIterator out);
        /**
         * The random partition method.
         *
         * @details Assigns random clusters to observations and computes the means.
         *
         * @see SeederFunction
         */
        template<typename NumericType, size_t Dimension, 
                 typename InputIterator, typename OutputIterator>
        void random_partition(size_t k, 
                         InputIterator begin, InputIterator end,
                         OutputIterator out);
    }
}


#include "seeder.cpp"


#endif  // K_MEANS_SEEDER_H
