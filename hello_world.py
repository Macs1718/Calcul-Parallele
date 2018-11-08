from mpi4py import MPI

print("Hello world from {:04d} in {}".format(MPI.COMM_WORLD.rank,
                                         MPI.COMM_WORLD.size))
