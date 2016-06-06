#ifndef K_MEANS_RANDOM_H
#define K_MEANS_RANDOM_H
/**
 * @file seeder.hpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Seeder methods.
 */


#include <random>


namespace cluster
{
    /**
     * Container for random operations.
     */
    namespace random
    {
        /**
         * Gets random integral type in range.
         */
        template<typename IntegralType>
        IntegralType int_in_range(IntegralType min, IntegralType max)
        {
            static_assert(std::is_integral<IntegralType>::value, 
                          "integral type required");

            #ifdef _DEBUG
            static std::mt19937 engine;  // use default seed
            #else
            static std::random_device device;
            static std::mt19937 engine(device());
            #endif
            
            std::uniform_int_distribution<IntegralType> distribution(min, max);
            return distribution(engine);
        }
    }
}


#endif  // K_MEANS_RANDOM_H
