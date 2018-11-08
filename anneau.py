from mpi4py import MPI

s = "a"

rang = MPI.COMM_WORLD.rank
nbp  = MPI.COMM_WORLD.size

if rang == 0:
    MPI.COMM_WORLD.send(s, dest=rang+1)
    s = MPI.COMM_WORLD.recv(source=nbp-1)
else:
    s = MPI.COMM_WORLD.recv(source=rang-1)
    s2 = s+"a"
    MPI.COMM_WORLD.send(s2, dest=(rang+1)%nbp)

print("{} : a pour token {}".format(rang,s))
