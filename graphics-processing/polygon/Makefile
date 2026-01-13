MACOSX_FLAGS = -DMACOSX -framework OpenGL -framework GLUT
LINUX_FLAGS = -DLINUX -lglut -lGLU
OPT = $(MACOSX_FLAGS)
all: libpolygon.so bspt tetra simple complex
libpolygon.so: polygon.c polygon.h
	cc polygon.c -o libpolygon.so -lm -shared -Wall -fPIC $(OPT)
simple: simple.c
	cc simple.c -o simple -lpolygon -L.
complex: complex.c
	cc complex.c -o complex -lpolygon -L.
bspt: bspt.c
	cc bspt.c -o bspt -lpolygon -L.
tetra: tetra.c
	cc tetra.c -o tetra -lpolygon -L.
.PHONY: clean dist
clean:
	-rm -f libpolygon.so bspt tetra sample # Added -f for robust removal
dist: clean
	( cd ..; tar zcvf polygon.tgz polygon/ )