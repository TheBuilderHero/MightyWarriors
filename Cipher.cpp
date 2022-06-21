#include <string>

#include "Cipher.h"
#include "Menu.h" //including for the display funciton

using namespace std;


//this function is intended to pull out the delimiters from a message and the data associated with each request
string Cipher::decipher(char messageFromClient[], bool hasSubItems){
    Menu menu;
    
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
            if (output.length() > 0) {
                try{ 
                    responseType = stoi(output);
                }catch(invalid_argument){ 
                    menu.display(1,1,"string Cipher::decipher(char messageFromClient[], bool hasSubItems){ Failed STOI", false);
                }
            } // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
            break;
            case 2://the second item enclosed in delimiters
            if (output.length() > 0) {
                item[2] = output;
                if (hasSubItems) subDecipher(item[2], 2);
                } 
            break;
            case 3://third item after delimiter
            if (output.length() > 0) {
                item[3] = output;
                if (hasSubItems) subDecipher(item[3], 3);
                }
            break;
            case 4://forth item after delimiter
            if (output.length() > 0) {
                item[4] = output;
                if (hasSubItems) subDecipher(item[4], 4);
                }
            break;
            case 5://fith item after delimiter
            if (output.length() > 0) {
                item[5] = output;
                if (hasSubItems) subDecipher(item[5], 5);
                }
            break;
            case 6://sixth item after delimiter
            if (output.length() > 0) {
                item[6] = output;
                if (hasSubItems) subDecipher(item[6], 6);
                }
            break;
            case 7://seventh item after delimiter
            if (output.length() > 0) {
                item[7] = output;
                if (hasSubItems) subDecipher(item[7], 7);
                }
            break; 
            case 8://the eighth item enclosed in delimiters
            if (output.length() > 0) {
                item[8] = output;
                if (hasSubItems) subDecipher(item[8], 8);
                } 
            break;
            case 9://the ninth item enclosed in delimiters
            if (output.length() > 0) {
                item[9] = output;
                if (hasSubItems) subDecipher(item[9], 9);
                } 
            break;
            case 10://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[10] = output;
                if (hasSubItems) subDecipher(item[10], 10);
                } 
            break;
            case 11://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[11] = output;
                if (hasSubItems) subDecipher(item[11], 11);
                } 
            break;
            case 12://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[12] = output;
                if (hasSubItems) subDecipher(item[12], 12);
                } 
            break;
            case 13:
            if (output.length() > 0) {
                item[13] = output;
                if (hasSubItems) subDecipher(item[13], 13);
                } 
            break;
            case 14:
            if (output.length() > 0) {
                item[14] = output;
                if (hasSubItems) subDecipher(item[14], 14);
                } 
            break;
            case 15:
            if (output.length() > 0) {
                item[15] = output;
                if (hasSubItems) subDecipher(item[15], 15);
                } 
            break;
            case 16:
            if (output.length() > 0) {
                item[16] = output;
                if (hasSubItems) subDecipher(item[16], 16);
                } 
            break;
            case 17:
            if (output.length() > 0) {
                item[17] = output;
                if (hasSubItems) subDecipher(item[17], 17);
                } 
            break;
            case 18:
            if (output.length() > 0) {
                item[18] = output;
                if (hasSubItems) subDecipher(item[18], 18);
                } 
            break;
            case 19:
            if (output.length() > 0) {
                item[19] = output;
                if (hasSubItems) subDecipher(item[19], 19);
                } 
            break;
            case 20:
            if (output.length() > 0) {
                item[20] = output;
                if (hasSubItems) subDecipher(item[20], 20);
                } 
            break;
            case 21:
            if (output.length() > 0) {
                item[21] = output;
                if (hasSubItems) subDecipher(item[21], 21);
                } 
            break;
            case 22:
            if (output.length() > 0) {
                item[22] = output;
                if (hasSubItems) subDecipher(item[22], 22);
                } 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}
string Cipher::decipher(string messageFromClient, bool hasSubItems){
    Menu menu;
    
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
            cout << ">>>" << output << "<<<" << endl;
            cout << s << endl;
            system("pause");

            if (output.length() > 0) {
                try{ 
                    responseType = stoi(output);
                }catch(invalid_argument){ 
                    menu.display(1,1,"string Cipher::decipher(char messageFromClient[], bool hasSubItems){ Failed STOI", false);
                }
            } // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
            break;
            case 2://the second item enclosed in delimiters
            if (output.length() > 0) {
                item[2] = output;
                if (hasSubItems) subDecipher(item[2], 2);
                } 
            break;
            case 3://third item after delimiter
            if (output.length() > 0) {
                item[3] = output;
                if (hasSubItems) subDecipher(item[3], 3);
                }
            break;
            case 4://forth item after delimiter
            if (output.length() > 0) {
                item[4] = output;
                if (hasSubItems) subDecipher(item[4], 4);
                }
            break;
            case 5://fith item after delimiter
            if (output.length() > 0) {
                item[5] = output;
                if (hasSubItems) subDecipher(item[5], 5);
                }
            break;
            case 6://sixth item after delimiter
            if (output.length() > 0) {
                item[6] = output;
                if (hasSubItems) subDecipher(item[6], 6);
                }
            break;
            case 7://seventh item after delimiter
            if (output.length() > 0) {
                item[7] = output;
                if (hasSubItems) subDecipher(item[7], 7);
                }
            break; 
            case 8://the eighth item enclosed in delimiters
            if (output.length() > 0) {
                item[8] = output;
                if (hasSubItems) subDecipher(item[8], 8);
                } 
            break;
            case 9://the ninth item enclosed in delimiters
            if (output.length() > 0) {
                item[9] = output;
                if (hasSubItems) subDecipher(item[9], 9);
                } 
            break;
            case 10://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[10] = output;
                if (hasSubItems) subDecipher(item[10], 10);
                } 
            break;
            case 11://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[11] = output;
                if (hasSubItems) subDecipher(item[11], 11);
                } 
            break;
            case 12://the tenth item enclosed in delimiters
            if (output.length() > 0) {
                item[12] = output;
                if (hasSubItems) subDecipher(item[12], 12);
                } 
            break;
            case 13:
            if (output.length() > 0) {
                item[13] = output;
                if (hasSubItems) subDecipher(item[13], 13);
                } 
            break;
            case 14:
            if (output.length() > 0) {
                item[14] = output;
                if (hasSubItems) subDecipher(item[14], 14);
                } 
            break;
            case 15:
            if (output.length() > 0) {
                item[15] = output;
                if (hasSubItems) subDecipher(item[15], 15);
                } 
            break;
            case 16:
            if (output.length() > 0) {
                item[16] = output;
                if (hasSubItems) subDecipher(item[16], 16);
                } 
            break;
            case 17:
            if (output.length() > 0) {
                item[17] = output;
                if (hasSubItems) subDecipher(item[17], 17);
                } 
            break;
            case 18:
            if (output.length() > 0) {
                item[18] = output;
                if (hasSubItems) subDecipher(item[18], 18);
                } 
            break;
            case 19:
            if (output.length() > 0) {
                item[19] = output;
                if (hasSubItems) subDecipher(item[19], 19);
                } 
            break;
            case 20:
            if (output.length() > 0) {
                item[20] = output;
                if (hasSubItems) subDecipher(item[20], 20);
                } 
            break;
            case 21:
            if (output.length() > 0) {
                item[21] = output;
                if (hasSubItems) subDecipher(item[21], 21);
                } 
            break;
            case 22:
            if (output.length() > 0) {
                item[22] = output;
                if (hasSubItems) subDecipher(item[22], 22);
                } 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}
string Cipher::subDecipher(string subMessageFromClient, int rootItem){
    
    //string message = messageFromClient; // change the message into a string

    
    // the above variables may later be replaced with a more wide veriety of variables however, for testing we are using all strings
    string s = subMessageFromClient;
    string str_file_content;
    string token, output;
    int loopPass = 0;
    size_t pos = 0; // position variable for removing the subDelimiters to view the message
    while ((pos = s.find(subDelimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        output = token;
        str_file_content += std::string(token); // we do not need to add spaces between the information for now so I removed: + std::string(" ")
        s.erase(0, pos + subDelimiter.length());
        switch (loopPass){
            case 1://the first item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][1] = output; // we many need to change the variable to an int with stoi(output) later but right now we just want a string version
            break;
            case 2://the second item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][2] = output; 
            break;
            case 3://the third item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][3] = output; 
            break;
            case 4://the forth item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][4] = output; 
            break;
            case 5://the fith item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][5] = output; 
            break;
            case 6://the sixth item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][6] = output; 
            break;
            case 7://the seventh item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][7] = output; 
            break; 
            case 8://the eighth item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][8] = output; 
            break;
            case 9://the ninth item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][9] = output; 
            break;
            case 10://the tenth item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][10] = output; 
            break;
            case 11://the eleventh item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][11] = output; 
            break;
            case 12://the twelth item enclosed in subDelimiters
            if (output.length() > 0) subItem[rootItem][12] = output; 
            break;
            case 13:
            if (output.length() > 0) subItem[rootItem][13] = output; 
            break;
            case 14:
            if (output.length() > 0) subItem[rootItem][14] = output; 
            break;
            case 15:
            if (output.length() > 0) subItem[rootItem][15] = output; 
            break;
            case 16:
            if (output.length() > 0) subItem[rootItem][16] = output; 
            break;
            case 17:
            if (output.length() > 0) subItem[rootItem][17] = output; 
            break;
            case 18:
            if (output.length() > 0) subItem[rootItem][18] = output; 
            break;
            case 19:
            if (output.length() > 0) subItem[rootItem][19] = output; 
            break;
            case 20:
            if (output.length() > 0) subItem[rootItem][20] = output; 
            break;
            case 21:
            if (output.length() > 0) subItem[rootItem][21] = output; 
            break;
            case 22:
            if (output.length() > 0) subItem[rootItem][22] = output; 
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
            case 11:
            if (output.length() > 0) itemS11 = output; 
            break;
            case 12:
            if (output.length() > 0) itemS12 = output; 
            break;
            case 13:
            if (output.length() > 0) itemS13 = output; 
            break;
            case 14:
            if (output.length() > 0) itemS14 = output; 
            break;
            case 15:
            if (output.length() > 0) itemS15 = output; 
            break;
            case 16:
            if (output.length() > 0) itemS16 = output; 
            break;
            case 17:
            if (output.length() > 0) itemS17 = output; 
            break;
            case 18:
            if (output.length() > 0) itemS18 = output; 
            break;
            case 19:
            if (output.length() > 0) itemS19 = output; 
            break;
            case 20:
            if (output.length() > 0) itemS20 = output; 
            break;
            case 21:
            if (output.length() > 0) itemS21 = output; 
            break;
            case 22:
            if (output.length() > 0) itemS22 = output; 
            break;
        }
        loopPass++;
    }
    return str_file_content;
}

//this functions purpose it to add the delimiters to given items 
string Cipher::cipher(string typeOfRequest, string username, string item3, string item4, string item5, string item6, string item7, string item8, string item9, string item10, string item11, string item12, string item13, string item14, string item15, string item16, string item17, string item18, string item19, string item20, string item21, string item22){ // the default values have been set to "" in case no input is given
    int numberOfItems = 22; //max number of items that we can cipher
    //"~" //a character that marks the beginning or end of a unit of data

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
            case 13:
            if (item13.length() > 0) str_file_content += item13;
            break;
            case 14:
            if (item14.length() > 0) str_file_content += item14;
            break;
            case 15:
            if (item15.length() > 0) str_file_content += item15;
            break;
            case 16:
            if (item16.length() > 0) str_file_content += item16;
            break;
            case 17:
            if (item17.length() > 0) str_file_content += item17;
            break;
            case 18:
            if (item18.length() > 0) str_file_content += item18;
            break;
            case 19:
            if (item19.length() > 0) str_file_content += item19;
            break;
            case 20:
            if (item20.length() > 0) str_file_content += item20;
            break;
            case 21:
            if (item21.length() > 0) str_file_content += item21;
            break;
            case 22:
            if (item22.length() > 0) str_file_content += item22;
            break;
        }
        loopPass++;
    }
    str_file_content += delimiter; // this will add the seperating delimiter after all the data
    return str_file_content;
}

string Cipher::subCipher(string item1, string item2, string item3, string item4, string item5, string item6, string item7, string item8, string item9, string item10, string item11, string item12, string item13, string item14, string item15, string item16, string item17, string item18, string item19, string item20, string item21, string item22){ // the default values have been set to "" in case no input is given
    int numberOfItems = 22; //max number of items that we can cipher
    //"=" //a character that marks the beginning or end of a unit of data

    string str_file_content;
    int loopPass = 1; // start the loop at 1 so that there is no extra spaces
    while (loopPass <= numberOfItems) {
        str_file_content += subDelimiter; // this will add the seperating subDelimiter before the a given item
        switch (loopPass){
            case 1:
            if (item1.length() > 0) str_file_content += item1;
            break;
            case 2:
            if (item2.length() > 0) str_file_content += item2;
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
            case 13:
            if (item13.length() > 0) str_file_content += item13;
            break;
            case 14:
            if (item14.length() > 0) str_file_content += item14;
            break;
            case 15:
            if (item15.length() > 0) str_file_content += item15;
            break;
            case 16:
            if (item16.length() > 0) str_file_content += item16;
            break;
            case 17:
            if (item17.length() > 0) str_file_content += item17;
            break;
            case 18:
            if (item18.length() > 0) str_file_content += item18;
            break;
            case 19:
            if (item19.length() > 0) str_file_content += item19;
            break;
            case 20:
            if (item20.length() > 0) str_file_content += item20;
            break;
            case 21:
            if (item21.length() > 0) str_file_content += item21;
            break;
            case 22:
            if (item22.length() > 0) str_file_content += item22;
            break;
        }
        loopPass++;
    }
    str_file_content += subDelimiter; // this will add the seperating subDelimiter after all the data
    return str_file_content;
}

string Cipher::getItem(int itemNumberToReturn, int subItemNumber){ //this is usally item3 - item22 However, the subItemNumbers are item1 - item22
    if(subItemNumber > 0) return subItem[itemNumberToReturn][subItemNumber];
    return item[itemNumberToReturn];
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
    case 11:
        return itemS11;
        break;
    case 12:
        return itemS12;
        break;
    case 13:
        return itemS13;
        break;
    case 14:
        return itemS14;
        break;
    case 15:
        return itemS15;
        break;
    case 16:
        return itemS16;
        break;
    case 17:
        return itemS17;
        break;
    case 18:
        return itemS18;
        break;
    case 19:
        return itemS19;
        break;
    case 20:
        return itemS20;
        break;
    case 21:
        return itemS21;
        break;
    case 22:
        return itemS22;
        break;
    
    default:
        return "Default Output Given";
        break;
    }
}