#include <string>

#pragma once

class Cipher {
    public:
    std::string delimiter = "~"; //a character that marks the beginning or end of a unit of data
    int responseType;
    std::string item2, item3, item4, item5, item6, item7, item1; // declare the variables that are being used to store the message from the client - some use item1

    std::string decipher(char messageFromClient[]);//this function is intended to pull out the delimiters from a message and the data associated with each request
    std::string decipherS(std::string messageFromClient);//this function is intended to pull out the delimiters from a message and the data associated with each request - string version

    std::string cipher(std::string typeOfRequest, std::string username= "", std::string item3= "", std::string item4= "", std::string item5= "", std::string item6= "", std::string item7= "");// the default values have been set to "" in case no input is given
};
