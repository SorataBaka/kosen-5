all:	libimg.so libvect.so raycast

libimg.so:	img.c img.h
	cc img.c -o libimg.so -shared -Wall -fPIC

libvect.so:	vect.c vect.h
	cc vect.c -lm -o libvect.so -shared -Wall -fPIC

raycast:	raycast.c
	cc raycast.c -o raycast -lm -limg -lvect -L. -Wall

.PHONY: all clean dist

clean:
	-rm libimg.so libvect.so raycast

dist:	clean
	( cd ..; tar zcvf raycast.tgz raycast/ )

