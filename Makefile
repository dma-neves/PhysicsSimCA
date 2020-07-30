INC_DIRECOTRY=-I src -I src/sim
LIBS=-lcsfml-graphics -lcsfml-window -lcsfml-system

CC=gcc -std=c11

OBJECT_FILES=obj/main.o obj/PhysicsSim.o

sim.out: $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -o sim.out $(LIBS)

obj/main.o: src/main.c
	$(CC) -c src/main.c $(INC_DIRECOTRY) -o obj/main.o

obj/PhysicsSim.o: src/sim/PhysicsSim.h src/sim/PhysicsSim.c
	$(CC) -c src/sim/PhysicsSim.c $(INC_DIRECOTRY) -o obj/PhysicsSim.o

clean:
	rm obj/*.o sim.out

