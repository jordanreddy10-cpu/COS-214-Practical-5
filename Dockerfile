# Use a standard Ubuntu base image
FROM ubuntu:22.04

# Prevent interactive prompts during apt installations
ENV DEBIAN_FRONTEND=noninteractive

# Install g++, make, valgrind, and gdb for memory checking and debugging
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    valgrind \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy all files from the host to the container's working directory
COPY . .

# Build the application using the provided Makefile
RUN make

# By default, run the compiled application
CMD ["make", "run"]