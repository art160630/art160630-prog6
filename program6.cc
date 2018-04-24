//Alisha Tapiawala
//art160630@utdallas.edu
//CS 3377.502

#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "cdk.h"
#include <fstream>
#include <sstream>

//define matrix aspects
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Binary File Contents"

const int maxRecordStringLength = 25;

using namespace std;

class BinaryFileHeader
{
public: 
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{
  //create the matrix
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;        

  const char 		*rowTitles[] = {"666", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"666", "a", "b", "c"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  window = initscr();
  cdkscreen = initCDKScreen(window);

  initCDKColor();

  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //get data from binary file
  ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
  
  BinaryFileHeader *binaryHeader = new BinaryFileHeader();
  BinaryFileRecord *binaryRecord = new BinaryFileRecord();

  binInfile.read((char *) binaryHeader, sizeof(BinaryFileHeader));
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));

  //strings that hold binary file info
  string magicNo, version, numRecords, strlenb,strlenB, strlenc, strlenC, strlend, strlenD, strlene, strlenE, seedMoney, leadership, entre, skillz;
  magicNo = "Magic: 0x";
  version = "Version: ";
  numRecords = "NumRecords: ";
  strlenB = "strlen: ";
  strlenC = "strlen: ";
  strlenD = "strlen: ";
  strlenE = "strlen: ";

  //stringstream object to convert binary to dec, hex, and string
  stringstream convert;
  
  //get magic number
  convert << hex << uppercase << binaryHeader->magicNumber;
  magicNo += convert.str();
  convert.str(""); //resets the stringstream object

  //get version
  convert << dec << binaryHeader->versionNumber;
  version += convert.str();
  convert.str("");

  //get number of records
  convert << binaryHeader->numRecords;
  numRecords += convert.str();
  convert.str("");

  //get the first string and the length of the string
  convert << binaryRecord->stringBuffer;
  strlenb = convert.str();
  convert.str("");
  convert << strlenb.length();
  strlenB += convert.str();
  convert.str("");

  //get the second string and the length of the string 
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  convert << binaryRecord->stringBuffer;
  strlenc = convert.str();
  convert.str("");
  convert << strlenc.length();
  strlenC += convert.str();
  convert.str("");

  //get the third string and the length of the string 
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  convert << binaryRecord->stringBuffer;
  strlend = convert.str();
  convert.str("");
  convert << strlend.length();
  strlenD += convert.str();
  convert.str("");

  //get the fourth string and the length of the string 
  binInfile.read((char *) binaryRecord, sizeof(BinaryFileRecord));
  convert << binaryRecord->stringBuffer;
  strlene = convert.str();
  convert.str("");
  convert << strlene.length();
  strlenE += convert.str();
  convert.str("");

  //add the data to the matrix
  setCDKMatrixCell(myMatrix, 1, 1, magicNo.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str());
  setCDKMatrixCell(myMatrix, 2, 1, strlenB.c_str());
  setCDKMatrixCell(myMatrix, 2, 2, strlenb.c_str());  
  setCDKMatrixCell(myMatrix, 3, 1, strlenC.c_str());
  setCDKMatrixCell(myMatrix, 3, 2, strlenc.c_str());
  setCDKMatrixCell(myMatrix, 4, 1, strlenD.c_str());
  setCDKMatrixCell(myMatrix, 4, 2, strlend.c_str());
  setCDKMatrixCell(myMatrix, 5, 1, strlenE.c_str());
  setCDKMatrixCell(myMatrix, 5, 2, strlene.c_str());
  drawCDKMatrix(myMatrix, true);

  //wait for user input to exit the program
  unsigned char x;
  cin >> x;

  endCDK();
}
