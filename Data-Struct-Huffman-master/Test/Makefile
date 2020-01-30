CFLAGS = -w -g
TREE = Headers/huff_tree.h Source/huff_tree.c
MAIN = main.c
P_QUEUE = Source/pq.c Headers/pq.h
HASH = Source/hash.c Headers/hash.h
COMPRESS = Source/compress.c Headers/compress.h
DESCOMPRESS = Source/descompress.c Headers/descompress.h
TEST = CUnit.c

compile:
	gcc $(CFLAGS) $(P_QUEUE)	$(HASH)	$(TREE)	$(MAIN)	$(COMPRESS)	$(DESCOMPRESS) -o	main

test:
		gcc $(CFLAGS) $(P_QUEUE)	$(HASH)	$(TREE)	$(COMPRESS)	$(DESCOMPRESS) $(TEST) -o	test -lcunit
