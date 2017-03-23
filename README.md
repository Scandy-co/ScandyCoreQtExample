# ScandyCoreQtExample
This repo is for demonstrating how to use Qt with [Scandy Core](https://scandy.co/scandycore)

# Setup

## Step 1: C++ compiler

* OSX: install Xcode (sorry there's handy one-liner here...)
* Ubuntu: `sudo apt-get install build-essential`

## Step 2: CMake

* OSX: `brew install cmake`
* Ubuntu: `sudo apt-get install cmake`

## Step 3: Qt

* Qt 5
  * OSX: `brew install qt`
  * Ubuntu: `sudo apt-get install qt5-default`

## Step 4: Scandy Core SDK

You should install your copy of the Scandy Core SDK into `dependencies/ScandyCore`

# Building

```bash
mkdir -p build
cd build
cmake ../
make
```

# Running

**NOTE:**
OSX you will need to update your `DYLD_LIBRARY_PATH` path:

```bash
export DYLD_LIBRARY_PATH=$PWD/../dependencies/ScandyCore/lib/
```
*from the `build` dir*

Then on OSX or Linux:

```bash
./ScandyCoreQtExample
```
*from the `build` dir*