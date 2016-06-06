## What is this?

A simple implementation of the [k-mean clustering](https://en.wikipedia.org/wiki/K-means_clustering) algorithm for C++.


## Installation

This is a header-only library, simply `#include "kmeans.hpp"` from [core/include/](core/include/) and you're good to go!


## Usage

### Create

```cpp
using namespace cluster;
typedef Vector<float, 2> Vector2f;

const std::vector<Vector2f> observations = ...;
const size_t cluster_count = 3;
kMeans<float, 2, distance::euclidean2<float, 2>> solver(

    cluster_count,
    &observations[0], observations.size()
); // for two dimensional floating-point data and
   // euclidean distance measure.
```

### Initialize means

```cpp
const std::vector<Vector2f> initial_means = ...;
solver.initialize(&initial_means[0]);
```

### Run the algorithm

#### Automatically
```cpp
const size_t max_iterations = 3;
solver.run(max_iterations);
```

#### Manually
```cpp
const size_t max_iterations = 3;
size_t i = 0;
while (i < max_iterations && solver.assign())
{
    solver.update();
    ++ i;
}
```

### Inspect means

```cpp
Vector2f cluster_mean = solver.mean(i);
// Where i in range [0, cluster_count)
```

## Further documentation

Refer to the [docs](docs/).

## Demo

An example application can be found under [demo/](demo/). The python script under [demo/scripts/](demo/scripts/) was used to generate some random data points, cluster them using the demo executable, and export visualization of intermediate steps of the algorithm under [demo/scripts/visuals/](demo/scripts/visuals/).

## License

This software is licensed under the **MIT License**. See the [LICENSE](LICENSE.txt) file for more information.
