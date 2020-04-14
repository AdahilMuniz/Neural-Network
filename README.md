<h1>Neural Network</h1>

This repository contains a code for a Neural Network class designed to be an object of learning.

<h2>How to use</h2>

To compile a code which use the Neural Network library it's recommended the us of the Makefile script. It contains two (2) modifiable variables:

* $PROJ_NAME : Project Name
* $APP_FILE  : File path of your application (Including the name)

Therefore, to compile a code:

> make $PROJ_NAME=[Optional] $APP_FILE=[File Path]

If the Project name is not provided its name will be "neural_network"

<h2>Running an example</h2>

The example which we will run here is the "xor" one, an application responsible to emulate a xor logic port.

> make $PROJ_NAME=xor $APP_FILE=./examples/xor/xor.cpp
> ./xor ./examples/xor/xor.txt ./examples/xor/xor_test.txt 1000

To run this example we need to provide the training data input file path, the test input file path and the number of epochs as arguments.