CC = gcc
CFLAGS = -Wall -g
SOURCES = Source/compress.c Source/hash.c Source/huff_tree.c Source/pq.c
HEADERS = Headers/compress.h Headers/hash.h Headers/huff_tree.h Headers/pq.h

compile: main.c
	${CC} ${CFLAGS} ${SOURCES} ${HEADERS} -o main main.c

clean:
	rm main.exe