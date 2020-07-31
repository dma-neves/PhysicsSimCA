INC_DIRECOTRY=-I src -I src/sim
LIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system

CC=gcc -std=c11 -g

OBJECT_FILES=obj/main.o obj/PhysicsSim.o obj/ParticleSimulator.o obj/ParticleRenderer.o

sim.out: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -o sim.out $(LIBS)

obj/main.o: src/main.c
	$(CC) -c src/main.c $(INC_DIRECOTRY) -o obj/main.o

obj/PhysicsSim.o: src/sim/PhysicsSim.h src/sim/PhysicsSim.c
	$(CC) -c src/sim/PhysicsSim.c $(INC_DIRECOTRY) -o obj/PhysicsSim.o

obj/ParticleSimulator.o: src/sim/ParticleSimulator.h src/sim/ParticleSimulator.c
	$(CC) -c src/sim/ParticleSimulator.c $(INC_DIRECOTRY) -o obj/ParticleSimulator.o

obj/ParticleRenderer.o: src/sim/ParticleRenderer.h src/sim/ParticleRenderer.c
	$(CC) -c src/sim/ParticleRenderer.c $(INC_DIRECOTRY) -o obj/ParticleRenderer.o

clean:
	rm obj/*.o sim.out

