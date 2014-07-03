//function for Part I of HW 1
//function for Part I of HW 1
//in Natural Language Processing course
//Cecilia Aas June 2014

#include <fstream>
#include <string>
#include <vector>
#include <map>

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



