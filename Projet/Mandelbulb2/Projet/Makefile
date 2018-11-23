# Makefile pour compiler le raytracer de mandelbulb
# Plusieurs options en commentaires pour aider a compiler pour divers parallelismes
CC = g++
LIBS = -lm
# Pour compiler avec MPI sous Linux
# CC = mpic++
# Pour compiler avec Microsoft MPI sous Windows
#CC = g++ -I/c/Program\ Files\ \(x86\)/Microsoft\ SDKs/MPI/Include
#LIBS = -L/c/Program\ Files\ \(x86\)/Microsoft\ SDKs/MPI/Lib/x64 -lmsmpi -lm
# Pour développer sur GPU ( NVIDIA CUDA )
CUDAROOT = /c/Program\ Files/NVIDIA\ GPU\ Computing\ Toolkit/CUDA/v9.1
NVCC = $(CUDAROOT)/bin/nvcc
CUDAOPTS = --generate-code arch=compute_35,code=sm_35 --generate-code arch=compute_60,arch=sm_60
# Pour code de développement déboguable
#CXXOPTS = -Wall -DDEBUG -pedantic -g -Weffc++ -O0 -std=c++14
# Pour code de production
CXXOPTS = -O3 -march=native -fopenmp -std=c++14

.cpp.o:
	$(CC) $(CXXOPTS) -c $< -o $@
.cu.o:
	$(NVCC) -c $< -o $@

OBJS = camera.o vector3d.o scene.o mandelbulb.o runner.o

runner.exe: $(OBJS)
	$(CC) $(CXXOPTS) -o $@ $(OBJS) $(LIBS)

clean:
	@rm -f *.o *~ *.exe
