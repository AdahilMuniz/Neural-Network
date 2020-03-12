# Name of the project
PROJ_NAME?=neural_network

# Application File
APP_FILE?=./example/xor/xor.cpp 

# .c files
C_SOURCE=$(wildcard ./src/*.cpp)
 
# .h files
H_SOURCE=$(wildcard ./header/*.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)

# Compiler
CPP=g++

# Lib Directory
LIB_DIR="./header/"

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      


all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CPP) -o $@ $^ $(APP_FILE) -I $(LIB_DIR) 

%.o: %.c %.h
	$(CPP) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CPP) -o $@ $< $(CC_FLAGS)


clean:
	rm -rf *.o $(PROJ_NAME) *~