//function to evaluate the trigram frequency parameters
//Cecilia Aas 6th July 2014

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;


map<vector<string>, double> collectTrigramCounts()
{
   vector<string> unigramsList;
   map<vector<string>, int> digramCounts;
   map<vector<string>, int> trigramCounts;

   const string sGene = "I-GENE";
   const string sWord = "O";
   const string sWordtag = "WORDTAG";
   const string sNothing = "*";
   const string sStop = "STOP";
   const string sUnigram = "1-GRAM";
   const string sDigram = "2-GRAM";
   const string sTrigram = "3-GRAM";

   ifstream countsFile;
   vector<string> inDigram(2,"");
   vector<string> inTrigram(3,"");
   countsFile.open("geneRare.counts");
   string inString;
   string inJunk;
   int inCount;
   while(countsFile.good())
   {
       countsFile >> inCount >> inString;
       if(countsFile.eof()) break;
       if(inString == sWordtag)
       {
	   countsFile >> inJunk >> inJunk;
	   continue;
       } 
       if(inString == sUnigram)
       {
	   countsFile >> inJunk;
	   continue;
       }
       //CHANGE TO SELECT CASE
       if(inString == sDigram)
       {
	    countsFile >> inDigram[0] >> inDigram[1];
	    digramCounts[inDigram] = inCount;
       }
       if(inString == sTrigram)
       {
	    countsFile >> inTrigram[0] >> inTrigram[1] >> inTrigram[2];
	    trigramCounts[inTrigram] = inCount;
       }
   }
   countsFile.close();


   map<vector<string>, double> qParameter;

   typedef map<vector<string>, int>::const_iterator pIter;
   for(pIter p = trigramCounts.begin(); p != trigramCounts.end(); ++p)
   {
	vector<string> currentTrigram = p->first;
        vector<string> currentDigram(2,"");
        currentDigram[0] = currentTrigram[0];
        currentDigram[1] = currentTrigram[1];
        qParameter[currentTrigram] = ((double) trigramCounts[currentTrigram])/((double) digramCounts[currentDigram]);

   }

   return qParameter;
}
