# Darkflame Event Broker
A simple message broker that would allow objects to subscribe to message events based on a message type

### Dependencies
* [Google Test](https://github.com/google/googletest)

### Build
To build the project, you will need [Conan Package Manager](https://conan.io/).

First, download the code and unzip it somewhere. Next run `conan install .` to download and install Conan packages (just gtest for the time being.)

After that, build the project with

```
cmake .
make
```

Binaries will be stored in **./bin**.

### License
This project is licensed under the MIT License. Feel free to copy the code, modify it, and use it both commercially and non-commercially however you want.

The only requirement is that the code be attributed to me, and that I cannot be held liable for anything you do with it.