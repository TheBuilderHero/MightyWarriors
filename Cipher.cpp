#include <string>

#include "Cipher.h"

using namespace std;


//this function is intended to pull out the delimiters from a message and the data associated with each request
string Cipher::decipher(char messageFromClient[]){
    
    //string message = messageFromClient; // change the message into a string

    
    // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    string s = messageFromClient;
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + delimiter.length());
        switch (loopPass){
            case 1://the first item enclosed in delimiters
            if (output.length() > 0) responseType = stoi(output); // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
            break;
            case 2://the second item enclosed in delimiters
            if (output.length() > 0) item2 = output; 
            break;
            case 3://the third item enclosed in delimiters
            if (output.length() > 0) item3 = output; 
            break;
            case 4://the forth item enclosed in delimiters
            if (output.length() > 0) item4 = output; 
            break;
            case 5://the fith item enclosed in delimiters
            if (output.length() > 0) item5 = output; 
            break;
            case 6://the sixth item enclosed in delimiters
            if (output.length() > 0) item6 = output; 
            break;
            case 7://the seventh item enclosed in delimiters
            if (output.length() > 0) item7 = output; 
            break; 
            case 8://the eighth item enclosed in delimiters
            if (output.length() > 0) item8 = output; 
            break;
            case 9://the ninth item enclosed in delimiters
            if (output.length() > 0) item9 = output; 
            break;
            case 10://the tenth item enclosed in delimiters
            if (output.length() > 0) item10 = output; 
            break;
            case 11://the eleventh item enclosed in delimiters
            if (output.length() > 0) item11 = output; 
            break;
            case 12://the twelth item enclosed in delimiters
            if (output.length() > 0) item12 = output; 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}

//this function is intended to pull out the delimiters from a message and the data associated with each request - string version
string Cipher::decipherS(string messageFromClient){
    
    //string message = messageFromClient; // change the message into a string

    
    // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    string s = messageFromClient;
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the delimiters to view the message
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + delimiter.length());
        switch (loopPass){
            case 1://the first item enclosed in delimiters
            if (output.length() > 0) itemS1 = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
            break;
            case 2://the second item enclosed in delimiters
            if (output.length() > 0) itemS2 = output; 
            break;
            case 3://the third item enclosed in delimiters
            if (output.length() > 0) itemS3 = output; 
            break;
            case 4://the forth item enclosed in delimiters
            if (output.length() > 0) itemS4 = output; 
            break;
            case 5://the fith item enclosed in delimiters
            if (output.length() > 0) itemS5 = output; 
            break;
            case 6://the sixth item enclosed in delimiters
            if (output.length() > 0) itemS6 = output; 
            break;
            case 7://the seventh item enclosed in delimiters
            if (output.length() > 0) itemS7 = output; 
            break;
            case 8://the eighth item enclosed in delimiters
            if (output.length() > 0) itemS8 = output; 
            break;
            case 9://the ninth item enclosed in delimiters
            if (output.length() > 0) itemS9 = output; 
            break;
            case 10://the tenth item enclosed in delimiters
            if (output.length() > 0) itemS10 = output; 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}

//this functions purpose it to add the delimiters to given items 
string Cipher::cipher(string typeOfRequest, string username, string item3, string item4, string item5, string item6, string item7, string item8, string item9, string item10, string item11, string item12){ // the default values have been set to "" in case no input is given
    int numberOfItems = 12; //max number of items that we can cipher
    string delimiter = "~"; //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start the loop at 1 so that there is no extra spaces
    while (loopPass <= numberOfItems) {
        str_file_content += delimiter; // this will add the seperating delimiter before the a given item
        switch (loopPass){
            case 1:
            if (typeOfRequest.length() > 0) str_file_content += typeOfRequest;
            break;
            case 2:
            if (username.length() > 0) str_file_content += username;
            break;
            case 3:
            if (item3.length() > 0) str_file_content += item3;
            break;
            case 4:
            if (item4.length() > 0) str_file_content += item4;
            break;
            case 5:
            if (item5.length() > 0) str_file_content += item5;
            break;
            case 6:
            if (item6.length() > 0) str_file_content += item6;
            break;
            case 7:
            if (item7.length() > 0) str_file_content += item7;
            break;
            case 8:
            if (item8.length() > 0) str_file_content += item8;
            break;
            case 9:
            if (item9.length() > 0) str_file_content += item9;
            break;
            case 10:
            if (item10.length() > 0) str_file_content += item10;
            break;
            case 11:
            if (item11.length() > 0) str_file_content += item11;
            break;
            case 12:
            if (item12.length() > 0) str_file_content += item12;
            break;
        }
        loopPass++;
    }
    str_file_content += delimiter; // this will add the seperating delimiter after all the data
    return str_file_content;
}

string Cipher::getItem(int itemNumberToReturn){
    switch (itemNumberToReturn)
    {
    case 2:
        return item2;
        break;
    case 3:
        return item3;
        break;
    case 4:
        return item4;
        break;
    case 5:
        return item5;
        break;
    case 6:
        return item6;
        break;
    case 7:
        return item7;
        break;
    case 8:
        return item8;
        break;
    case 9:
        return item9;
        break;
    case 10:
        return item10;
        break;
    case 11:
        return item11;
        break;
    case 12:
        return item12;
        break;
    
    default:
    return "Default Output Given";
        break;
    }
}

string Cipher::getItemS(int itemNumberToReturn){
    switch (itemNumberToReturn)
    {
    case 1:
        return itemS1;
        break;   
    case 2:
        return itemS2;
        break;
    case 3:
        return itemS3;
        break;
    case 4:
        return itemS4;
        break;
    case 5:
        return itemS5;
        break;
    case 6:
        return itemS6;
        break;
    case 7:
        return itemS7;
        break;
    case 8:
        return itemS8;
        break;
    case 9:
        return itemS9;
        break;
    case 10:
        return itemS10;
        break;
    
    default:
        return "Default Output Given";
        break;
    }
}