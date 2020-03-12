#include <iostream>
#include <fstream>
using namespace std;


void generateXOR(int count){

    ofstream myfile;
    myfile.open ("xor.txt");

    for (int i = 0; i < count; ++i){
        int input_a=rand()%2;
        int input_b=rand()%2;
        int output = input_a ^ input_b;

        myfile << input_a << " " << input_b << " " << output << "\n"; 

    }

    myfile.close();


}


int main(int argc, char const *argv[])
{
    generateXOR(200000);
    return 0;
}