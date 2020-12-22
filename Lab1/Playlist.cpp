#include <iostream>
#include "Playlist.h"

using namespace std;

PlaylistNode::PlaylistNode(){
  uniqueID = "none";
  songName = "none";
  artistName = "none";
  songLength = 0;
  nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string ID, string sName, string aName, int length){
  uniqueID = ID;
  songName = sName;
  artistName = aName;
  songLength = length;
  nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode *Node){
  //set temporary Node pointer to nextNodePtr 
  PlaylistNode *tempNode = nextNodePtr;
  //set nextNodePtr to node user wants to insert
  nextNodePtr = Node;
  //set new next node's next pointer to old next node 
  Node->SetNext(tempNode);
}

void PlaylistNode::SetNext(PlaylistNode *nextNode){
  this->nextNodePtr = nextNode;
}

string PlaylistNode::GetID() const{
  return uniqueID;
}

string PlaylistNode::GetSongName() const{
  return songName;
}

string PlaylistNode::GetArtistName() const{
  return artistName;
}

int PlaylistNode::GetSongLength() const{
  return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const{
  return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode(){
  cout << "Unique ID: " << uniqueID << endl;
  cout << "Song Name: " << songName << endl;
  cout << "Artist Name: " << artistName << endl;
  cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::Playlist(){
  head = nullptr;
  tail = nullptr;
}

void Playlist::PrintMenu(string pName){
  cout << pName << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl << endl;
  cout << "Choose an option:" << endl;
  string userInput;
  getline(cin, userInput);
  if(userInput == "q"){ //user wants to quit
    return; //do nothing
  }
  else if(userInput == "a"){
    string ID;
    string name;
    string artist;
    int length;
    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    getline(cin, ID);
    cout << "Enter song's name:" << endl;
    getline(cin, name);
    cout << "Enter artist's name:" << endl;
    getline(cin, artist);
    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    cin.ignore(); //ignores \n from buffer
    PlaylistNode *newSong = new PlaylistNode(ID, name, artist, length);
    push_back(newSong);
    cout << endl;
    PrintMenu(pName); //prints menu again for new userInput
  }
  else if(userInput == "d"){
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    string ID;
    getline(cin, ID);
    PlaylistNode *rem = remove(ID);
    if(rem){
      cout << '"' << rem->GetSongName() << '"' << " removed." << endl;
    }
    else{
      cout << "Song with unique ID " << ID << " not found!" << endl;
    }
    cout << endl;
    PrintMenu(pName);
  }
  else if(userInput == "c"){
    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's current position:" << endl;
    int currPos;
    int newPos;
    cin >> currPos;
    cin.ignore();
    cout << "Enter new position for song:" << endl;
    cin >> newPos;
    cin.ignore();
    changeSongPos(currPos, newPos);
    cout << endl;
    PrintMenu(pName);
  }
  else if(userInput == "s"){
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    string artistName;
    getline(cin, artistName);
    songsFromArtist(artistName);
    PrintMenu(pName);
  }
  else if(userInput == "t"){
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    cout << "Total time: " << totalTime() << " seconds" << endl;
    cout << endl;
    PrintMenu(pName);
  }
  else if(userInput == "o"){
    outputFullPlaylist(pName);
    PrintMenu(pName);
  }
  else{ //invalid input
    cout << "Invalid Selection." << endl;
    PrintMenu(pName); //recursion, prompts to menu options again
  }

}

void Playlist::push_back(PlaylistNode *newNode){
   if(head == nullptr){ //if empty, if one, if many
        head = newNode;
        tail = newNode;
    }
    else{
        tail->SetNext(newNode); //set tail's next node to newNode
        tail = newNode; //last element of playlist is now newNode
    }
}

PlaylistNode* Playlist::remove(string ID){ //option d
  PlaylistNode *before = nullptr;
  PlaylistNode *curr = head;
  while(curr != nullptr && curr->GetID() != ID){ //finding correct 
    before = curr;                               //nodes in playlist
    curr = curr->GetNext();
  }
  if(curr != nullptr){ 
    if(before != nullptr){ //removing node in middle of playlist
      before->SetNext(curr->GetNext());
    }
    else{ //removing head
      head = curr->GetNext();
    }
    if(curr->GetNext() == nullptr){ //removing tail
      tail = before;
    }
    return curr;
  }
  else{
    return nullptr;
  }
}

void Playlist::changeSongPos(int currPos, int newPos){
  if(currPos < 1){
    cout << "Invalid current position." << endl;
    return;
  }
  int nodeCounter = 1;
  PlaylistNode *before = nullptr;
  PlaylistNode *currNode = head;
  while(nodeCounter < currPos){ //move pointers to right positions
    if(currNode != nullptr){ //shifts pointers one node at a time
      before = currNode;
      currNode = currNode->GetNext();
      nodeCounter++;
    }
    else{ //currPos given as paramerter is > number of nodes
      cout << "Invalid current position." << endl;
      return;
    }
  }
 if(before != nullptr){ //removing current node, making before point 
   before->SetNext(currNode->GetNext()); //to one after current Node
 }
 else{ //if currPos is first node
   head = currNode->GetNext();
 }
if(newPos <= 1){ //moving node to position 1 (head)
  if(head == nullptr){ //if empty playlist
    tail = currNode; 
  }
  currNode->SetNext(head); 
  head = currNode; //new head is now current node
  cout << '"' << currNode->GetSongName() << '"' << " moved to position 1" << endl; 
}
else{ //moving to position somewhere in middle
  int newSongPos = 2;
  PlaylistNode *previousNode = head;
  PlaylistNode *afterNode = head->GetNext();
  while(newSongPos < newPos && afterNode != nullptr){ //shifts 2 pointers 
    previousNode = afterNode;                         //one at a time
    afterNode = afterNode->GetNext();
    newSongPos++; //keeps track of song number
  }
  currNode->SetNext(previousNode->GetNext()); //changes positions of songs
  previousNode->SetNext(currNode); //changes positions of songs
  if(afterNode == nullptr){ //new position is at tail
    tail = currNode;
  }
cout << '"' << currNode->GetSongName() << '"' << " moved to position " << newSongPos << endl;
}
if(currNode == tail){ //removing original tail (last node = curr node)
  tail = before; //new tail is now node before original tail
}
}

void Playlist::songsFromArtist(string artist){
  int songCount = 1;
  PlaylistNode *currNode = head;
  while(currNode){
    if(currNode->GetArtistName() == artist){
      cout << songCount << "." << endl;
      currNode->PrintPlaylistNode();
      cout << endl;
    }
    else{
      currNode = currNode->GetNext();
      songCount++;
    }
  }
}


int Playlist::totalTime(){
  PlaylistNode *currNode = head;
  int sum = 0;
  while(currNode){
    sum += currNode->GetSongLength();
    currNode = currNode->GetNext();
  }
  return sum;
}

void Playlist::outputFullPlaylist(string pName){
  cout << pName << " - OUTPUT FULL PLAYLIST" << endl;
  if(head == nullptr){ //if playlist is empty
    cout << "Playlist is empty" << endl << endl;
  }
  else{
    int songCount = 1; //count begins with 1, not 0
    PlaylistNode *currNode = head;
    while(currNode){
      cout << songCount << "." << endl; //print song number
      currNode->PrintPlaylistNode(); //print song details
      cout << endl;
      songCount++; //increase counter each time while loop repeats
      currNode = currNode->GetNext(); //go to next node
    }

  }
}

