#include<bits/stdc++.h>

using namespace std;




string format1Arr[] = {"FIX" , "FLOAT" , "HIO" , "NORM" , "SIO" , "TIO"};
string format2Arr[] = {"ADDR" , "CLEAR" , "COMPR" , "DIVR" , "MULR" , "RMO" , "SHIFTL" , "SHIFTR" , "SUBR" , "SVC" , "TIXR"};
string opCodeArr[59][59] = { {"ADD" , "18"} , {"ADDF" , "58"} , {"ADDR" , "90"} , {"AND" , "40"} , {"CLEAR" , "B4"} , {"COMP" , "28"} , {"COMPF" , "88"} , {"COMPR" , "A0"} , {"DIV" , "24"} ,
{"DIVF" , "64"} , {"DIVR" , "9C"} , {"FIX" , "C4"} , {"FLOAT" , "C0"} , {"HIO" , "F4"} , {"J" , "3C"} , {"JEQ" , "30"} , {"JGT" , "34"} , {"JLT" , "38"} , {"JSUB" , "48"} , {"LDA" , "00"} ,
{"LDB" , "68"} , {"LDCH" , "50"} , {"LDF" , "70"} , {"LDL" , "08"} , {"LDS" , "6C"} , {"LDT" , "74"} , {"LDX" , "04"} , {"LPS" , "D0"} , {"MUL" , "20"} , {"SSK" , "EC"} , {"STA" , "0C"} ,
{"STB" , "78"} , {"STCH" , "54"} , {"STF" , "80"} , {"STI" , "D4"} , {"STL" , "14"} , {"STS" , "7C"} , {"STSW" , "E8"} , {"STT" , "84"} , {"STX" , "10"} , {"SUB" , "1C"} , {"SUBF" , "5C"} ,
{"MULF" , "60"} , {"MULR" , "98"} , {"NORM" , "C8"} , {"OR" , "44"} , {"RD" , "D8"} , {"RMO" , "AC"} , {"RSUB" , "4C"} , {"SHIFTL" , "A4"} , {"SHIFTR" , "A8"} , {"SIO" , "F0"} , {"SUBR" , "94"} ,
{"SVC" , "B0"} , {"TD" , "E0"} , {"TIO" , "F8"} , {"TIX" , "2C"} , {"TIXR" , "B8"} , {"WD" , "DC"} };

const int MAX_PC = 2047 , MIN_PC = -2048 , MAX_BASE = 4095 , MIN_BASE = 0;

string registerOP[9][9] = { {"A" , "0"} , {"X" , "1"} , {"L" , "2"} , {"B" , "3"} , {"S" , "4"} , {"T" , "5"} , {"F" , "6"} , {"PC" , "8"} , {"SW" , "9"} };


void writeSymTabintoFile(string locArr[] , string symbolsArr[] , string instArr[] , string refArr[] , int size){
    ofstream outFile("symtab.txt");
    if (outFile.is_open()){

        for (int i = 0 ; i < size ; i++){
            outFile << locArr[i] << '\t' << symbolsArr[i] << '\t' << instArr[i] << '\t' << refArr[i] << endl;
        }
        outFile.close();
    }
    else
        cout << "Couldn't Write SymTab to file" << endl;
}

void writeObjTabintoFile(string locArr[] , string symbolsArr[] , string instArr[] , string refArr[] , string objArr[] , int size){
    ofstream outFile("objtab.txt");
    if (outFile.is_open()){

        for (int i = 0 ; i < size ; i++){
            outFile << locArr[i] << '\t' << symbolsArr[i] << '\t' << instArr[i] << '\t' << refArr[i] << '\t' << objArr[i] << endl;
        }
        outFile.close();
    }
    else
        cout << "Couldn't Write ObjTab to file" << endl;
}

void writeHTEintoFile(string headerRecord , vector<string> textRecords , vector<string> modificationRecords , string endRecord){
    ofstream outFile("outHTE.txt");
    if (outFile.is_open()){
        outFile << headerRecord << endl;
        for (int i = 0 ; i < textRecords.size() ; i++){
            outFile << textRecords[i];
        }
        for (int i = 0 ; i < modificationRecords.size() ; i++){
            outFile << modificationRecords[i] << endl;
        }
        outFile << endRecord << endl;
        outFile.close();
    }
}

int convertHexToDec(string hexString){
  stringstream stream;
  int dec;
  stream << hexString;
  stream >> hex >> dec;
  return dec;
}

int convertStringToInt(string str){
    int value;
    stringstream(str) >> value;
    return value;
}

string convertDecToHex(int decimal){
    stringstream stream2;
    stream2 << hex << decimal;
    string result(stream2.str());
    char resultUpper[10];
    strcpy(resultUpper, result.c_str());
    for (int i = 0 ; i < strlen(resultUpper) ; i++){
        resultUpper[i] = toupper(resultUpper[i]);
    }
    return resultUpper;
}

string convertHexToBin(string text){
    int no = 0;
    string binaryResult = "";
    for (int i = 0 ; i < text.length() ; i++){
        string temp = "";
        if (text[i] >= '0' && text[i] <= '9'){
            no = int(text[i]) - 48;
            while (no > 0){
                temp += char(no % 2 + 48);
                no /= 2;
            }
            while (temp.length() != 4){
                temp += '0';
            }
            no = 0;
        }
        else {
            no = text[i] - 'A' + 10;
            while (no > 0){
                temp += char(no % 2 + 48);
                no /= 2;
            }
        }
        for (int j = 3 ; j >= 0 ; j--){
            binaryResult += temp[j];
        }
    }
    return binaryResult;
}

string convertBinToHex(string binText){
    stringstream res;
    string binary_str(binText);
    bitset<12> set(binary_str);
    res << hex << uppercase << set.to_ulong();
    return res.str();
}

int checkIfNumber(string str){
    for (int i = 0 ; i < str.size() ; i++){
        if (isdigit(str[i]) == 0)
            return 0;
    }
    return 1;
}

int searchFormat1(string str){
    int found = 0;
    for (int i = 0 ; i < sizeof(format1Arr) / sizeof(format1Arr[0]) ; i++){
        if (str == format1Arr[i]){
            found = 1;
            break;
        }
    }
    return found;
}

int searchFormat2(string str){
    int found = 0;
    for (int i = 0 ; i < sizeof(format2Arr) / sizeof(format2Arr[0]) ; i++){
        if (str == format2Arr[i]){
            found = 1;
            break;
        }
    }
    return found;
}

string searchOpCode(string str){
    string opCode = "";
    for (int i = 0 ; i < sizeof(opCodeArr) / sizeof(opCodeArr[0][0]) ; i++){
        if (str == opCodeArr[i][0]){
            opCode = opCodeArr[i][1];
            break;
        }
    }

    return opCode;
}

string searchRegOpCode(string str){
    string rOpCode = "";
    for (int i = 0 ; i < sizeof(registerOP) / sizeof(registerOP[0][0]) ; i++){
        if (str == registerOP[i][0]){
            rOpCode = registerOP[i][1];
            break;
        }
    }
    return rOpCode;
}

string byteXopcode(string str){
    string result = str.substr(2 , str.length() - 1);
    char tempArr[result.length()];
    strcpy(tempArr, result.c_str());
    string embeddedString = "";
    int i = 0;
    while (tempArr[i] != 39){
        embeddedString += tempArr[i];
        i++;
    }
    return embeddedString;
}

string byteCopcode(string str){
    string result = str.substr(2 , str.length() - 1);
    char tempArr[result.length()];
    strcpy(tempArr, result.c_str());
    string embeddedString = "";
    int i = 0;
    while (tempArr[i] != 39){
        embeddedString += tempArr[i];
        i++;
    }
    stringstream stream;
    for (int i = 0 ; i < embeddedString.length() ; i++) {
        stream << hex << int(embeddedString[i]);
    }
    string answer = stream.str();
    for (int i = 0 ; i < answer.length() ; i++){
        answer[i] = toupper(answer[i]);
    }

    return answer;
}

int isIndexBased(string str){
    int found = 0;
    if(str.substr(str.length() - 2 , str.length()) == ",X" || str.substr(str.length() - 2 , str.length()) == ",x"){
        found = 1;
    }
    return found;
}

int checkIfPcRelative(int num){
    if (num >= MIN_PC && num <= MAX_PC)
        return 1;
    else
        return 0;
}

string searchForLocation(string str){
    string location = "";
    ifstream symbolTable("symtab.txt");
    int i = 0;

    string line;
    string locText , symbolsText , temp1Text , temp2Text;

    string locationArr[200];
    string symbolsArray[200];
    string temp1[200];
    string temp2[200];

    while(getline (symbolTable, line))
      {
          stringstream ss(line);
          getline(ss , locText , '\t');
          getline(ss , symbolsText , '\t');
          getline(ss , temp1Text , '\t');
          getline(ss , temp2Text , '\t');
          locationArr[i] = locText;
          symbolsArray[i] = symbolsText;
          temp1[i] = temp1Text;
          temp2[i] = temp2Text;
          ++i;
     }
    symbolTable.close();

    for (int i = 0 ; i < sizeof(symbolsArray) / sizeof(symbolsArray[0]) ; i++){
        if (symbolsArray[i] == str){
            location = locationArr[i];
            break;
        }
    }
    return location;

}

int searchForBaseValue(string locArr[] , string symbolsArr[] , string instArr[] , string refArr[] , int size){
    int x = 0;
    string hexLoc = "";
    for (int i = 0 ; i < size ; i++){
        if (instArr[i] == "BASE"){
           hexLoc = searchForLocation(refArr[i]);
           break;
        }
    }
    x = convertHexToDec(hexLoc);
    return x;
}


int main()
{
  ifstream inputFile;
  int numLines = 0;
  int i = 0;
  inputFile.open("sicxe.txt");

  string tempLine;

    while (getline(inputFile , tempLine)){
        numLines++;
    }
    inputFile.close();

    inputFile.open("sicxe.txt");

    string symbolsArr[numLines + 1];
    string instArr[numLines + 1];
    string refArr[numLines + 1];
    string locArr[numLines + 1];
    string objArr[numLines + 1];

    string line;
    string symbolsText , instText , refText;

    while(getline (inputFile, line))
      {
          stringstream ss(line);
          getline(ss , symbolsText , '\t');
          getline(ss , instText , '\t');
          getline(ss , refText , '\t');
          symbolsArr[i] = symbolsText;
          instArr[i] = instText;
          refArr[i] = refText;
          ++i;
     }

  inputFile.close();

  if (refArr[0].length() == 1){
    locArr[0] = locArr[1] = "000" + refArr[0];
  }
  else if(refArr[0].length() == 2){
    locArr[0] = locArr[1] = "00" + refArr[0];
  }
  else if (refArr[0].length() == 3){
    locArr[0] = locArr[1] = "0" + refArr[0];
  }

  string endAddress = "";

  for (int i = 1 ; i <= (sizeof(instArr) / sizeof(instArr[0])) ; i++){
    if (instArr[i] == ""){
        break;
    }
    if (symbolsArr[i+1] == "" && instArr[i+1] == "" && refArr[i+1] == ""){
        break;
    }

    int flag = 0;
    int countIncr = 0;

    if (instArr[i + 1] == "BASE"){
        countIncr = 0;
        locArr[i + 1] = "";
        flag = 1;
    }

    else if (instArr[i].substr(0 , 1) == "+"){
        countIncr = 4;
    }

    else if (searchFormat1(instArr[i]) == 1){
        countIncr = 1;
    }

    else if (searchFormat2(instArr[i]) == 1){
        countIncr = 2;
    }

    else if (instArr[i] == "BYTE"){
        string temp = refArr[i];
        char tempArr[temp.length()];
        strcpy(tempArr, temp.c_str());
        if (tempArr[0] == 'X' || tempArr[0] == 'x'){
            countIncr = (strlen(tempArr) - 3) / 2 ;
        }
        else if (tempArr[0] == 'C' || tempArr[0] == 'c'){
            countIncr = strlen(tempArr) - 3;
        }
    }
    else if (instArr[i] == "RESW"){
        countIncr = convertHexToDec(refArr[i]) * 3;
    }
    else if (instArr[i] == "RESB"){
        string temp = convertDecToHex(convertStringToInt(refArr[i]));
        int tempDec = convertHexToDec(temp);
        tempDec += convertHexToDec(locArr[i]);
        locArr[i + 1] = convertDecToHex(tempDec);
        flag = 1;
    }
    else{
        countIncr = 3;
    }
    int temp = convertHexToDec(locArr[i]);
    if (flag == 0){
        locArr[i + 1] = convertDecToHex(temp + countIncr);
        if (locArr[i + 1].length() == 1){
            locArr[i + 1] = "000" + locArr[i+1];
        }
        else if (locArr[i + 1].length() == 2){
            locArr[i + 1] = "00" + locArr[i+1];
        }
    }

    if (instArr[i + 1] == "END"){
        endAddress = locArr[i + 1];
    }

  }


  writeSymTabintoFile(locArr , symbolsArr , instArr , refArr , (sizeof(instArr) / sizeof(instArr[0])) );


  for (int i = 0 ; i < (sizeof(instArr) / sizeof(instArr[0])) ; i++){
        string temp = instArr[i];
        if (temp.substr(0 , 1) == "+"){
            temp = instArr[i].substr(1 , instArr[i].length() - 1);
        }
        if (temp == "START" || temp == "BASE" || temp == "RESB" || temp == "RESW" || temp == "END"){
            objArr[i] = "";
        }
        else if (temp == "BYTE"){
            string byte = refArr[i];
            char tempArr[byte.length()];
            strcpy(tempArr, byte.c_str());
            if (tempArr[0] == 'X' || tempArr[0] == 'x'){
                objArr[i] = byteXopcode(byte);
            }
            else if (tempArr[0] == 'C' || tempArr[0] == 'c'){
                objArr[i] = byteCopcode(byte);
            }
        }
        else if (temp == "WORD"){
            string word = convertDecToHex(convertStringToInt(refArr[i]));
            if (word.length() == 1)
                word = "00000" + word;
            else if (word.length() == 2)
                word = "0000" + word;
            else if (word.length() == 3)
                word = "000" + word;
            else if (word.length() == 4)
                word = "00" + word;
            else if (word.length() == 5)
                word = "0" + word;
            objArr[i] = word;
        }
        else if (temp == "RSUB"){
            string opRsub = searchOpCode(temp);
            string opRbits = convertHexToBin(opRsub).substr(0 , 6);
            opRbits = opRbits + "1" + "1"; // n i
            objArr[i] = convertBinToHex(opRbits) + "0000";
        }
        else if (searchFormat2(temp) == 1){
            string opForm2 = searchOpCode(temp);
            if (refArr[i].length() == 5){
                opForm2 += searchRegOpCode(refArr[i].substr(0 , 2));
                opForm2 += searchRegOpCode(refArr[i].substr(3 , refArr[i].length() - 1));
            }
            else if (refArr[i].length() == 4){
                if (refArr[i].substr(0 , 2) == "PC" || refArr[i].substr(0 , 2) == "SW"){
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 2));
                    opForm2 += searchRegOpCode(refArr[i].substr(3 , refArr[i].length() - 1));
                }
                else {
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 1));
                    opForm2 += searchRegOpCode(refArr[i].substr(2 , refArr[i].length() - 1));
                }
            }
            else if (refArr[i].length() == 3){
                if (checkIfNumber(refArr[i].substr(2 , refArr[i].length() - 1)) == 1){
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 1));
                    opForm2 += refArr[i].substr(2 , refArr[i].length() - 1);
                }
                else{
                    opForm2 += searchRegOpCode(refArr[i].substr(0 , 1));
                    opForm2 += searchRegOpCode(refArr[i].substr(2 , refArr[i].length() - 1));
                }
            }
            else if (refArr[i].length() == 2){
                opForm2 += searchRegOpCode(refArr[i]);
            }
            else if (refArr[i].length() == 1){
                opForm2 += searchRegOpCode(refArr[i]);
            }
            if (opForm2.length() == 3){
                opForm2 = opForm2 + "0";
            }
            objArr[i] = opForm2;
        }

        else if (searchFormat1(temp) == 1){
            string opForm1 = searchOpCode(temp);
            objArr[i] = opForm1;
        }
        else if (instArr[i].substr(0 , 1) == "+"){
            string opForm4 = searchOpCode(temp);
            string bits6Op = convertHexToBin(opForm4).substr(0 , 6); // 6 bits op code
            string n4 , i4 , x4 , b4 , p4 , e4;
            string symbolLocation = "";
            e4 = n4 = i4 = "1";
            x4 = b4 = p4 = "0";
            symbolLocation = searchForLocation(refArr[i]);
            if (refArr[i].substr(0 , 1) == "#"){
                n4 = "0";
                if (checkIfNumber(refArr[i].substr(1 , refArr[i].length())) == 1){
                    symbolLocation = convertDecToHex(convertStringToInt(refArr[i].substr(1 , refArr[i].length())));
                }
                else
                    symbolLocation = searchForLocation(refArr[i].substr(1 , refArr[i].length()));
            }
            if (refArr[i].substr(0 , 1) == "@"){
                i4 = "0";
                symbolLocation = searchForLocation(refArr[i].substr(1 , refArr[i].length()));
            }
            if (isIndexBased(refArr[i]) == 1){
                x4 = "1";
                symbolLocation = searchForLocation(refArr[i].substr(0 , refArr[i].length() - 2));
            }
            if (isIndexBased(refArr[i]) == 1 && refArr[i].substr(0 , 1) == "@"){
                i4 = "0";
                x4 = "1";
                symbolLocation = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            if (isIndexBased(refArr[i]) == 1 && refArr[i].substr(0 , 1) == "#"){
                n4 = "0";
                x4 = "1";
                symbolLocation = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            string nixbpe4 = n4 + i4 + x4 + b4 + p4 + e4;
            opForm4 = bits6Op + nixbpe4;
            symbolLocation = "0" + symbolLocation;
            objArr[i] = convertBinToHex(opForm4) + symbolLocation;
        }
        else if (instArr[i].substr(0 , 1) != "+" && searchFormat1(temp) != 1 && searchFormat2(temp) != 1 && instArr[i] != ""){
            int flag = 0;
            string opForm3 = searchOpCode(temp);
            string bits6Op3 = convertHexToBin(opForm3).substr(0 , 6);
            string n3 , i3 , x3 , b3 , p3 , e3;
            string symbolDisp = "";
            n3 = i3 = p3 = "1";
            x3 = b3 = e3 = "0";
            symbolDisp = searchForLocation(refArr[i]);
            if (refArr[i].substr(0 , 1) == "#"){
                n3 = "0";
                if (checkIfNumber(refArr[i].substr(1 , refArr[i].length())) == 1){
                    symbolDisp = convertDecToHex(convertStringToInt(refArr[i].substr(1 , refArr[i].length())));
                    p3 = "0";
                    flag = 1;
                }
                else
                    symbolDisp = searchForLocation(refArr[i].substr(1 , refArr[i].length()));
            }
            if (refArr[i].substr(0 , 1) == "@" && flag == 0){
                i3 = "0";
                symbolDisp = searchForLocation(refArr[i].substr(1 , refArr[i].length()));
            }
            if (isIndexBased(refArr[i]) == 1 && flag == 0){
                x3 = "1";
                symbolDisp = searchForLocation(refArr[i].substr(0 , refArr[i].length() - 2));
            }
            if (isIndexBased(refArr[i]) == 1 && refArr[i].substr(0 , 1) == "@" && flag == 0){
                i3 = "0";
                x3 = "1";
                symbolDisp = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            if (isIndexBased(refArr[i]) == 1 && refArr[i].substr(0 , 1) == "#" && flag == 0){
                n3 = "0";
                x3 = "1";
                symbolDisp = searchForLocation(refArr[i].substr(1 , refArr[i].length() - 3));
            }
            int pc , base;
            if (locArr[i + 1] == ""){
                pc = convertHexToDec(locArr[i + 2]);
            }
            else
                pc = convertHexToDec(locArr[i+1]);
            if (checkIfPcRelative(convertHexToDec(symbolDisp) - pc) == 0 && flag == 0){
                p3 = "0";
                b3 = "1";
                base = searchForBaseValue(locArr  , symbolsArr , instArr , refArr , sizeof(instArr)/sizeof(instArr[0]));
                symbolDisp = convertDecToHex(convertHexToDec(symbolDisp) - base);
            }
            else if (checkIfPcRelative(convertHexToDec(symbolDisp) - pc) == 1 && flag == 0){
                symbolDisp = convertDecToHex(convertHexToDec(symbolDisp) - pc);
            }
            string nixbpe3 = n3 + i3 + x3 + b3 + p3 + e3;
            opForm3 = bits6Op3 + nixbpe3;
            if (symbolDisp.length() == 1){
                symbolDisp = "00" + symbolDisp;
            }
            else if (symbolDisp.length() == 2){
                symbolDisp = "0" + symbolDisp;
            }
            if (opForm3.substr(0 , 4) == "0000"){
                opForm3 = "0" + convertBinToHex(opForm3);
                objArr[i] = opForm3 + symbolDisp;
            }
            else
                objArr[i] = convertBinToHex(opForm3) + symbolDisp;
            if (objArr[i].length() > 8){
                objArr[i] = objArr[i].substr(0 , 3) + objArr[i].substr(objArr[i].length() - 3 , objArr[i].length());
            }
        }


    }

    writeObjTabintoFile(locArr , symbolsArr , instArr , refArr , objArr , sizeof(instArr)/sizeof(instArr[0]));

    string hRecord = symbolsArr[0];
    if (hRecord.length() == 4){
        hRecord = hRecord + "__";
    }
    else if (hRecord.length() == 5){
        hRecord = hRecord + "_";
    }
    string startAddress = locArr[0];
    if (startAddress.length() == 4){
        startAddress = "00" + startAddress;
    }
    else if (startAddress.length() == 5){
        startAddress = "0" + startAddress;
    }
    string programLength = convertDecToHex(convertHexToDec(endAddress) - convertHexToDec(startAddress));
    if (programLength.length() == 4){
        programLength = "00" + programLength;
    }
    else if (programLength.length() == 5){
        programLength = "0" + programLength;
    }
    hRecord = "H^" + hRecord + "^" + startAddress + "^" + programLength;
    string endRecord = "E^"+startAddress;

    vector <string> tRecord;
    vector <string> mRecord;
    vector <string> temp;
    int textRLength = 0;
    int flag = 0;
    int first = 0;
    int cnt = 0;
    string lastAddress = "";

    for (int i = 0 , j = 0 ; i < sizeof(objArr)/sizeof(objArr[0]) ; i++ , j++){
        if (flag == 0){
            if (first == 0){
                tRecord.push_back("T^" + startAddress + "^");
                first = 1;
            }
            if (textRLength + objArr[i].length() / 2 <= 30){
                textRLength += objArr[i].length() / 2;
                temp.push_back(objArr[i]);
            }
            if (textRLength + objArr[i].length() / 2 >= 30){
                textRLength = 0;
                flag = 1;
                lastAddress = locArr[i + 1];
                tRecord.push_back(convertDecToHex(convertHexToDec(locArr[i + 1]) - convertHexToDec(startAddress))+"^");
                tRecord.insert(tRecord.end() , temp.begin() , temp.end());
                tRecord.push_back("\n");
                temp.clear();
            }
        }
        else if (flag == 1){
            if (first == 1){
                if (lastAddress.length() == 4)
                    lastAddress = "00" + lastAddress;
                else if (lastAddress.length() == 5)
                    lastAddress = "0" + lastAddress;
                tRecord.push_back("T^" + lastAddress + "^");
                first = 0;
            }
            if (textRLength + objArr[i].length() / 2 <= 30){
                textRLength += objArr[j].length() / 2;
                temp.push_back(objArr[j]);
            }
            if (textRLength + objArr[i].length() / 2 >= 30 || instArr[i] == "RESW" || instArr[i] == "RESB" || instArr[i] == "END"){
                textRLength = 0;
                string tLength = convertDecToHex(convertHexToDec(locArr[i]) - convertHexToDec(lastAddress));
                if (tLength.length() == 1){
                    tLength = "0" + tLength;
                }
                tRecord.push_back(tLength+"^");
                tRecord.insert(tRecord.end() , temp.begin() , temp.end());
                tRecord.push_back("\n");
                temp.clear();

                while (instArr[i] == "RESW" || instArr[i] == "RESB"){
                    i++;
                }
                j = i - 1;
                lastAddress = locArr[i];
                first = 1;
                if (instArr[i] == "END")
                    break;
            }
        }
    }

    for (int i = 0 ; i < sizeof(objArr) / sizeof(objArr[0]) ; i++){
        if (objArr[i].length() == 8){
            string tempLoc = locArr[i];
            tempLoc = convertDecToHex(convertHexToDec(tempLoc) + 1);
            if (tempLoc.length() == 5)
                tempLoc = "0" + tempLoc;
            else if (tempLoc.length() == 4)
                tempLoc = "00" + tempLoc;
            else if (tempLoc.length() == 3)
                tempLoc = "000" + tempLoc;
            else if (tempLoc.length() == 2)
                tempLoc = "0000" + tempLoc;
            else if (tempLoc.length() == 1)
                tempLoc = "00000" + tempLoc;
            if (refArr[i].substr(0 , 1) == "#"){
                if (checkIfNumber(refArr[i].substr(1 , refArr[i].length())) == 0){
                    mRecord.push_back("M^" + tempLoc + "^05");
                }
            }
            else{
                mRecord.push_back("M^" + tempLoc + "^05");
            }
        }
    }

    writeHTEintoFile(hRecord , tRecord , mRecord , endRecord);


    cout << "Loc  |" << '\t' << "Symb  |" << '\t' << "Inst  |" << '\t' << " Ref   |" << "   Obj   |" << endl << "_____|________|_______|________|_________|" << endl;

  for (int i = 0 ; i < (sizeof(instArr) / sizeof(instArr[0])) ; i++){
        cout << locArr[i] << '\t' << symbolsArr[i] << '\t' << instArr[i] << '\t' << refArr[i] << '\t' << "  " << objArr[i] <<endl;
  }

  cout << hRecord << endl;

  for (int i = 0 ; i < tRecord.size() ; i++){
      cout << tRecord[i];
  }


  for (int i = 0 ; i < mRecord.size() ; i++){
        cout << mRecord[i] << endl;
  }

  cout << endRecord << endl;

  return 0;

}




