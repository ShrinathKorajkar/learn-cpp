#include "musicPlayer.hpp"

void printError(const char *message)
{
    if (message != nullptr)
    {
        std::cout << std::endl;
        std::cout << message << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();
}

void printHeading(const std::string heading)
{
    std::cout << std::endl;
    std::cout << DOTTEDLINE;
    std::cout << DOTTEDLINE;
    int desiredLength = 44;
    int headingLength = heading.length();
    if (headingLength < 45)
    {
        int fillLength1 = (desiredLength - headingLength) / 2 - 1;
        int fillLength2 = (desiredLength - headingLength) / 2;
        if (headingLength % 2 != 0)
        {
            fillLength1++;
        }
        std::string fill1(fillLength1, ' ');
        std::string fill2(fillLength2, ' ');
        std::cout << "---" << fill1 << heading << fill2 << "---" << std::endl;
    }
    else
    {
        std::cout << heading << std::endl;
    }
    std::cout << DOTTEDLINE;
}

void PlayLists::replaceChar(std::string &strToChange, const char &old, const char &replacement)
{
    for (char &c : strToChange)
    {
        c = c == old ? replacement : c;
    }
}

void PlayLists::showAllSongs()
{
    if (allSongs.size() == 0)
    {
        std::cout << "There are no songs available in " << MUSIC_PATH << std::endl;
        return;
    }
    int count = 1;
    for (std::string song : allSongs)
    {
        replaceChar(song, '_', ' ');
        std::cout << count++ << " : " << song << std::endl;
    }
}

void PlayLists::addSongsToNewPlaylist(const std::string &playlistName)
{
    int noOfSongs = allSongs.size();
    if (noOfSongs > 0)
    {
        std::string filePath = PLAYLISTS_PATH + playlistName + ".txt";
        std::list<std::string> playListToAdd;
        if (std::filesystem::exists(filePath))
        {
            playListToAdd = allPlaylists[playlistName];
        }
        std::ofstream playList(filePath, std::ios::app);
        std::set<std::string> listOfSongsToAdd(playListToAdd.begin(), playListToAdd.end());
        std::cout << "Enter song number you want to add 0 to exit" << std::endl;
        std::cout << std::endl;
        int songNoToAdd = -1;
        do
        {
            std::cout << "Song No : ";
            std::cin >> songNoToAdd;
            if (std::cin.fail())
            {
                printError("Invalid Input !... Enter Song Number");
                std::cout << std::endl;
                songNoToAdd = -1;
                continue;
            }
            if (songNoToAdd > noOfSongs)
            {
                std::cout << "\nInvalid Song Number !.. Please enter in range 1 - " << noOfSongs << std::endl;
            }
            else if (songNoToAdd != 0)
            {
                auto iterator = allSongs.begin();
                std::advance(iterator, songNoToAdd - 1);
                std::string song = *iterator;
                if (listOfSongsToAdd.count(song) == 1)
                {
                    std::cout << "Already added" << std::endl;
                }
                else
                {
                    listOfSongsToAdd.insert(song);
                    playListToAdd.push_back(song);
                    playList << song << std::endl;
                    replaceChar(song, '_', ' ');
                    std::cout << "Song : \"" << song << "\" added to playlist" << std::endl;
                }
            }
            std::cout << std::endl;
        } while (songNoToAdd != 0);
        std::cout << "Pressed 0 ... going back" << std::endl;
        allPlaylists[playlistName] = playListToAdd;
        playList.close();
    }
}

void PlayLists::removeSongsFromPlaylist(const std::string &playListName)
{
    std::list<std::string> playList = allPlaylists[playListName];
    while (true)
    {
        if (playList.size() == 0)
        {
            std::cout << "\nPlaylist is Empty!" << std::endl;
            break;
        }
        std::cout << "Contents of Playlist" << std::endl;
        std::cout << std::endl;
        int count = 0;
        for (std::string song : playList)
        {
            std::cout << count + 1 << " : " << song << std::endl;
            count++;
        }
        int songNoToDelete;
        std::cout << DOTTEDLINE;
        std::cout << "Enter Song Number to Delete / 0 to Go Back: ";
        std::cin >> songNoToDelete;
        if (std::cin.fail())
        {
            printError("Invalid Input!... Choose Song number");
            std::cout << "\n\n";
            continue;
        }

        if (songNoToDelete > playList.size())
        {
            std::cout << "\nIncorrect Song Number choose between 1 - " << playList.size() << std::endl;
            std::cout << "\n\n";
            continue;
        }

        if (songNoToDelete == 0)
        {
            break;
        }
        auto iterator = playList.begin();
        std::advance(iterator, songNoToDelete - 1);
        playList.erase(iterator);
        std::cout << "\nDeleted Successfully\n\n";
        std::cout << DOTTEDLINE;
    }
    allPlaylists[playListName] = playList;
    std::cout << "\nPressed 0 ... going Back" << std::endl;
}

void PlayLists::moveSongUpDownInPlaylist(const std::string &playListName)
{
    std::list<std::string> playList = allPlaylists[playListName];
    while (true)
    {
        if (playList.size() == 0)
        {
            std::cout << "\nPlaylist is Empty!\n";
            return;
        }
        std::cout << "Contents of Playlist : " << std::endl;
        std::cout << std::endl;
        int count = 0;
        for (std::string song : playList)
        {
            replaceChar(song, '_', ' ');
            std::cout << count + 1 << " : " << song << std::endl;
            count++;
        }
        int songNoToMove;
        std::cout << DOTTEDLINE;
        std::cout << "Enter Song Number to Move / 0 to Go Back: ";
        std::cin >> songNoToMove;
        if (std::cin.fail())
        {
            printError("Invalid Input!... Choose Song number");
            std::cout << std::endl;
            std::cout << DOTTEDLINE;
            continue;
        }

        if (songNoToMove > playList.size())
        {
            std::cout << "\nIncorrect Song Number choose between 1 - " << playList.size();
            std::cout << "\n\n";
            std::cout << DOTTEDLINE;
            continue;
        }

        if (songNoToMove == 0)
        {
            break;
        }

        int positionToMove;
        std::cout << "\nEnter Its new Position 1-" << playList.size() << " : ";
        std::cin >> positionToMove;
        if (std::cin.fail())
        {
            printError("Invalid Input!... Choose Number\n");
            std::cout << DOTTEDLINE;
            continue;
        }
        positionToMove = positionToMove < 1 ? 1 : positionToMove;
        positionToMove = positionToMove > playList.size() ? playList.size() : positionToMove;

        auto iterator = playList.begin();
        auto iterator2 = playList.begin();
        if (songNoToMove < positionToMove)
        {
            positionToMove++;
        }
        std::advance(iterator, songNoToMove - 1);
        std::advance(iterator2, positionToMove - 1);
        playList.splice(iterator2, playList, iterator);
        std::cout << "\nOperation Successfull\n\n";
        std::cout << DOTTEDLINE;
    }
    allPlaylists[playListName] = playList;
}

void PlayLists::modifyPlaylist(const std::string &playlistName)
{
    std::string name = playlistName;
    replaceChar(name, '_', ' ');
    int choice = 0;
    do
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "1. Add new Song " << std::endl;
        std::cout << "2. Delete a Song" << std::endl;
        std::cout << "3. Move Song Up/Down" << std::endl;
        std::cout << "4. Save Changes" << std::endl;
        std::cout << DOTTEDLINE;
        std::cout << "Enter choice : ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("Invalid Choice !... Choose between 1 - 4");
            continue;
        }
        switch (choice)
        {
        case 1:
            std::cout << "\n\n";
            std::cout << "ADD NEW SONG" << std::endl;
            std::cout << DOTTEDLINE;
            std::cout << "List of All Songs Available : " << std::endl;
            std::cout << std::endl;
            showAllSongs();
            std::cout << DOTTEDLINE;
            addSongsToNewPlaylist(playlistName);
            std::cout << DOTTEDLINE;
            break;
        case 2:
            std::cout << "\n\n";
            std::cout << "DELETE SONG" << std::endl;
            std::cout << DOTTEDLINE;
            removeSongsFromPlaylist(playlistName);
            std::cout << DOTTEDLINE;
            break;
        case 3:
            std::cout << "\n\n";
            std::cout << "MOVE SONG UP/DOWN" << std::endl;
            std::cout << DOTTEDLINE;
            moveSongUpDownInPlaylist(playlistName);
            std::cout << DOTTEDLINE;
            break;
        case 4:
            break;

        default:
            printError("Invalid Choice !... Choose between 1 - 4");
        }
    } while (choice != 4);

    std::ofstream playList(PLAYLISTS_PATH + playlistName + ".txt");
    std::list<std::string> playListToSave = allPlaylists[playlistName];
    for (auto song : playListToSave)
    {
        playList << song << std::endl;
    }
    playList.close();
    std::cout << "Changes Saved Successfully" << std::endl;
}

PlayLists::PlayLists()
{
    if (!std::filesystem::exists(MUSIC_PATH))
    {
        std::filesystem::create_directory(MUSIC_PATH);
    }
    if (!std::filesystem::exists(PLAYLISTS_PATH))
    {
        std::filesystem::create_directory(PLAYLISTS_PATH);
    }
    for (const auto &file : std::filesystem::directory_iterator(MUSIC_PATH))
    {
        if (file.path().extension() == ".wav")
        {
            std::string fileName = file.path().stem();
            allSongs.push_back(fileName);
        }
    }
    for (const auto &file : std::filesystem::directory_iterator(PLAYLISTS_PATH))
    {
        if (file.is_regular_file())
        {
            std::string fileName = file.path().stem();
            std::ifstream fileStream(file.path());
            std::string songName;
            std::list<std::string> songsInPlaylist;
            while (fileStream >> songName)
            {
                songsInPlaylist.push_back(songName);
            }
            allPlaylists[fileName] = songsInPlaylist;
            fileStream.close();
        }
    }
}

bool PlayLists::playListExists(const std::string &playListName)
{
    bool existsOrNot = false;
    for (auto playList : allPlaylists)
    {
        if (playList.first == playListName)
        {
            existsOrNot = true;
            break;
        }
    }
    return existsOrNot;
}

void PlayLists::createPlaylist()
{
    std::string playlistName;
    std::cin.ignore();
    std::cout << DOTTEDLINE;
    while (true)
    {
        std::cout << "Enter Playlist Name : ";
        std::getline(std::cin, playlistName);

        replaceChar(playlistName, ' ', '_');
        if (playListExists(playlistName))
        {
            std::cout << "\nERROR! : Playlist already exists. Try again...\n\n\n";
            continue;
        }
        break;
    }

    std::cout << DOTTEDLINE;
    std::cout << "List of All Songs Available : " << std::endl;
    std::cout << std::endl;
    showAllSongs();
    std::cout << DOTTEDLINE;

    addSongsToNewPlaylist(playlistName);
}

int PlayLists::showAvailablePlaylists()
{
    if (allPlaylists.size() == 0)
    {
        std::cout << "\nPlaylist are not available. Create one first\n\n";
        return -1;
    }
    for (auto playlist : allPlaylists)
    {
        std::string playlistName = playlist.first;
        replaceChar(playlistName, '_', ' ');
        std::cout << playlistName << std::endl;
    }
    return 0;
}

void PlayLists::editPlaylist()
{
    std::cout << DOTTEDLINE;
    std::cout << "All Available Playlists" << std::endl;
    int result = showAvailablePlaylists();
    if (result == -1)
    {
        return;
    }
    std::cout << DOTTEDLINE;
    std::cin.ignore();

    while (true)
    {
        std::string playListName;
        std::cout << "Enter Name of Playlist to edit : ";
        std::getline(std::cin, playListName);

        replaceChar(playListName, ' ', '_');
        if (playListExists(playListName))
        {
            modifyPlaylist(playListName);
            break;
        }

        std::cout << "\nInvalid Input !... Please enter valid playlist name\n\n";
    }
}

void PlayLists::deletePlaylist()
{
    std::cout << "All Available Playlists" << std::endl;
    int result = showAvailablePlaylists();
    if (result == -1)
    {
        return;
    }
    std::cout << DOTTEDLINE;

    std::string playListName;
    std::cin.ignore();
    while (true)
    {
        std::cout << "Enter Playlist Name to Delete / 0 to go back : ";
        std::getline(std::cin, playListName);
        replaceChar(playListName, ' ', '_');
        if (playListName == "0" && !playListExists(playListName))
        {
            std::cout << "\nOperation Canceled !...\n";
            break;
        }
        if (!playListExists(playListName))
        {
            std::cout << "\nPlaylist Does Not Exist !... Enter Again\n\n\n";
            continue;
        }

        allPlaylists.erase(playListName);
        std::filesystem::remove(PLAYLISTS_PATH + playListName + ".txt");
        std::cout << "\nPlaylist removed successfully\n\n";
        std::cout << DOTTEDLINE;
        std::cout << "Remaining Playlists: " << std::endl;
        showAvailablePlaylists();
        std::cout << DOTTEDLINE;
    }
}

std::list<std::string> PlayLists::getPlaylist(const std::string &playListName)
{
    if (playListExists(playListName))
    {
        return allPlaylists[playListName];
    }
    return std::list<std::string>{};
}

void MusicPlayer::replaceChar(std::string &strToChange, const char &old, const char &replacement)
{
    for (char &c : strToChange)
    {
        c = c == old ? replacement : c;
    }
}

void MusicPlayer::displayUserGuidelines()
{
    printHeading("USER GUIDELINES");
    std::cout << "1. space    -   PLAY/PAUSE" << std::endl;
    std::cout << "2. < or p   -   PREVIOUS" << std::endl;
    std::cout << "3. > or n   -   NEXT" << std::endl;
    std::cout << "4. S or s   -   STOP" << std::endl;
    std::cout << "5. T        -   TOGGLE -> LOOP CURRENT SONG" << std::endl;
    std::cout << "\nPress any key to continue...";
    std::cin.ignore();
    std::cout << DOTTEDLINE << std::endl;
}

void MusicPlayer::playSongs(const std::list<std::string> &playList)
{
    auto iterator = playList.begin();
    int playlistSize = playList.size();
    sf::SoundBuffer soundBuffer;
    sf::Sound song;

    bool playOnLoop = false;
    std::cout << std::boolalpha;

    while (true)
    {
        if (iterator == playList.end())
        {
            iterator = playList.begin();
        }
        std::string currentSong = *iterator;
        replaceChar(currentSong, '_', ' ');
        std::string currentSongPath = MUSIC_PATH + *iterator + ".wav";

        if (!soundBuffer.loadFromFile(currentSongPath))
        {
            std::cout << "\nERROR : unable to load song : \n\n\n!";
            std::cout.flush();
            iterator++;
            continue;
        }

        song.setBuffer(soundBuffer);
        song.play();
        std::cout << "PLAYING : " << currentSong << std::endl;
        bool isSongChanged = false;

        while (song.getStatus() != sf::Music::Stopped)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                if (song.getStatus() == sf::Music::Playing)
                {
                    song.pause();
                    sf::sleep(sf::milliseconds(200));
                }
                else
                {
                    song.play();
                    sf::sleep(sf::milliseconds(200));
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                song.stop();
                if (iterator == playList.begin())
                {
                    iterator = playList.end();
                }
                iterator--;
                isSongChanged = true;
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            {
                song.stop();
                iterator++;
                isSongChanged = true;
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            {
                playOnLoop = playOnLoop ? false : true;
                song.setLoop(playOnLoop);
                sf::sleep(sf::milliseconds(200));
                std::cout << "\nLoop : " << playOnLoop << std::endl;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                song.stop();
                return;
            }
        }
        if (!isSongChanged)
        {
            iterator++;
        }
        sf::sleep(sf::milliseconds(500));
        std::cout << std::endl;
    }
}

void MusicPlayer::startPlaying()
{
    std::cout << "Select the Playlist For Playing" << std::endl;
    int result = manager->showAvailablePlaylists();
    if (result == -1)
    {
        return;
    }
    std::cin.ignore();
    std::string playlistName;
    while (true)
    {
        std::cout << "\nSelect Playlist To Play : ";
        std::getline(std::cin, playlistName);
        replaceChar(playlistName, ' ', '_');
        if (manager->playListExists(playlistName))
        {
            break;
        }
        std::cout << "\nERROR!... Please Enter valid Playlist name\n\n";
    }
    std::list<std::string> currentPlaylist = manager->getPlaylist(playlistName);
    replaceChar(playlistName, '_', ' ');
    displayUserGuidelines();
    printHeading("Current Playlist : " + playlistName);
    if (currentPlaylist.size() == 0)
    {
        std::cout << "\nPlaylist is Empty!... Choose Another\n\n";
        return;
    }
    int count = 0;
    for (std::string song : currentPlaylist)
    {
        replaceChar(song, '_', ' ');
        std::cout << count + 1 << " : " << song << std::endl;
        count++;
    }
    std::cout << DOTTEDLINE << std::endl;
    playSongs(currentPlaylist);
    std::cout << "\n\nMUSIC STOPPED" << std::endl;
    std::cin.clear();
}