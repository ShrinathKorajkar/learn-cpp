#include <iostream>
#include "musicPlayer.hpp"

void startPlaylist(PlayLists &manager)
{
    MusicPlayer player(manager);
    player.startPlaying();
}

void startMusicPlayer(PlayLists &manager, const int &choice)
{
    switch (choice)
    {
    case 1:
        std::cout << "\n\n";
        printHeading("CREATE PLAYLIST");
        manager.createPlaylist();
        std::cout << DOTTEDLINE << DOTTEDLINE;
        std::cout << "\n\n";
        break;
    case 2:
        std::cout << "\n\n";
        printHeading("PLAY SONGS");
        startPlaylist(manager);
        std::cout << DOTTEDLINE << DOTTEDLINE;
        std::cout << "\n\n";
        break;
    case 3:
        std::cout << "\n\n";
        printHeading("EDIT PLAYLIST");
        manager.editPlaylist();
        std::cout << DOTTEDLINE << DOTTEDLINE;
        std::cout << "\n\n";
        break;
    case 4:
        std::cout << "\n\n";
        printHeading("DELETE PLAYLIST");
        manager.deletePlaylist();
        std::cout << DOTTEDLINE << DOTTEDLINE;
        std::cout << "\n\n";
        break;
    case 5:
        break;
    default:
        printError("INVALID CHOICE !... Please Enter 1, 2, 3, 4 or 5");
        std::cout << "\n\n";
    }
}

int main()
{
    PlayLists manager;
    int choice = 0;
    do
    {
        printHeading("MUSIC PLAYER");
        std::cout << "1. Create Playlist" << std::endl;
        std::cout << "2. Start Playlist" << std::endl;
        std::cout << "3. Edit Playlist" << std::endl;
        std::cout << "4. Delete Playlist" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << DOTTEDLINE;
        std::cout << "Enter Your Choice : ";

        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("INAVALID CHOICE !... Please Enter 1, 2, 3, 4 or 5\n\n");
            continue;
        }
        startMusicPlayer(manager, choice);
    } while (choice != 5);

    std::cout << DOTTEDLINE;
    std::cout << DOTTEDLINE << std::endl;
    return 0;
}
