# Name of the project
PROJ_NAME?=neural_network

# Application File
APP_FILE?=./examples/xor/xor.cpp 

# .c files
C_SOURCE=$(wildcard ./src/*.cpp)
 
# .h files
H_SOURCE=$(wildcard ./include/*.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)

# Compiler
CPP=g++

# Lib Directory
LIB_DIR="./include/"

# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -fopenmp   \


all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
ifneq ("$(wildcard $(dir $(APP_FILE))/Makefile)","")
	cd $(dir $(APP_FILE)) && make PROJ_NAME=$(PROJ_NAME)
	mv $(dir $(APP_FILE))/$(PROJ_NAME) .
else
	$(CPP) -o $@ $^ $(APP_FILE) -I $(LIB_DIR)
endif


%.o: %.c %.h
	$(CPP) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CPP) -o $@ $< $(CC_FLAGS)


clean:
	rm -rf *.o $(PROJ_NAME) *~