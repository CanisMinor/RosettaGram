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

using namespace std;


map<string, int> wordCounts(const string sInFile)
{
   const string sWordtag = "WORDTAG";
   map <string, int>  wordCounts;  
   int nCount = 0;
   string inString, inLabel, inWord;

   ifstream inCount;
   inCount.open(sInFile.c_str());
   while(inCount.good())
   {
      inCount >> nCount >> inString;
      if(inCount.eof()) break;
      if(inString == sWordtag)
      {
         inCount >> inLabel >> inWord;
	 wordCounts[inWord] += nCount;  
      }
      else
      {
         break;
      }
   }
   inCount.close();

   return wordCounts;
}


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


int main()
{
   const string inFile = "geneRare.counts";
   map<vector<string>, double> e = emissionParameters(inFile);

   ofstream outCounts;
   outCounts.open("gene_count.pl.out");
   typedef map<vector<string>, double>::const_iterator pIter;
   for(pIter p = e.begin(); p!=e.end(); ++p)
   {
       vector<string> inP = p->first;
       outCounts << inP[0] << "\t" << inP[1] << "\t" << p->second << endl;
   }
   outCounts.close();


   map<string, string> maxEmit = findMaxEmission(e);
   ofstream maxCounts;
   ifstream testFile;
   testFile.open("gene.dev");
   maxCounts.open("gene_dev.pl.out");
   string inWord, inJunk;
   const string sRare = "_RARE_";
   const string sDot = ".";
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
   return 0;
}


/*

double evalFrequencies()
{
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

*/
