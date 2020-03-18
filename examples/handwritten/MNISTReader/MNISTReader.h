#pragma once

#include<iostream>
#include <new>
#include<fstream>
#include <assert.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

typedef struct image_t { char pixels[784]; } image_t;

typedef struct trainData_t{
    unsigned int img_magic_number;
    unsigned int label_magic_number;
    unsigned int rn, cn;
    unsigned int item_number;
    char * values;
    image_t * images;
} trainData_t;

typedef struct testData_t{
    unsigned int img_magic_number;
    unsigned int label_magic_number;
    unsigned int rn, cn;
    unsigned int item_number;
    char * values;
    image_t * images;
} testData_t;

class MNISTReader{
private:
    trainData_t trainData;
    testData_t  testData;

    string train_img_path, train_label_path, test_img_path, test_label_path;

public:
    MNISTReader(const string &_train_img_path, const string &_train_label_path, const string &_test_img_path, const string &_test_label_path);
    
    MNISTReader();
    ~MNISTReader();

    int loadTrain();
    int loadTest();
    int parser_int(const char* value);

    int getTrainSize() const { return trainData.item_number; }
    int getTestSize () const { return testData.item_number;  }

    trainData_t getTrainData() const { return trainData; }
    testData_t  getTestData () const { return testData;  }

};
