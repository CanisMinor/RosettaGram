//function for Part I of HW 1
//function for Part I of HW 1
//in Natural Language Processing course
//Cecilia Aas June 2014

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "wordCount.h"

using namespace std;



int replaceRare()
{
   const string inFile = "gene.train";
   const string outFile = "geneRare.train";

   map <string, int>  wCounts = wordCounts(inFile);  
   ofstream replaceRareOut;
   ifstream trainIn;
   replaceRareOut.open(outFile.c_str());
   trainIn.open(inFile.c_str());

   string inWord;
   string inLabel;
   while(trainIn.good())
   {
       trainIn >> inWord >> inLabel;
       if(trainIn.eof() ) break;
       if(wCounts[inWord] < 5)
       {
          replaceRareOut << "_RARE_" << " " << inLabel << endl;
       }
       else
       {
	  replaceRareOut << inWord << " " << inLabel << endl;
       }
   }
   trainIn.close();
   replaceRareOut.close();
}


