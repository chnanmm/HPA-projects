FROM gcc:8.1.0

RUN mkdir -p /project

WORKDIR /project

COPY ./PowerGrid.cpp /project

RUN g++ -fopenmp -O3 -o prog PowerGrid.cpp

RUN rm ./PowerGrid.cpp

ENV PATH="/project:${PATH}"