#!/bin/bash

#SBATCH --job-name=mpi_test
#SBATCH -o mpi_out%j.out
#SBATCH -N 15
#SBATCH --ntasks-per-node=16

echo -e '\n submitted Open MPI job'
echo 'hostname'
hostname

# load Open MPI module
module load mpi

# compile the C file
#mpicc crack.c -o crack
make

# run compiled test_mpi.c file
mpirun ./mpi_hash_cracker password
