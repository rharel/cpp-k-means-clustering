#ifndef K_MEANS_H
#define K_MEANS_H
/**
 * @file kmeans.hpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Class kMeans.
 */


#include "distance.hpp"
#include "seeder.hpp"
#include "Vector.hpp"

#include <type_traits>
#include <vector>


namespace cluster
{   
    /**
     * The main class of the module. Computes a customizable k-means clustering.
     * 
     * @tparam NumericType Data type.
     * @tparam Dimension   Data dimension.
     */
    template 
    <
        typename NumericType,
        size_t Dimension,
        DistanceFunction<NumericType, Dimension> Distance
    >
    class kMeans
    {
        static_assert(std::is_arithmetic<NumericType>::value, 
                      "arithmetic type required");

        public:
        /**
         * Initialize a new instance for given number of clusters and 
         * observation sequence.
         *
         * @param k            Number of clusters.
         * @param observations Pointer to first observation in sequence.
         * @param n            Number of observations to read from sequence.
         */
        kMeans(size_t k,
               const Vector<NumericType, Dimension>* observations, size_t n);

        /**
         * Sets initial means from a sequence.
         *
         * @param means Pointer to first mean in sequence sequence.
         *
         * @pre Sequence has length >= number of clusters provided in constructor.
         */
        void initialize(const Vector<NumericType, Dimension>* means);
        
        /**
         * Assign observations to clusters.
         * 
         * @details 
         *  After a call to assign(), the assigned clusters can be
         *  inspected through a call to cluster(size_t observation_index).
         *
         * @returns True if there was change in cluster assignment.
         */
        bool assign();

        /**
         * Update cluster means based on current observation-cluster assignment.
         *
         * @details
         *  After a call to update(), the updated means can be 
         *  inspected through a call to mean(size_t cluster_index). 
         */
        void update();

        /**
         * Repeats the assignment and update steps until termination condition is met, or 
         * maximum number of iterations have been performed.
         * 
         * @param max_iterations Maximum number of iterations to perform.
         *
         * @return Number of iterations until termination.
         */
        size_t run(size_t max_iterations);

        /**
         * Gets number of observations.
         */
        size_t n() const;
        /**
         * Gets number of clusters.
         */
        size_t k() const;

        /**
         * Gets observation at index.
         *
         * @pre index is in [0, #(observations)).
         */
        const Vector<NumericType, Dimension>& observation(size_t index) const;
        /**
         * Gets cluster index of observation at index.
         *
         * @pre index is in [0, #(observations)).
         *
         * @note Default value for unassigned observations is cluster zero.
         */
        size_t cluster(size_t index) const;
        /**
         * Gets the number of observations assigned to cluster at index.
         *
         * @pre index is in [0, k).
         */
        size_t cluster_size(size_t index) const;
        /**
         * Gets mean observation of cluster at index.
         *
         * @pre index is in [0, k).
         */
        const Vector<NumericType, Dimension>& mean(size_t index) const;

        private:
        std::vector<Vector<NumericType, Dimension>> observations_;
        std::vector<Vector<NumericType, Dimension>> mean_observations_;
        std::vector<size_t> assigned_clusters_;
        std::vector<size_t> cluster_sizes_;
    };
 }


#include "kMeans.cpp"


#endif  // K_MEANS_H
