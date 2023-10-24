# mpi_hash_cracker

Efficiency-wise this is nothing to write home about, but it was fun to make.

The main idea to this is converting from decimal numbers to base k numbers (where k is the length of the character set that we're using) so that we can arbitrarily "skip forward" different combinations of numbers. This makes it very easy to parallelize hashing combinations of characters across an arbitrary number of MPI slots/cores. Obviously this does not have the optimizations that something like hashcat does, but you can throw as many nodes at this as you can get your hands on. Networking won't be a bottleneck because each instance doesn't even need to communicate with other instances.
