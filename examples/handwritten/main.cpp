#include "MNISTReader.h"
#include "NeuralNetwork.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void print_result(vector<double> resultVals){
    double max = 0.0;
    int  i_max = 0;

    for (int i = 0; i < resultVals.size(); ++i){
        if (resultVals[i] > max){
            max = resultVals[i];
            i_max = i;
        }
    }

    cout << "Result: "<< i_max << endl;
}

vector<double> to_bw(image_t image){
    vector<double> pixels_double;
    
    for (int i = 0; i < 784; ++i){
        if (((unsigned int)(image.pixels[i] << 24) >> 24) < 128){
            pixels_double.push_back(0.0);
        }
        else {
            pixels_double.push_back(1.0);
        }
    }

    return pixels_double;
}

vector<double> to_onehot(char val){
    vector<double> result(10, 0);
    
    result[(int)val] = 1.0;

    return result;
}

bool test_error(vector<double> result, char target){
    double  max = 0.0;
    int     i_result;

    for (int i = 0; i < result.size(); ++i){
        if (result[i] > max){
            max = result[i];
            i_result = i;
        }
    }

    if (i_result != (int)target){
        return true;
    }

    return false;
}

int main(int argc, char const **argv){

    vector<unsigned> topology;
    
    //Train Variables
    trainData_t trainData;
    vector<double> input_pixels;
    vector<double> targetVal;

    //Test Variables
    testData_t testData;
    vector<double> input_pixels_test;
    vector<double> resultVals;

    //Error
    double error_r  = 0.0;
    int    nb_error = 0;

    //Network
    topology.push_back(784);
    topology.push_back(60);
    topology.push_back(10);

    NeuralNetwork net(topology);

    //Data Set
    //MNISTReader reader("./data_set/train-images-idx3-ubyte", "./data_set/train-labels-idx1-ubyte", "./data_set/t10k-images-idx3-ubyte", "./data_set/t10k-lables-idx1-ubyte");
    MNISTReader reader(argv[1], argv[2], argv[3], argv[4]);
    reader.loadTrain();
    trainData = reader.getTrainData();

    reader.loadTest();
    testData = reader.getTestData();

    //Training
    for (int i = 0; i < trainData.item_number; ++i){
        input_pixels = to_bw(trainData.images[i]);
        targetVal    = to_onehot(trainData.values[i]);

        net.feedForward(input_pixels);
        net.backProp(targetVal);
    }

    //Test
    for (int i = 0; i < testData.item_number; ++i){
        input_pixels_test = to_bw(testData.images[i]);
        net.feedForward(input_pixels_test);
        net.getResults(resultVals);

        if(test_error(resultVals, testData.values[i])){
            nb_error ++;
        }
    }

    error_r = ((double)nb_error/testData.item_number)*100;
    cout << "Error Rate: " << error_r << "%" <<endl;

    cout << "Visual Test" << endl;
    input_pixels_test = to_bw(testData.images[0]);
    net.feedForward(input_pixels_test);
    net.getResults(resultVals);

    print_result(resultVals);
    test_error(resultVals, testData.values[0]);

    const cv::Mat img(cv::Size(28, 28), CV_8U, testData.images[0].pixels);
    cv::namedWindow("Handwritten");
    cv::imshow("Handwritten", img);
    cv::waitKey(0);


    return 0;
}