#include <iostream>
#include <string>
#include "Playlist.h"

using namespace std;

int main() {
  string pName;
  cout << "Enter playlist's title:" << endl;
  getline(cin, pName);
  cout << endl;
  Playlist *playlistA = new Playlist();
  playlistA->PrintMenu(pName);

  return 0;
}
