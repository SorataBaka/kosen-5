DIR = pcm
LIB = libpcm.so
APP = thru rate sin concat overlay

all:	$(LIB)	$(APP)

libpcm.so:	pcm.c	pcm.h
	cc $< -std=c99 -I. -lm -fpic -shared -o $@

thru:	thru.c	$(LIB)
	cc $< -std=c99 -I. -L. -lpcm -o $@

rate:	rate.c	$(LIB)
	cc $< -std=c99 -I. -L. -lpcm -lm -o $@

sin:	sin.c	$(LIB)
	cc $< -std=c99 -I. -L. -lpcm -lm -o $@

clean:
	-rm $(LIB) $(APP)

dist:	clean
	( cd ..; tar zcvf $(DIR).tgz $(DIR) )

concat:	concat.c libpcm.so
	cc $< -std=c99 -I. -L. -lpcm -lm -o $@

overlay:	overlay.c libpcm.so
	cc $< -std=c99 -I. -L. -lpcm -lm -o $@

