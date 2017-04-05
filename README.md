# ScandyCoreQtExample
This repo is for demonstrating how to use Qt with [Scandy Core](https://scandy.co/scandycore)

# Setup

## Step 1: C++ compiler

* OS X: install Xcode (sorry there's no handy one-liner here...)
* Ubuntu: `sudo apt-get install build-essential`

## Step 2: CMake

* OS X: `brew install cmake`
* Ubuntu: `sudo apt-get install cmake`

## Step 3: Qt

* Qt 5
  * OS X: `brew install qt`
  * Ubuntu: `sudo apt-get install qt5-default`

## Step 4: Scandy Core SDK

You should install your copy of the Scandy Core SDK into
`dependencies/ScandyCore`. See `dependencies/README.md` for more information.
For example, if you've downloaded the ScandyCore package for macOS, do this:
```
pushd dependencies/
mv ~/Downloads/ScandyCore-0.0.3+1690.1bec63f-Darwin.zip ./
unzip ScandyCore-0.0.3+1690.1bec63f-Darwin.zip
ln -s ScandyCore-0.0.3+1690.1bec63f-Darwin ScandyCore
popd
```

# Building

```bash
mkdir -p build
cd build
cmake ../
make
```

# Running

**NOTE:**
OS X you will need to update your `DYLD_LIBRARY_PATH` path:

```bash
export DYLD_LIBRARY_PATH=$PWD/../dependencies/ScandyCore/lib/
```
*from the `build` dir*

Then on OS X or Linux:

```bash
./ScandyCoreQtExample
```
*from the `build` dir*
