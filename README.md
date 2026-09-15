# Dependencies:
```
sudo apt update
sudo apt install -y \
    build-essential \
    tar \
    zip \
    unzip \
    curl \
    cmake \
    ninja-build \
    git \
    pkg-config \
    gphoto2 \
    libgphoto2-dev
```

# Installation:
```
git clone --recursive https://github.com/Psaltria/sps-gravity-pi.git
cd sps-gravity-pi
cmake -S . -B build -G Ninja \ -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
