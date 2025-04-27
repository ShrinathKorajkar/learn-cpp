#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>
#include <map>
#include <SFML/Audio.hpp>
#include <SFML/Window/Event.hpp>

#define DOTTEDLINE "-------------------------------------------------\n"
#define PLAYLISTS_PATH "./assets/playlists/"
#define MUSIC_PATH "./assets/music/"

#include "musicPlayer.hpp"

void printError(const char *message);

void printHeading(const std::string heading);

class PlayLists
{
    std::list<std::string> allSongs;
    std::map<std::string, std::list<std::string>> allPlaylists;

protected:
    void replaceChar(std::string &strToChange, const char &old, const char &replacement);
    virtual void showAllSongs();
    void addSongsToNewPlaylist(const std::string &playlistName);
    void removeSongsFromPlaylist(const std::string &playListName);
    void moveSongUpDownInPlaylist(const std::string &playListName);
    virtual void modifyPlaylist(const std::string &playlistName);

public:
    PlayLists();
    bool playListExists(const std::string &playListName);
    void createPlaylist();
    int showAvailablePlaylists();
    void editPlaylist();
    void deletePlaylist();
    std::list<std::string> getPlaylist(const std::string &playListName);
};

class MusicPlayer
{
    PlayLists *manager;

protected:
    void replaceChar(std::string &strToChange, const char &old, const char &replacement);
    virtual void displayUserGuidelines();
    virtual void playSongs(const std::list<std::string> &playList);

public:
    MusicPlayer(PlayLists &manager) : manager(&manager) {}
    void startPlaying();
};

#endif // !MUSIC_PLAYER_H