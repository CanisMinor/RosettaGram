//function for Part I of HW 1
//function for Part I of HW 1
//in Natural Language Processing course
//Cecilia Aas June 2014

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "wordCount.h"

using namespace std;



map<vector<string>, double> emissionParameters(const string sInFile)
{
   const string sWordtag = "WORDTAG";

   map<string, int>  wCounts = wordCounts(sInFile);  
   
   
   map<vector<string>, double> emissionParams;
   string inLabel, inWord, inString;
   int nCount = 0;
   ifstream inCount;
   inCount.open(sInFile.c_str());
   vector<string> inPuts(2,"");
   while(inCount.good())
   {
      inCount >> nCount >> inString;
      if(inCount.eof()) break;
      if(inString == sWordtag)
      {
         inCount >> inLabel >> inWord;
         inPuts[0] = inLabel;
	 inPuts[1] = inWord;
	 emissionParams[inPuts] = ((double) nCount) / ((double) wCounts[inWord]);
      }
      else
      {
         break;
      }
   }
   inCount.close();

   return emissionParams;
}


map<string,string> findMaxEmission(map<vector<string>, double> e)
{
   map<string, string> maxEmit;

   const string sGene = "I-GENE";
   const string sWord = "O";
   vector<string> ePairGene(2,"");
   vector<string> ePairWord(2,"");
   typedef map<vector<string>, double>::const_iterator pIter;
   for(pIter p = e.begin(); p!=e.end(); ++p)
   {
      vector<string> pLabelWord = p->first;
      string testWord = pLabelWord[1];
      string testLabel = pLabelWord[0];

      ePairGene[0] = sGene;
      ePairWord[0] = sWord;
      ePairGene[1] = testWord;
      ePairWord[1] = testWord;

      if(maxEmit.count(testWord)==0)
      {
         if(e[ePairGene] > e[ePairWord])
         {
             string temp = ePairGene[0];
	     ePairGene[0] = ePairGene[1];
	     ePairGene[1] = temp;
             maxEmit.insert(pair<string,string>(p->first[1],sGene));
         }
         else
         {
             string temp = ePairWord[0];
	     ePairWord[0] = ePairWord[1];
	     ePairGene[1] = temp;
             maxEmit.insert(pair<string,string>(p->first[1],sWord));
         }
      } 
   }

   return maxEmit; 
}

