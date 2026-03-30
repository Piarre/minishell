FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    gdb \
    make \
    cmake \
    valgrind \
    clang \
    clang-format \
    libc6-dev \
    git \
    curl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["bash"]