// Jacob Kutch - w963538
// CSC 317
// 2/4/19
// references: geeksforgeeks.org; cppreference.com; 
			//cplusplus.com; stackoverflow.com

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	ifstream input;  //creates input stream
	input.open("hw1_input.txt"); //specifies input with a specific file
	//istringstream stringContainer(textFile);
	string textFile(istreambuf_iterator<char>(input), (istreambuf_iterator<char>()));
		//stream iterators used to traverse the file
		//text from file written into textFile
	input.close();
	
	/*for(string::iterator str_itt = textFile.begin(); str_itt < textFile.end(); str_itt++) 
	{
		if(*str_itt == ('.'|','|'?'|'!'|':'|';'|'"'|'\''|'/'))
				textFile.erase(remove(textFile.begin(), textFile.end(), *str_itt));
	}*/
	
	// following line modified from Stack Overflow post
	textFile.erase(remove(textFile.begin(), textFile.end(), 
					(','|'.'|'?'|'!'|':'|';'|'"'|'/'|'\''))); 
		//<algorithm> function that traverse the string and delete punctuation
	 
	istringstream stringInput(textFile); //istringstream object holding contents of textFile
	
	vector<string> fileVector; //vector of strings

	while (stringInput >> textFile) //while the input has not reached the end of stream
		fileVector.push_back(textFile);	//adds words to vector one at a time

	set<string> setString; //creates a <set> of strings
	
	for(vector<string>::iterator vector_itt = fileVector.begin(); vector_itt != fileVector.end(); vector_itt++)
		setString.insert(*vector_itt); //traverses vector and adds words to set. set discards duplicates
	
	map<string, int> fileMap; //creates <map> of strings to be the keys and numbers to be values
	
	//following algorithm taken from geeksforgeeks.org
	for(set<string>::iterator set_itt = setString.begin(); set_itt != setString.end(); set_itt++)
	{	
		int count = 0; //turns back to 0 before next pass
		for(vector<string>::iterator set_itt2 = fileVector.begin(); set_itt2 != fileVector.end(); set_itt2++)
		{	//needed second set iterator for nested loop
			if(*set_itt == *set_itt2)
				count = count + 1; //count increments into the new value for the map
		}
		fileMap[*set_itt] = count; //new value of map[i]
	}
	
	ofstream output; //creates output stream
	output.open("hw1_output.txt"); //creates file
	
	for(map<string, int>::iterator map_itt = fileMap.begin(); map_itt != fileMap.end(); map_itt++)
		output << (map_itt -> first) << "\t-\t" << (map_itt -> second) << endl;
		//writes to output file

  return 0;
}



/*
 * std::istream get(streambuf& sb) - extracts characters from the string
 * and inputs them into the output sequence controlled by the stream buffer
 * object sb, stopping as soon as such an insertion fails or end of file is reached
 * Only characters successfully inserted into sb are extracted from the stream
 */
//After using this function, call member gcount to access number of chars read and stored

/*
  std::streamsize - defined in <ios> - represents the number of characters
  transferred in an I/O operation or size of I/O buffer.
  use after putting file in stream buffer
 */
