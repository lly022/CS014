#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
  hashTable = new list<WordEntry>[s];
	size = s;
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
  unsigned int hashVal = 0;
  for(unsigned int i = 0; i < s.size(); ++i){
    hashVal += (hashVal << 5) + s.at(i);
  }
  return hashVal % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score){
 list <WordEntry> *ListAt = hashTable + computeHash(s);
 if(contains(s)){
   list <WordEntry> :: iterator it;
   for(it = ListAt->begin(); it != ListAt->end(); ++it){
     if(s == it->getWord()){
       it->addNewAppearance(score);
     }
   }
 }
 else{
   WordEntry newWordEntry(s, score);
   ListAt->push_back(newWordEntry);
 }
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
  double average = 2.0;
  if(contains(s)){
    list <WordEntry> :: iterator it;
    list <WordEntry> *ListAt = hashTable + computeHash(s);//gets list in hashTable array using array/pointer arithmetic(adding int(index) from computeHash() to start of array)
    for(it = ListAt->begin(); it != ListAt->end(); ++it){
      if(s == it->getWord()){
        average = it->getAverage();
      }
    }
  }
  return average;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
  bool foundWord = false;
	list <WordEntry> :: iterator it; 
  list <WordEntry> *ListAt = hashTable + computeHash(s);//gets list in hashTable array using array/pointer arithmetic(adding int(index) from computeHash() to start of array)
  if(!(ListAt->empty())){
    for(it = ListAt->begin(); it != ListAt->end(); ++it){
      if(s == it->getWord()){
        foundWord = true;
      }
    }
  }
  return foundWord;
}
