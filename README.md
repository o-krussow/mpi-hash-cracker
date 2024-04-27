# mpi_hash_cracker

This is nowhere near as fast as something like hashcat, more a learning exercise than anything else.

The main idea to this is converting from decimal numbers to base k numbers (where k is the length of the character set that we're using) so that we can arbitrarily "skip forward" different combinations of numbers. This makes it very easy to parallelize hashing combinations of characters across an arbitrary number of MPI slots/cores, so we can use it with little to no consideration of node symmetry or performance. Network latency/bandwidth doesn't become a bottleneck because the instances do not communicate with each other, so in theory this should scale up very linearly.

## Build
Make sure that your mpi implementation is loaded:
```
$ module load openmpi
```
Now, make
```
$ make
```

## An example of running across 560 different cores
This doesn't use very much memory so you (could) adjust this.
```
$ salloc -n 560 --mem=0
```
Running mpi_hash_cracker within your allocation:
```
$ mpirun mpi_hash_cracker 5d41402abc4b2a76b9719d911017c592

...

Current guess:  
Current guess: z5 .
Current guess: 1Pa4
Current guess: ahAbV
Current guess: aIlcN
Current guess: a9;dF
Current guess: bp2ex
Current guess: bQMfp
Current guess: b'xgh
Current guess: cyih 
Current guess: cY<h.
Current guess: dfYi4
Current guess: dGJjV
Current guess: d8ukN
Current guess: eoflF
Current guess: eO,mx
Current guess: e?Vnp
Current guess: fwGoh
Current guess: fXrp 
Current guess: gecp.
Current guess: gE8q4
Current guess: g6SrV
n283 found string is hello
```

Across 560 (mixed) E5 2660 v1/v2 cores, I found that I was able to do ~180MH/sec (md5). Not too terrible.
