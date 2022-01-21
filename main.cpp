//
//  Project 1 Starter Code - DNA Profiling
//  TODO:  Put your header info here.  Update line above.
//  
//

#include "ourvector.h"
#include <iostream> // to read user input and also output
#include <string>
#include <vector>
#include <fstream>  // to read files
#include <sstream> // to read strings

using namespace std;

struct info {
  ourvector<string> name;
  ourvector<string> dna;
};

struct strs {
    ourvector<string> name;
    int number;
};

//-----------------------------------------------------------------------
/*removeComma will remove all commas from the string taken in and also count its dna strands.
The string will be updated along with its dna size*/
void removeComma(string& theString, int& dnaSize)
{
     for(char& b : theString)
     {
         if(b == ',' )
         {
             b = ' ';
             dnaSize++;
         }
     }
 }
 
/*loadDB will take in 3 paremeters that will assist in reading a files contents and sorting them into two differnt vectors
 the topVec will take in only the top line of the file and the infoVec will take in the rest of the file's lines, these 
 vectors will be of type string so each string will correspond to a line in the file aka a persons data. This function will 
 not return anything, instead, it will just update a vector that was passed to it with contents.*/
void loadDB(string fileName, ourvector<string>& infoList, ourvector<string>& topVec)
{
    int dnaSize = 0;
    string nombre;
    ifstream inFS;      //the File Stream !
    string indivualsName;
    string theString;
    
   cout << "Loading database..." << endl;
   inFS.open(fileName); 
   
   if (!inFS.is_open())
   {
      cout << "Error: unable to open "<< "'" << fileName << "'" << endl;
      return;
   }
   inFS >> theString;          //for the topVec
   removeComma(theString, dnaSize);  
   topVec.push_back(theString);
   theString.clear();
   dnaSize = 0;

   inFS >> theString;   //for the infoList vector
   while (!inFS.fail())
   {
       removeComma(theString, dnaSize); // passes the current string and updates it with no commas
       infoList.push_back(theString);
       theString.clear();
       dnaSize = 0;
       inFS >> theString;   //reads in next string char
   }
    if (!inFS.eof()) 
    {
      cout << "Input failure before reaching end of file." << endl;
    }
   inFS.close();
}
/*SVprinterHelper will take in a single string and print it.*/
void SVprinterHelper(string& theString){
    string nombre;
    istringstream inSS(theString);      // Input string stream
    
       inSS >> nombre;
       cout << "Name: " << nombre << "      ";
       
       int dnaSize = 0;
       for(char& b : theString){
           if(b == ' '){
               dnaSize++;
           }
       }
     string dnas;
     
     for(int d = 0; d < dnaSize; d++){

         inSS >> dnas;
         cout << "dna: " << dnas << ",";
         dnas.clear();
       
     }
     cout << endl;
 }
/*SVprinter will ultimtley print the contents of the vector taken in.
This function was used to print the list of strings that each represnt a person. 
This function uses a helper function that is the leaf component that actaully 
prints the given string char by char*/
void SVprinter(ourvector<string>& infoList){
    for(string& s : infoList){
        SVprinterHelper(s);
    }
    //return;
}
/*intoStruct copies a regular vector into a structed vector whose type is of a struct.
The struct type has a name and a dna vector within it. The data from the regular vector
is sorted and moved into those spaces. One string from the regular vector will correspond 
to one block in the vector of structs.*/
void intoStruct(ourvector<string>& infoList, ourvector<info>& structList)
{
    for(string& g : infoList)
    {
    istringstream inSS(g);
    info person;
    string thename;
    inSS >> thename;
    for(char& n : thename){
      stringstream stream;
      stream << n;
      string c;
      stream >> c;
      person.name.push_back(c);
    }
    
    int spacecounter = 0;
    for(char& k : g)
    {
        if(k == ' ')
        {
            spacecounter++;
        }
    }
    string dnas;

    for(int b = 0; b < spacecounter; b++)
    {
        inSS >> dnas;
        person.dna.push_back(dnas);
        dnas.clear();
    }
    structList.push_back(person);
    }
    
    //cout << "info is in list of structs" << endl;
    //return;
}
/*structPrinter will print the special vector with dna and name components for each member*/
void structPrinter(ourvector<info>& structList){
    
    for(info& o : structList){
        for(string& g : o.name){
          cout << g ;
        }
        for(string& v : o.dna){
            cout << " " << v;
        }
        cout << endl;
    }
    //return;
}
/*loadDNA will read the dna file into a vector of type string. Each string will rep char*/
void loadDNA(string fileName, ourvector<string>& DNA)
{    
    ifstream inFS;
    string theString;
    
    cout << "Loading DNA..." << endl;
    inFS.open(fileName); 
   
   if (!inFS.is_open()) 
   {
      cout << "Error: unable to open "<< "'" << fileName << "'" << endl;
      return;
   }
   inFS >> theString;
   for(char& f : theString) 
   {
      stringstream stream;  //from char to string
      stream << f;
      string current;
      stream >> current;
       DNA.push_back(current);
   }
}
bool isEmpty(string& DNA){
  if(DNA.empty()){
    return true;
  }
  return false;
}

bool match(ourvector<string>& DNA, string& strain, int index, ourvector<strs>& strsStruct){
for(char& d : strain){
  stringstream stream;
  stream << d;
  string p;
  stream >> p;
if(isEmpty(DNA[index]) == true){
  return false;
}
if(p != DNA[index]){
  return false;
}
index++;
}
return true;
}

void compareStrings(string& strain, ourvector<string>& DNA, ourvector<strs>& strsStruct){
int count = 0;
strs newstr;

for(char& s : strain){
//cout << " char in strain: " << s << endl;
stringstream astream;
      astream << s;
      string g;
      astream >> g;
newstr.name.push_back(g);
}
  //cout << "DNA size: " << DNA.size() << endl;
  //cout << "last char in dna: " << DNA[DNA.size() - 1] << endl;
  for(int c = 0; c < DNA.size() - 2 ; c++){     //runs through DNA

    stringstream stream;  
    stream << strain.at(0); 
    string b;
    stream >> b;
    //cout << "dna index c: " << c << endl;
    
    //if(isEmpty(DNA[c]) != true) {
    
    if(DNA[DNA.size() - 1].empty() == false ){
        
    if (DNA[c] == b){
      
      int index = c;
      if(match(DNA, strain, index, strsStruct) == true){
        count++;
       
         c = c + strain.size() - 1 ;
         //cout << "MATCH adding c: " << c << endl;
         if(c > DNA.size()){
           newstr.number = count;
           strsStruct.push_back(newstr);
           return;
         }
      }
    }
    }
   
    
  }
  newstr.number = count;
strsStruct.push_back(newstr);
}
 /* I will save each strain in a list and for each strain I 
 will call a function that compares it to the DNA vector of strings */
void processDNA(ourvector<string>& DNA, ourvector<info>& structTop, ourvector<strs>& strsStruct) {
  ourvector<string> strchars;
  int c = 0;

  cout << "Processing DNA..." << endl;
  for(info& i : structTop){
    c++;
    //cout << "block: " << c << endl;
    for(string& s : i.dna){
      strchars.push_back(s);  //string of dna strands
      //cout << " s going into vector of strings, strchars: " << s << endl;
    }
    for(string& strain : strchars){ //for each strand
   // cout << "for each strain, call compare strings: " << strain << endl;
      compareStrings(strain, DNA, strsStruct); //will take starin by strain and compare to the dna string
      //Will return strsStruct, a vector with counts correspoding to each dna strand
     // cout << "done comparing little str with dna" << endl;
    }
  }
}

void printSTR(ourvector<strs>& strsStruct){
  for(strs& s : strsStruct){
    for(string& t : s.name){
      cout << t;
    }
    cout << ": " ;
    cout << s.number << endl;
  }
}

int main() {
    //TODO:  Write your code here.  You should have LOTS of function decomposition.
    ourvector<string> infoList;
    ourvector<string> topVec;
    ourvector<info> structList;
    ourvector<info> structTop;
    string userOption;
    string fileName;
    bool over = false;
    string response;
    ourvector<string> DNA;
    ourvector<strs> strsStruct; 
    
    
    cout << "Welcome to the DNA Profiling Application." << endl << endl;
    
    while(!over)
    {
    cout << "Enter command or # to exit: " << endl << endl;
    cout << "load_db" << "  -databasefile-" << endl;
    cout << "load_dna" << " -dna file-" << endl;
    cout << "process" << endl;
    cout << "display" << endl;
    getline(cin, response);
    //cout << response;
    for(char& t : response)
    {
        if(t == ' ')
        {
            istringstream inSS(response);
            inSS >> userOption;
            inSS >> fileName;
        }
        else
        {
            istringstream inSS(response);
            inSS >> userOption;
        }
    }
  
      if (userOption=="#")
      {
        over = true;
      }
    
       if(userOption == "load_db")
       {
          loadDB(fileName, infoList, topVec);   //Loads first line of file in one vector and the rest of the lines in infoList
          //SVprinter(infoList);
          intoStruct(topVec, structTop);       //Puts the first line from the file into a structed vector topVec
          intoStruct(infoList, structList);     //Puts rest of file in structed vector structList
          //structPrinter(structList);
       }
      if(userOption == "load_dna")
      {
          loadDNA(fileName, DNA);   //Pets the DNA string of chars in a vector of type string
      }
      if (userOption == "process") 
      {
          //cout << " userOption is Process. " << endl;
          processDNA(DNA, structTop, strsStruct);    //needes to count the dna strings found in the dna file, so must return a vector of strains with there number of appearences, best for a structed vector
          //cout<< "done with process" << endl;
      }
       if(userOption == "display")
       {
           if(structList.size() != 0)
           {
          cout << "Database loaded: " << endl;
          //structPrinter(structTop);
          structPrinter(structList);
          cout << endl;
           }
           else
           {
               cout << "No database loaded." << endl << endl;
           }
           if(DNA.size() != 0)
           {
               cout << "DNA loaded: " << endl;
               for(string& g : DNA)
               {
                    cout << g;
               }
                cout << endl << endl;
                //cout << "No DNA has been processed." << endl;
           }
           else{
             cout << "No DNA loaded." << endl << endl;
           }
           if(strsStruct.size() != 0){
             cout << "DNA processed, STR counts: " << endl;
             printSTR(strsStruct);
             cout << endl;
           }
           else 
           {
                cout << "No DNA has been processed." << endl;
           }
       }
        
    }    
    
    return 0;
}