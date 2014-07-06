//function for Part I of HW 1
//function for Part I of HW 1
//in Natural Language Processing course
//Cecilia Aas June 2014

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "wordCount.h"
#include "emissionParameters.h"
#include "replaceRare.h"
#include "trigramParameters.h"

using namespace std;




int main()
{
   //io file names
   const string countFile = "geneRare.counts";
   const string countOutFile = countFile + ".trainOut";
   const string testInFile = "gene.dev";   //"gene.test";
   const string testOutFile = testInFile + ".predict";

   // ----------------------- TRAINING PHASE -----------------------
   //evaluate and output emission parameters for original training data
   map<vector<string>, double> e = emissionParameters(countFile);

   //tag words using emission parameters
   map<string, string> maxEmit = findMaxEmission(e);

   //output results for training data
   ofstream outCounts;
   outCounts.open(countOutFile.c_str());
   outCounts << "tag" << "\t" << setw(18) << left << "word" << "\t" << "probability(tag|word)" << "\t" << "predicted tag" << endl;
   typedef map<vector<string>, double>::const_iterator pIter;
   for(pIter p = e.begin(); p!=e.end(); ++p)
   {
       vector<string> inP = p->first;
       outCounts << inP[0] << "\t" << setw(18) << left << inP[1] << "\t" << setw(7) << setprecision (8) << fixed << p->second << "\t\t" << maxEmit[inP[1]] << endl;
   }
   outCounts.close();


   // ----------------------- TAGGING OF TEST DATA------------------
   const string sRare = "_RARE_";
   const string sDot = ".";

   //tag test data, output results to file
   ofstream maxCounts;
   ifstream testFile;
   testFile.open(testInFile.c_str());
   maxCounts.open(testOutFile.c_str());
   string inWord, inJunk;
   while(testFile.good())
   {
       testFile >> inWord; // >> inJunk;
       if(testFile.eof()) break;
       if(maxEmit.count(inWord) > 0)
       {
          maxCounts << inWord << " " << maxEmit[inWord] << endl;
       }
       else
       {
	  maxCounts << inWord << " " << maxEmit[sRare] << endl;
       }

       if(inWord == sDot)
       {
	   maxCounts << endl;
       } 
   }
   maxCounts.close();
   testFile.close();


   // --------------- PROBABILITY PARAMETERS EVALUATION ------------
   //evaluate trigram probabilities
   ofstream probsFile;
   probsFile.open("TrigramProbabilities.dat");
   probsFile << "y_i" << "\t" << setw(24) << left << "y_{i-1}, y_{i-2}" << setw(16) << setprecision (8) << fixed << "q(y_i | y_{i-1}, y_{i-2})" << endl;
   map<vector<string>, double> qParam = collectTrigramCounts();
   for(pIter q = qParam.begin(); q != qParam.end(); ++q)
   {
       vector<string> currentTrigram = q->first;
       double currentQ = q->second;
       probsFile << currentTrigram[2] << "\t" << setw(24) << left << currentTrigram[0] + ", " + currentTrigram[1] << setw(16) << setprecision (8) << fixed << currentQ << endl;
   }
   probsFile.close();



   return 0;
}
