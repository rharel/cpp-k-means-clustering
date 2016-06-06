"""
@author Raoul Harel
@url github.com/rharel/cpp-k-means-clustering

Visual demonstration of the k-means library
found under ../core/

@details
    This script performs the following tasks:
        1. Generates random observations and writes them to a .csv
        2. Runs the k-means-demo executable on the observation file.
        3. Converts the output of the demo executable into svg images stores
           them under visuals/
"""


from random import gauss
import subprocess

import matplotlib.pyplot as plot


PATH_EXECUTABLE = '../bin/kmeans-demo.exe'
PATH_OBSERVATIONS = '../data/demo_observations.csv'
PATH_MEANS = '../data/demo_means.csv'

IMAGE_DIRECTORY = './visuals/'
IMAGE_NAME = 'demo'
IMAGE_EXTENSION = '.png'
IMAGE_SIZE_SMALL = 300
IMAGE_SIZE_LARGE = 800

OBSERVATION_DISTRIBUTIONS = [  # drawn from a gaussian

    ((0, 0), (10, 10), 300),  # [<mu>, <sigma>, <# of samples>]
    ((-20, 20), (5, 5), 100),
    ((20, 20), (5, 5), 100)
]
CLUSTER_COUNT = 3

STYLE_OBSERVATION = {'radius': 50, 'color': 'black'}
STYLE_MEAN = {

    'radius': 200,
    'assigned_color': ['#BB0000', '#00BB00', '#0000BB'],
    'self_color': ['#FF0000', '#00FF00', 'cyan']
}


def read_csv(path):
    """Reads 2D points from a .csv file."""
    points = []
    try:
        with open(path, 'r') as file:
            for line in file:
                line = line.strip().split(',')
                if len(line) is 2:
                    points.append(tuple(float(token) for token in line))
    except IOError:
        print("Could not open file for reading: %s" % path)
    return points


def write_csv(points, path):
    """Writes 2D points to a .csv file."""
    try:
        with open(path, 'w') as file:
            for point in points:
                file.write("%f, %f\n" % point)
    except IOError:
        print("Could not open file for writing: %s" % path)


def generate_observations(gaussians):
    """Generates observation data from a list of gaussian distributions."""
    observations = []
    for mu, sigma, n in gaussians:
        observations += [(gauss(mu[0], sigma[0]), gauss(mu[1], sigma[1])) for _ in range(n)]
    return observations


def run_kmeans(path_executable, cluster_count, path_input, path_output):
    """Runs the kmean executable on generated data."""
    subprocess.call(

        "%s %d %s %s" %
        (path_executable,
         cluster_count, path_input, path_output)
    )


def visualize(observations, means):
    figures = [visualize_observations(observations)]
    mean_iterations = [means[x:x + CLUSTER_COUNT] for x in range(0, len(means), CLUSTER_COUNT)]
    for iteration in mean_iterations:
        figures.append(visualize_clusters(observations, iteration))
    return figures


def visualize_observations(points):
    """Plots observation data."""
    x = tuple(p[0] for p in points)
    y = tuple(p[1] for p in points)

    figure = plot.figure()
    plot.scatter(

        x, y,
        STYLE_OBSERVATION['radius'],
        STYLE_OBSERVATION['color']
    )
    plot.axis('off')

    return figure


def visualize_clusters(observations, means):
    x = [p[0] for p in observations]
    y = [p[1] for p in observations]
    x += [p[0] for p in means]
    y += [p[1] for p in means]

    radius = [STYLE_OBSERVATION['radius'] for _ in range(len(observations))]
    radius += [STYLE_MEAN['radius'] for _ in range(len(means))]

    color = []
    for p in observations:
        distances = [

            (p[0] - q[0])**2 + (p[1] - q[1])**2 for q in means
        ]
        _, cluster_i = min((value, i) for (i, value) in enumerate(distances))
        color_i = cluster_i % len(STYLE_MEAN['assigned_color'])
        color.append(STYLE_MEAN['assigned_color'][color_i])
    color += [STYLE_MEAN['self_color'][i] for i in range(len(means))]

    figure = plot.figure()
    plot.scatter(x, y, radius, color)
    plot.axis('off')

    return figure


def save_images(figures, directory, name, extension):
    for figure in figures:
        plot.figure(figure.number)
        plot.savefig(directory + name + '_small' + str(figure.number) + extension,
                     dpi=IMAGE_SIZE_SMALL / max(figure.get_size_inches()))
        plot.savefig(directory + name + '_large' + str(figure.number) + extension,
                     dpi=IMAGE_SIZE_LARGE / max(figure.get_size_inches()))


if __name__ == '__main__':

    print("Generating observations...")
    observations = generate_observations(OBSERVATION_DISTRIBUTIONS)

    print("Saving to CSV...")
    write_csv(observations, PATH_OBSERVATIONS)

    print("Running kmeans...")
    run_kmeans(

        PATH_EXECUTABLE,
        CLUSTER_COUNT, PATH_OBSERVATIONS, PATH_MEANS
    )

    print("Reading output...")
    means = read_csv(PATH_MEANS)

    print("Plotting data...")
    figures = visualize(observations, means)

    print("Saving as SVG...")
    save_images(figures, IMAGE_DIRECTORY, IMAGE_NAME, IMAGE_EXTENSION)

    print("Done! See %s for images." % IMAGE_DIRECTORY)
