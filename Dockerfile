# syntax=docker/dockerfile:1.4

# Stage 1: Build the project
FROM sillyfreak/wombat-cross:latest AS builder
LABEL Description="Build environment"

USER root
ENV DEBIAN_FRONTEND=noninteractive \
    TZ=America/New_York

SHELL ["/bin/bash", "-c"]

# Install CMake and Ninja
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /root/build
COPY . .

# Build CMake Project
RUN cmake -S . -B build && \
    cmake --build build

# Create an output directory for the executable
RUN mkdir -p /root/output && \
    cp build/botball_user_program /root/output/
