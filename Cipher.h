#include <string>

#pragma once

class Cipher {
    private:
    std::string delimiter = "~"; //a character that marks the beginning or end of a unit of data
    int responseType;
    std::string item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14, item15, item16, item17, item18, item19, item20, item21, item22; // declare the variables that are being used to store the message from the client - some use item1
    std::string itemS1, itemS2, itemS3, itemS4, itemS5, itemS6, itemS7, itemS8, itemS9, itemS10, itemS11, itemS12, itemS13, itemS14, itemS15, itemS16, itemS17, itemS18, itemS19, itemS20, itemS21; //these variables are for the use of decipherS so that the cipher and decipher variables do not get mixed up with it.

    public:
    
    std::string decipher(char messageFromClient[]);//this function is intended to pull out the delimiters from a message and the data associated with each request
    std::string decipherS(std::string messageFromClient);//this function is intended to pull out the delimiters from a message and the data associated with each request - string version

    std::string cipher(std::string typeOfRequest, std::string username= "", std::string item3= "", std::string item4= "", std::string item5= "", std::string item6= "", std::string item7= "", std::string item8= "", std::string item9= "", std::string item10= "", std::string item11= "", std::string item12= "");// the default values have been set to "" in case no input is given

    //return for the private variables:
    std::string getDelimiter() { return delimiter; }
    int getResponseType() { return responseType; }
    std::string getItem(int itemNumberToReturn);
    std::string getItemS(int itemNumberToReturn);
};
