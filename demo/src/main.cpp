/**
 * @file main.cpp
 * @author Raoul Harel
 * @url github.com/rharel/cpp-k-means-clustering
 * @details
 *      This is a demo command line application utilizing the library.
 *      It loads a .csv file and runs the k-means clustering algorithm
 *      based on the parameters given.
 */


#include "../../core/include/kMeans.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace cluster;


typedef Vector<float, 2> Vector2f;



bool load_csv(const std::string& path, std::vector<Vector2f>& out)
{
    std::ifstream file(path);
    if (!file.is_open()) { return false; }

    float x, y;
    while (file >> x)
    {
        if (file.peek() == ',') { file.ignore(); }
        if (!(file >> y)) { return false; }
        else { out.push_back(Vector2f{x, y}); }
    }
    return true;
}
bool write_csv(const std::string& path, const std::vector<Vector2f>& data)
{
    std::ofstream file(path);
    if (!file.is_open()) { return false; }

    for (const Vector2f& v : data)
    {
        file << v[0] << ", " << v[1] << std::endl;
    }
    return true;
}

void display_help()
{
    std::cout << "This program reads a .csv file of two-dimensional points, " 
              << "runs the k-means clustering algorithm on the data and saves "
              << "the resulting cluster means in a separate .csv file."
              << std::endl << std::endl
              << "Basic usage: "
              << std::endl
              << "kmeans-demo.exe <cluster_count> <input_path> <output_path>"
              << std::endl << std::endl
              << "Optional flags: "
              << std::endl
              << "--help: Display this message."
              << std::endl
              << "--max-iterations <positive-integer>: Max number of iterations to run. "
              <<                                      "Default is 10."
              << std::endl
              << "--distance-manhattan: Use manhattan distance. Default is Euclidean."
              << std::endl
              << "--seeder-partition: Use the random partition method for initialization. "
              <<                     "Default is Forgy's method."
              << std::endl << std::endl << std::flush;
}
struct Options
{
    enum DistanceMethod { Euclidean, Manhattan };
    enum SeederMethod { Forgy, Random_Partition };

    bool show_help = false;
    std::string error_message;

    std::string input_path;
    std::string output_path;
    size_t cluster_count;

    DistanceMethod distance_method = DistanceMethod::Euclidean;
    SeederMethod seeder_method = SeederMethod::Forgy;

    size_t max_iterations = 10;
};
Options parse_arguments(int argc, char* argv[])
{
    static const size_t ARG_CLUSTER_COUNT = 1,
                        ARG_INPUT_PATH = 2,
                        ARG_OUTPUT_PATH = 3;
    Options options;
    if (argc == 2 && std::string(argv[1]) == "--help")
    {
        options.show_help = true;
        return options;
    }
    if (argc < 4) 
    { 
        options.error_message = "Expected <cluster_count> <input_path> <output_path>";
        return options;
    }

    int cluster_count;
    try
    {
        cluster_count = std::stoi(argv[ARG_CLUSTER_COUNT]);
    }
    catch (const std::exception&)
    {
        options.error_message = "Cluster count must be an integer > 0";
        return options;
    }
    if (cluster_count <= 0)
    {
        options.error_message = "Cluster count must be an integer > 0";
        return options;
    }
    else
    { 
        options.cluster_count = static_cast<size_t>(cluster_count); 
    }
    options.input_path = argv[ARG_INPUT_PATH];
    options.output_path = argv[ARG_OUTPUT_PATH];

    for (int i = 4; i < argc; ++i)
    {
        const std::string flag = argv[i];
        
        if (flag == "--max-iterations")
        {
            if (i == argc - 1)
            {
                options.error_message = "Missing number following --max-iterations";
                return options;
            }
            else { ++ i; }
            int n;
            try
            {
                n = std::stoi(argv[i]);
            }
            catch (const std::exception&)
            {
                options.error_message = "Max iterations must be integer > 0";
                return options;
            }
            if (n <= 0)
            {
                options.error_message = "Max iterations must be integer > 0";
                return options;
            }
            options.max_iterations = n;
        }
        else if (flag == "--distance-manhattan")
        {
            options.distance_method = Options::DistanceMethod::Manhattan;
        }
        else if (flag == "--seeder-partition")
        {
            options.seeder_method = Options::SeederMethod::Random_Partition;
        }
        else
        {
            options.error_message = "Unknown argument: " + std::string(argv[i]);
            return options;
        }
    }
    return options;
}

template
<
    typename NumericType, 
    size_t Dimension, 
    DistanceFunction<NumericType, Dimension> Distance
>
std::vector<Vector<NumericType, Dimension>> run_and_record
(
    const size_t cluster_count,
    const std::vector<Vector<NumericType, Dimension>>& observations,
    const std::vector<Vector<NumericType, Dimension>>& initial_means,
    const size_t max_iterations
)
{
    std::vector<Vector<NumericType, Dimension>> result;
    result.reserve(max_iterations * cluster_count);
    kMeans<NumericType, Dimension, Distance> solver
    (
        cluster_count, 
        &observations[0], observations.size()
    );
    solver.initialize(&initial_means[0]);
    for (size_t j = 0; j < cluster_count; ++j)
    {
        result.push_back(solver.mean(j));
    }

    size_t i = 0;
    while (i < max_iterations && solver.assign())
    {
        solver.update();
        for (size_t j = 0; j < cluster_count; ++j)
        {
            result.push_back(solver.mean(j));
        }
        ++ i;
    }
    return result;
}

int main(int argc, char* argv[])
{
    const Options options = parse_arguments(argc, argv);

    if (options.error_message.size() > 0)
    {
        std::cout << options.error_message 
                  << std::endl << std::endl
                  << "Run with --help to view usage instructions."
                  << std::endl << std::endl;
        return 1;
    }
    if (options.show_help) 
    { 
        display_help(); 
        return 0; 
    }

    std::vector<Vector2f> observations;
    if (!load_csv(options.input_path, observations))
    {
        std::cout << "Error reading path: " + options.input_path 
                  << std::endl << std::endl;
        return 1;
    }
    
    std::vector<Vector2f> initial_means(options.cluster_count);
    if (options.seeder_method == Options::SeederMethod::Forgy)
    {
        seeder::forgy<float, 2>
        (
            options.cluster_count,
            observations.begin(), observations.end(),
            initial_means.begin()
        );
    }
    else  // (options.seeder_method == Options::SeederMethod::Random_Partition)
    {
        seeder::random_partition<float, 2>
        (
            options.cluster_count,
            observations.begin(), observations.end(),
            initial_means.begin()
        );
    }

    std::vector<Vector2f> result;
    if (options.distance_method == Options::DistanceMethod::Euclidean)
    {
        result = run_and_record<float, 2, distance::euclidean2<float, 2>>
        (
            options.cluster_count, 
            observations, initial_means, 
            options.max_iterations
        );
    }
    else  // options.distance_method == Options::DistanceMethod::Manhattan
    {
        result = run_and_record<float, 2, distance::manhattan<float, 2>>
        (
            options.cluster_count, 
            observations, initial_means, 
            options.max_iterations
        );
    }

    if (!write_csv(options.output_path, result))
    {
        std::cout << "Error writing path: " + options.output_path 
                  << std::endl << std::endl;
        return 1;
    }
    else { return 0; }
}
