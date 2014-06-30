//function for Part I of HW 1
//in Natural Language Processing course
//Cecilia Aas June 2014

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int CountLines(string s)
{
  int nLines=0;
  string line;
  ifstream count_file;
  count_file.open(s.c_str());

  while (std::getline(count_file, line)) ++nLines;

  count_file.close();

  cout << nLines << endl;

  return nLines;
}


double emissionParameters()
{
   const string sInFile = "gene.counts";

   const string sZero = "0";
   const string sGene = "I-GENE";
   const string sWord = "WORDTAG";
   const string sTriGram = "3-GRAM";
   const string sBiGram = "2-GRAM";
   const string sUniGram = "1-GRAM";

   vector<string> words;
   vector<int> countWords;
   vector<string> labelWords;

   ofstream inCounts;
   inCount.open(sInFile.c_str());
   const int nLines = CountLines(sInFile);
   int nCount = 0;
   string inString;
   for(int i=0; i<nLines; i++)
   {
      inCount >> nCount >> inString;
      if(inString == sWord)
      {
         inCount >> labelWords[i] >> words[i];
         countWords[i] = nCount;
      } 
      else
      {
         break;
      }
   }
   inCount.close();

   inCount.open(sInFile.c_str())
   string inGram;
   vector<int> countUnigram;
   vector<int> countDigram;
   vector<int> countTrigram;
   vector<string> sUnigrams;
   vector<string> sDigram1;
   vector<string> sDigram2;
   vector<string> sTrigram1;
   vector<string> sTrigram2;
   vector<string> sTrigram3;

   string someText;

   for(int i=0; i<nLines; i++)
   {
      inCount >> nCount >> inString;
      if(inString == sWord)
      {
         continue;
      } 
      else
      {
         inCount >> inGram;

         if(inGram == sUniGram)
         {
            inCount >> someText;
            sUnigram.push_back(someText); 
            countUnigram.push_back(nCount); 
         }
         else if(inGram == sDiGram)
         {
            inCount >> someText;
            sDigram1.push_back(someText);
            inCount >> someText;
            sDigram2.push_back(someText);
            countDigram.push_back(nCount);
         }
         else if(inGram == sTriGram)
         {
            inCount >> someText;
            sTrigram1.push_back(someText);
            inCount >> someText;
            sTrigram2.push_back(someText);
            inCount >> someText;
            sTrigram3.push_back(someText);
            countTrigram.push_back(nCount);
         } 
         else
         {
             cout << "error in reading data" << endl;
             return 1.0;
         }
      }

   }

   inCount.close();
}
