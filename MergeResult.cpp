//This script merge result file
// usage:  g++ MergeResult.cpp -o MergeResult
// ./MergeResult coverageResult coverageResult.txt
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <sstream>
#include <stdlib.h>
using namespace std;

int main(int argc, char *argv[])
{
int OpenFile(FILE **filePoint, string fileInput);
void CloseFile(FILE **filePoint);
int checkFile(ifstream &input); 
void printMatrix(vector <vector <string> > &dad);
int fileToData (string filenameDIR,vector <vector <string> > &data);


//get list of file
DIR *dir;
struct dirent *ent;
string dirname= argv[1];
char const* ca = dirname.c_str();
string token;
vector <vector <string> > data2;
vector <string> filename;
int flag = 0;
if ((dir = opendir (ca)) != NULL) {
	/* print all the files and directories within directory */
	while ((ent = readdir (dir)) != NULL) {
 		string filenameDIR=dirname+"/"+ent->d_name;
 		token = ent->d_name;
 		if(token.substr(0,1)==".")continue;
 		filename.push_back(token);
		vector <vector <string> > data;
		
		fileToData(filenameDIR,data);
		
		//make data2 matrix
		if(flag==0){
			vector <string> tempName;
			for (int i=0;i< data.size();i++){
				tempName.push_back(data[i][0]);
			}
			data2.push_back(tempName);
		}
		flag = 1;
		vector <string> tempValue;
		for (int i=0 ; i <  data.size();i++){
			tempValue.push_back(data[i][2]);
		}
		data2.push_back(tempValue);
		
	
  	}//while
  closedir (dir);

} else {
  /* could not open directory */
  perror ("");
  return EXIT_FAILURE;
}//if


//make file
//file for result
ofstream myfile;
myfile.open (argv[2]);
myfile << "genome ";
for (int i=0; i<filename.size();i++){
		
	vector <string> record;
	istringstream ss (filename[i]);
	while (ss)
	{
		string s1;
		if(!getline(ss,s1,'_')) break;
		if(s1!=""){
			record.push_back(s1);
		}
	}
	myfile <<  record[0]+" ";
}
myfile << "\n";
for(int i=0;i<data2[0].size();i++){
	for (int j=0;j<data2.size();j++){
		myfile <<data2[j][i]+" ";
	}
	myfile << "\n";
}

myfile.close();

return 0;
}
//this is end of main

// open file for reading
int OpenFile(FILE **filePoint, string fileInput)
{
    const char *file = fileInput.c_str();
    *filePoint = fopen (file,"r");
    
    if (filePoint == NULL){
    	printf ("File could not be opened\n");
    }else{
    	printf ("File opened\n");
    }
	return 0;
}

// close file
void CloseFile(FILE **filePoint)
{
	fclose(*filePoint); 	
}

//check file
int checkFile(ifstream &input)
{
	if(input.fail()){                           //    Check open
       cerr << "Can't open file\n";
       exit(EXIT_FAILURE);
       //return 1;
	}else{return 0;}
}

//print matrix
void printMatrix(vector <vector <string> > &dad){
	for (int i=0;i<dad.size();i++){
		for (int j=0;j<dad[i].size();j++){
			cout<<dad[i][j]+" "<<flush;
		}
	cout<<endl<<flush;
	}
}

//file contents to data-vector
int fileToData (string filenameDIR,vector <vector <string> > &data){
	char const* fin = filenameDIR.c_str();
	ifstream input;
	string s;
	input.open(fin);
	checkFile(input);
	while(getline(input,s))
	{
		istringstream ss (s);
		//this add data into the column (second number)
		vector <string> record;
		while (ss)
		{
			string s1;
			if(!getline(ss,s1,' ')) break;
			if(s1!=""){
				record.push_back(s1);
			}
		}
		//this add data into the row (first number)
		data.push_back(record);
	}//while
	input.close();
	return 0;
}