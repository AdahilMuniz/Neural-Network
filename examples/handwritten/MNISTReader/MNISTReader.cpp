//@TODO: Verify whether the number of images and size are the same.

#include "MNISTReader.h"

MNISTReader::MNISTReader(const string &_train_img_path, const string &_train_label_path, const string &_test_img_path, const string &_test_label_path){
//MNISTReader::MNISTReader(){
    
    train_img_path   = _train_img_path;
    train_label_path = _train_label_path;
    test_img_path    = _test_img_path;
    test_label_path  = _test_label_path;
}

MNISTReader::~MNISTReader(){
    //
}

int MNISTReader::parser_int(const char* value){
  return ((value[0] & 0xff) << 24) | ((value[1] & 0xff) << 16) |
         ((value[2] & 0xff) <<  8) | ((value[3] & 0xff) <<  0);
}

int MNISTReader::loadTrain(){
    //Open Training Image File
    ifstream rfti(train_img_path, ios::out | ios::binary);

    if(!rfti) {
      cout << "Cannot open Tainning Image File!" << endl;
      return -1;
   }

   //Image Magic Number
   rfti.read((char *) &trainData.img_magic_number, sizeof(unsigned int));
   trainData.img_magic_number = parser_int((char *) &trainData.img_magic_number);
   assert(trainData.img_magic_number == 0x803);
   //cout << "Magic Number: " << trainData.img_magic_number << endl; 

   //Images Number
   rfti.read((char *) &trainData.item_number, sizeof(unsigned int));
   trainData.item_number = parser_int((char *) &trainData.item_number);

   //Allocate Image vector
   trainData.images = new (nothrow) image_t [trainData.item_number];
   //trainData.values = new (nothrow) char [trainData.item_number];
   if (trainData.images == nullptr){
        cout << "Cannot allocate images!" << endl;
        return -1;
   }

    //Row and Column size
    rfti.read((char *) &trainData.rn, sizeof(unsigned int));
    trainData.rn = parser_int((char *) &trainData.rn);
    rfti.read((char *) &trainData.cn, sizeof(unsigned int));
    trainData.rn = parser_int((char *) &trainData.rn);

    for (int i = 0; i < trainData.item_number; ++i){
        rfti.read((char *) &trainData.images[i], sizeof(image_t));
    }
    rfti.close();

   
   //Open Training Label File
    ifstream rftl(train_label_path, ios::out | ios::binary);

    if(!rftl) {
      cout << "Cannot open Tainning Label File!" << endl;
      return -1;
   }

   //Labels Magic Number
   rftl.read((char *) &trainData.label_magic_number, sizeof(unsigned int));
   trainData.label_magic_number = parser_int((char *) &trainData.label_magic_number);
   assert(trainData.label_magic_number == 0x801);

   //Itens Number
   rftl.read((char *) &trainData.item_number, sizeof(unsigned int));
   trainData.item_number = parser_int((char *) &trainData.item_number);

   //Allocate Label vector
   trainData.values = new (nothrow) char [trainData.item_number];
   if (trainData.values == nullptr){
        cout << "Cannot allocate labels!" << endl;
        return -1;
   }

   for (int i = 0; i < trainData.item_number; ++i){
        rftl.read((char *) &trainData.values[i], sizeof(char));
    }
    rftl.close();

}

int MNISTReader::loadTest(){
    //Open Test Image File
    ifstream rfti(test_img_path, ios::out | ios::binary);

    if(!rfti) {
      cout << "Cannot open Tainning Image File!" << endl;
      return -1;
   }

   //Image Magic Number
   rfti.read((char *) &testData.img_magic_number, sizeof(unsigned int));
   testData.img_magic_number = parser_int((char *) &testData.img_magic_number);
   assert(testData.img_magic_number == 0x803);
   //cout << "Magic Number: " << testData.img_magic_number << endl; 

   //Images Number
   rfti.read((char *) &testData.item_number, sizeof(unsigned int));
   testData.item_number = parser_int((char *) &testData.item_number);

   //Allocate Image vector
   testData.images = new (nothrow) image_t [testData.item_number];
   //testData.values = new (nothrow) char [testData.item_number];
   if (testData.images == nullptr){
        cout << "Cannot allocate images!" << endl;
        return -1;
   }

    //Row and Column size
    rfti.read((char *) &testData.rn, sizeof(unsigned int));
    testData.rn = parser_int((char *) &testData.rn);
    rfti.read((char *) &testData.cn, sizeof(unsigned int));
    testData.rn = parser_int((char *) &testData.rn);

    for (int i = 0; i < testData.item_number; ++i){
        rfti.read((char *) &testData.images[i], sizeof(image_t));
    }
    rfti.close();

   
   //Open Training Label File
    ifstream rftl(test_label_path, ios::out | ios::binary);

    if(!rftl) {
      cout << "Cannot open Tainning Label File!" << endl;
      return -1;
   }

   //Labels Magic Number
   rftl.read((char *) &testData.label_magic_number, sizeof(unsigned int));
   testData.label_magic_number = parser_int((char *) &testData.label_magic_number);
   assert(testData.label_magic_number == 0x801);

   //Itens Number
   rftl.read((char *) &testData.item_number, sizeof(unsigned int));
   testData.item_number = parser_int((char *) &testData.item_number);

   //Allocate Label vector
   testData.values = new (nothrow) char [testData.item_number];
   if (testData.values == nullptr){
        cout << "Cannot allocate labels!" << endl;
        return -1;
   }

   for (int i = 0; i < testData.item_number; ++i){
        rftl.read((char *) &testData.values[i], sizeof(char));
    }
    rftl.close();

}