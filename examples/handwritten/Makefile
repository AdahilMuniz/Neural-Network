# Name of the project
PROJ_NAME?=handwritten

# Application File
APP_FILE=main.cpp 

# .c files
C_SOURCE=$(wildcard ./MNISTReader/*.cpp ../../src/*.cpp)

# .h files
H_SOURCE=$(wildcard ./MNISTReader/*.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)

# Compiler
CPP=g++

# Lib Directory
LIB_DIR= -I./MNISTReader -I../../include

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \


all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CPP) -o $@ $^ 'main.cpp' $(LIB_DIR) `pkg-config opencv --cflags --libs`

%.o: %.c %.h
	$(CPP) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CPP) -o $@ $< $(CC_FLAGS)

download:
	mkdir -p './data_set'
	cd data_set && wget yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz && gunzip train-images-idx3-ubyte.gz
	cd data_set && wget yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz && gunzip train-labels-idx1-ubyte.gz
	cd data_set && wget yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz  && gunzip t10k-images-idx3-ubyte.gz
	cd data_set && wget yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz  && gunzip t10k-labels-idx1-ubyte.gz

clean:
	rm -rf *.o $(PROJ_NAME) *~