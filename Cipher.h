#include <string>

#pragma once

using namespace std;

class Cipher {
    public:
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data
    int responseType;
    string item2, item3, item4, item5, item6, item7; // declare the variables that are being used to store the message from the client

    string decipher(char messageFromClient[]);//this function is intended to pull out the delimiters from a message and the data associated with each request

    string cipher(string typeOfRequest, string username= "", string item3= "", string item4= "", string item5= "", string item6= "", string item7= "");// the default values have been set to "" in case no input is given
};
