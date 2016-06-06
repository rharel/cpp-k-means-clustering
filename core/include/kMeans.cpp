/**
 * @file kmeans.cpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 *
 * Class kMeans.
 */


#include "kMeans.hpp"


template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
cluster::kMeans<T, D, Distance>::
kMeans
(
    size_t k,
    const Vector<T, D>* obs, size_t n
) : 
    observations_(obs, &obs[n]),
    assigned_clusters_(n, 0),
    mean_observations_(k),
    cluster_sizes_(k) {}

template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
void 
cluster::kMeans<T, D, Distance>::
initialize(const Vector<T, D>* means)
{
    for (size_t i = 0; i < k(); ++i)
    {
        mean_observations_.at(i) = means[i];
    }
}
template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
bool 
cluster::kMeans<T, D, Distance>::
assign()
{
    std::fill_n(cluster_sizes_.begin(), k(), 0);
    bool is_converged = true;
    for (size_t i = 0; i < n(); ++i)
    {
        const Vector<T, D>& obs = observation(i);
        size_t nearest_mean_index = 0;
        float nearest_mean_distance = Distance(obs, mean(0));
        for (size_t j = 1; j < k(); ++j)
        {
            const float distance_to_j = Distance(obs, mean(j));
            if (distance_to_j < nearest_mean_distance)
            {
                nearest_mean_index = j;
                nearest_mean_distance = distance_to_j;
            }
        }
        is_converged = is_converged && assigned_clusters_.at(i) == nearest_mean_index;
        assigned_clusters_.at(i) = nearest_mean_index;
        ++ cluster_sizes_.at(nearest_mean_index);
    }
    return !is_converged;
}
template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
void
cluster::kMeans<T, D, Distance>::
update()
{
    std::vector<Vector<T, D>> new_means(k());
    
    for (size_t i = 0; i < n(); ++i)
    {
        const Vector<T, D>& obs = observation(i);
        const size_t cls = cluster(i);
        new_means.at(cls) += obs;
    }
    for (size_t i = 0; i < k(); ++i)
    {
        mean_observations_.at(i) = new_means.at(i).scale(1.0f / cluster_size(i));
    }
}
template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
size_t
cluster::kMeans<T, D, Distance>::
run(const size_t max_iterations)
{
    size_t i = 0;
    while (i < max_iterations && assign())
    {
        update();
        ++ i;
    }
    return i;
}

template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
const cluster::Vector<T, D>& 
cluster::kMeans<T, D, Distance>::
observation(const size_t index) const
{
    return observations_.at(index);
}
template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
size_t 
cluster::kMeans<T, D, Distance>::
cluster(const size_t index) const
{
    return assigned_clusters_.at(index);
}
template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
size_t 
cluster::kMeans<T, D, Distance>::
cluster_size(const size_t index) const
{
    return cluster_sizes_.at(index);
}
template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
const cluster::Vector<T, D>&
cluster::kMeans<T, D, Distance>::
mean(const size_t index) const
{
    return mean_observations_.at(index);
}

template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
size_t 
cluster::kMeans<T, D, Distance>::
n() const
{
    return observations_.size();
}
template<typename T, size_t D, cluster::DistanceFunction<T, D> Distance>
size_t 
cluster::kMeans<T, D, Distance>::
k() const
{
    return mean_observations_.size();
}
