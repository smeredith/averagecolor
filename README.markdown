#AverageColor

Windows console app to find the average color of a .jpg.

Demonstrates how to use Microsoft's Parallel Patterns Library for parallel processing. Also demonstrates how to use WIC to decompress images.

##Performance
There is a perf test project that times the different implementations of the algorithm.

##Tests
The tests are divided into two projects: one for unit tests that are fast and don't use the file system, and one for functional tests that use real files as input.
