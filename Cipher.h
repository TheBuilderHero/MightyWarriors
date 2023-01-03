#include <string>
#include <vector>

#pragma once

class Cipher {
    private:
    std::string delimiterLayer1 = "~"; //a character that marks the beginning or end of a unit of data
    std::string delimiterLayer2 = "="; //a character that marks the beginning or end of a unit of data
    std::string delimiterLayer3 = "|";
    std::string delimiterLayer4 = "+";
    int responseType;
    std::string item[22];//item2, item3, item4, item5, item6, item7, item8, item9, item10, item11, item12, item13, item14, item15, item16, item17, item18, item19, item20, item21, item22; // declare the variables that are being used to store the message from the client - some use item1
    std::string subItem[22][22];
    std::string itemS1, itemS2, itemS3, itemS4, itemS5, itemS6, itemS7, itemS8, itemS9, itemS10, itemS11, itemS12, itemS13, itemS14, itemS15, itemS16, itemS17, itemS18, itemS19, itemS20, itemS21, itemS22; //these variables are for the use of decipherS so that the cipher and decipher variables do not get mixed up with it.
    std::vector<std::string> recivedMessage;
    std::vector<std::string> MESSAGE;

    public:
    enum SEND_TYPE { VECTOR_SEND };
    enum DATA_TYPE { DIALOGUE_INFO, STAT_INFO, ENEMY_INFO };
    //enumeration convertion:
    enum SEND_TYPE convertToSEND_TYPE(std::string &input){
        //if these are changed we need to then update them on the server side:
        if(input == "7"){
            return VECTOR_SEND;
        }
    }
    enum DATA_TYPE convertToDATA_TYPE(std::string &input){
        //if these are changed we need to then update them on the server side:
        if (input == "dialogue") return DIALOGUE_INFO;
        if (input == "stats") return STAT_INFO;
        if (input == "enemyinfo") return ENEMY_INFO;
        return DIALOGUE_INFO;
    }
    //enumeration convertion:
    std::string convertSEND_TYPEToString(const enum SEND_TYPE &input){
        //if these are changed we need to then update them on the client side:
        switch(input){
            case 0: return "7";
            default: return "7"; 
        }
    }
    std::string convertDATA_TYPEToString(const enum DATA_TYPE &input){
        //if these are changed we need to then update them on the client side:
        switch(input){
            case 0: return "dialogue"; 
            case 1: return "stats"; 
            case 2: return "enemyinfo";
            default: return ""; 
        }
    }

    
    std::string decipher(char messageFromClient[], bool hasSubItems = false);//this function is intended to pull out the delimiters from a message and the data associated with each request
    std::string decipher(std::string messageFromClient, bool hasSubItems = false);//this function is intended to pull out the delimiters from a message and the data associated with each request - string version.
    std::string subDecipher(std::string subMessageFromClient, int rootItem);//this function is intended to pull out the subDelimiters from a message and the data
    std::string decipherS(std::string messageFromClient);//this function is intended to pull out the delimiters from a message and the data associated with each request - string version

    std::string cipher(std::string typeOfRequest, std::string username= "", std::string item3= "", std::string item4= "", std::string item5= "", std::string item6= "", std::string item7= "", std::string item8= "", std::string item9= "", std::string item10= "", std::string item11= "", std::string item12= "", std::string item13= "", std::string item14= "", std::string item15= "", std::string item16= "", std::string item17= "", std::string item18= "", std::string item19= "", std::string item20= "", std::string item21= "", std::string item22= "");// the default values have been set to "" in case no input is given

    std::string subCipher(std::string item1= "", std::string item2= "", std::string item3= "", std::string item4= "", std::string item5= "", std::string item6= "", std::string item7= "", std::string item8= "", std::string item9= "", std::string item10= "", std::string item11= "", std::string item12= "", std::string item13= "", std::string item14= "", std::string item15= "", std::string item16= "", std::string item17= "", std::string item18= "", std::string item19= "", std::string item20= "", std::string item21= "", std::string item22= "");// the default values have been set to "" in case no input is given

    //return for the private variables:
    std::string getDelimiterLayer1() { return delimiterLayer1; }
    std::string getDelimiterLayer2() { return delimiterLayer2; }
    std::string getDelimiterLayer3() { return delimiterLayer3; }
    std::string getDelimiterLayer4() { return delimiterLayer4; }
    int getResponseType() { return responseType; }
    std::string getItem(int itemNumberToReturn, int subItemNumber = 0); //default is 0 meaning that it is not considered to have subItems
    std::string getItemS(int itemNumberToReturn);

    //vector sending and reciving:
    //std::vector<std::string>* decipherVector(std::string* message);

};
