CC = gcc
FLAGS = -W -O2 -g
INCLUDES = -lm
OBJS = main.o matrix.o dct.o 
.PHONY: all clean

all: $(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -o exe_bin
  
%.o: %.c
	$(CC) $(FLAGS) -c $*.c $(INCLUDES)
  
clean:
	-rm -rf *.o
	-rm exe_bin



