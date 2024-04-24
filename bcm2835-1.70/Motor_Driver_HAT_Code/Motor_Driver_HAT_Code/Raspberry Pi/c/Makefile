# _*_ MakeFile _*_

# General compilation variables
pigpioFlags=-lpigpio
flags=-lrt -lpthread -lm

all: test

test: test.c
	gcc -o $@ $^ $(pigpioFlags) $(flags)

clean:
	rm -f *.o test.c
