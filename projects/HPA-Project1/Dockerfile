# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:8.1.0

RUN mkdir -p /project

WORKDIR /project

COPY ./TeraSort.cpp /project

RUN g++ -fopenmp -O3 -o prog TeraSort.cpp

RUN rm ./TeraSort.cpp

ENV PATH="/project:${PATH}"