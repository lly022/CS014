#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>

using namespace std;

class PlaylistNode{
  private: 
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode *nextNodePtr;
  public:
    PlaylistNode();
    PlaylistNode(string, string, string, int);
    void InsertAfter(PlaylistNode*);
    void SetNext(PlaylistNode*);
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void PrintPlaylistNode();

};

class Playlist{
  private:
    PlaylistNode *head;
    PlaylistNode *tail;
  public:
    Playlist();
    void PrintMenu(string);
    void push_back(PlaylistNode*);
    PlaylistNode* remove(string);
    void changeSongPos(int, int);
    void songsFromArtist(string);
    int totalTime();
    void outputFullPlaylist(string);
};

#endif
