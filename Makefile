OBJS	= hash_main.o getWord.o crc64.o hash_structures.o 
SOURCE	= hash_main.c getWord.c crc64.c hash_structures.c
HEADER	= getWord.h crc64.h hash_structures.h
OUT	= wordpairs
CC	 = gcc
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

hash_main.o: hash_main.c
	$(CC) $(FLAGS) hash_main.c 

getWord.o: getWord.c
	$(CC) $(FLAGS) getWord.c 

hash_structures.o: hash_structures.c
	$(CC) $(FLAGS) hash_structures.c

crc64.o: crc64.c
	$(CC) $(FLAGS) crc64.c
clean:
	rm -f $(OBJS) $(OUT)
