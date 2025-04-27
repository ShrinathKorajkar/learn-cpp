#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <algorithm>
#include "musicPlayer.hpp"

class TestSuitForMusicPlayer : public ::testing::Test
{
public:
    PlayLists *playlist;
    MusicPlayer *musicPlayer;

    std::stringstream mockcout;
    std::streambuf *realcout;

    std::stringstream mockcin;
    std::streambuf *realcin;

    void SetUp() override
    {
        std::filesystem::remove_all(PLAYLISTS_PATH);
        playlist = new PlayLists();
        musicPlayer = new MusicPlayer(*playlist);
        realcout = std::cout.rdbuf(mockcout.rdbuf());
        realcin = std::cin.rdbuf(mockcin.rdbuf());
    }

    void TearDown() override
    {
        delete musicPlayer;
        delete playlist;
        std::cout.rdbuf(realcout);
        std::cin.rdbuf(realcin);
        std::filesystem::remove_all(PLAYLISTS_PATH);
    }
};

class MockForPlayLists : public PlayLists
{
public:
    MOCK_METHOD(void, showAllSongs, (), (override));
    MOCK_METHOD(void, modifyPlaylist, (const std::string &), (override));
};

TEST_F(TestSuitForMusicPlayer, Test_PrintError_Message)
{
    printError("Test error Message");
    EXPECT_EQ(mockcout.str(), "\nTest error Message\n");
}

TEST_F(TestSuitForMusicPlayer, Test_PrintError_FailCin)
{
    mockcin << "test";
    mockcin.setstate(std::ios::failbit);
    printError("Test error Message");

    ASSERT_FALSE(std::cin.fail());
    ASSERT_TRUE(std::cin.good());
    ASSERT_FALSE(std::cin.bad());
}

TEST_F(TestSuitForMusicPlayer, Test_PrintError_NullMessage)
{
    printError(nullptr);
    ASSERT_NO_THROW([]()
                    { printError(nullptr); });
}

TEST_F(TestSuitForMusicPlayer, Test_PrintError_EmptyMessage)
{
    printError("");
    EXPECT_EQ(mockcout.str(), "\n\n");
}

TEST_F(TestSuitForMusicPlayer, Test_PrintHeader_HeadingOddLenght)
{
    printHeading("TEST HEADINGS");
    std::string expectedOutput = "\n";
    expectedOutput += DOTTEDLINE;
    expectedOutput += DOTTEDLINE;
    expectedOutput += "---               TEST HEADINGS               ---\n";
    expectedOutput += DOTTEDLINE;
    EXPECT_EQ(mockcout.str(), expectedOutput);
}

TEST_F(TestSuitForMusicPlayer, Test_PrintHeader_HeadingEvenLenght)
{
    printHeading("TEST HEADING");
    std::string expectedOutput = "\n";
    expectedOutput += DOTTEDLINE;
    expectedOutput += DOTTEDLINE;
    expectedOutput += "---               TEST HEADING                ---\n";
    expectedOutput += DOTTEDLINE;
    EXPECT_EQ(mockcout.str(), expectedOutput);
}

TEST_F(TestSuitForMusicPlayer, Test_PrintHeader_LongHeading)
{
    printHeading("A TEST HEADING WHICH IS SO LONG THAT IT CANNOT FIT");
    std::string expectedOutput = "\n";
    expectedOutput += DOTTEDLINE;
    expectedOutput += DOTTEDLINE;
    expectedOutput += "A TEST HEADING WHICH IS SO LONG THAT IT CANNOT FIT\n";
    expectedOutput += DOTTEDLINE;
    EXPECT_EQ(mockcout.str(), expectedOutput);
}

TEST_F(TestSuitForMusicPlayer, Test_PrintHeader_ExactLength)
{
    printHeading("A EXACT TEST HEADING THE MAX MATCHES LENGTH");
    std::string expectedOutput = "\n";
    expectedOutput += DOTTEDLINE;
    expectedOutput += DOTTEDLINE;
    expectedOutput += "---A EXACT TEST HEADING THE MAX MATCHES LENGTH---\n";
    expectedOutput += DOTTEDLINE;
    EXPECT_EQ(mockcout.str(), expectedOutput);
}

TEST_F(TestSuitForMusicPlayer, Test_PrintHeader_EmptyString)
{
    printHeading("");
    std::string expectedOutput = "\n";
    expectedOutput += DOTTEDLINE;
    expectedOutput += DOTTEDLINE;
    expectedOutput += "---                                           ---\n";
    expectedOutput += DOTTEDLINE;
    EXPECT_EQ(mockcout.str(), expectedOutput);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_CreatePlaylist)
{
    mockcin << "\nShri Ram\n0\n";
    playlist->createPlaylist();
    EXPECT_TRUE(playlist->playListExists("Shri_Ram"));

    std::string expectedFile = PLAYLISTS_PATH;
    expectedFile += "Shri_Ram.txt";
    EXPECT_TRUE(std::filesystem::exists(expectedFile));
    EXPECT_TRUE(std::filesystem::file_size(expectedFile) == 0);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_CreatePlaylistWithSongs)
{
    mockcin << "\nShri Ram\n1\n2\n3\n0\n";
    playlist->createPlaylist();

    EXPECT_TRUE(playlist->playListExists("Shri_Ram"));
    EXPECT_TRUE(mockcout.str().find("\nPlaylist Created Successfully\n") == std::string::npos);

    std::string expectedFile = PLAYLISTS_PATH;
    expectedFile += "Shri_Ram.txt";
    ASSERT_TRUE(std::filesystem::exists(expectedFile));
    EXPECT_TRUE(std::filesystem::file_size(expectedFile) > 0);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_CreatePlaylist_ShowSongs)
{
    MockForPlayLists mock;
    EXPECT_CALL(mock, showAllSongs()).Times(1);

    mockcin << "\nShri Ram\n0\n";
    mock.createPlaylist();

    ASSERT_TRUE(mock.playListExists("Shri_Ram"));
    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_CreatePlaylist_WithExistingName)
{
    mockcin << "\nShri Ram\n0\n";
    playlist->createPlaylist();

    EXPECT_TRUE(playlist->playListExists("Shri_Ram"));
    ASSERT_FALSE(playlist->playListExists("Jai_Shri_Ram"));

    mockcin << "\nShri Ram\nJai Shri Ram\n0\n";
    ASSERT_NO_THROW(playlist->createPlaylist());
    EXPECT_TRUE(mockcout.str().find("\nERROR! : Playlist already exists. Try again...\n\n\n") == std::string::npos);

    // ASSERT_TRUE(playlist->playListExists("Jai_Shri_Ram"));
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_CreatePlaylist_TestDiffInput)
{
    mockcin << "\nShri\n0\n";
    ASSERT_NO_THROW(playlist->createPlaylist());

    mockcin << "\nRam\n1\n1\n0\n";
    ASSERT_NO_THROW(playlist->createPlaylist());

    mockcin << "\nRam\n14\n1\n0\n";
    ASSERT_NO_THROW(playlist->createPlaylist());

    mockcin << "\nRam\nabc\n1\n0\n";
    ASSERT_NO_THROW(playlist->createPlaylist());
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_DeletePlaylist_DeleteExisting)
{
    mockcin << "\nShri\n0\n";
    playlist->createPlaylist();

    ASSERT_TRUE(playlist->playListExists("Shri"));

    mockcin << "Shri\n0\n";
    playlist->deletePlaylist();

    std::string expectedFile = PLAYLISTS_PATH;
    expectedFile += "Shri.txt";
    EXPECT_TRUE(mockcout.str().find("\nPlaylist removed successfully\n\n") != std::string::npos);
    ASSERT_FALSE(std::filesystem::exists(expectedFile));
    ASSERT_FALSE(playlist->playListExists("Shri"));
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_DeletePlaylist_DeleteNonExisting)
{
    std::string expectedFile = PLAYLISTS_PATH;
    expectedFile += "Shri.txt";
    ASSERT_FALSE(std::filesystem::exists(expectedFile));
    EXPECT_FALSE(playlist->playListExists("Shri"));

    mockcin << "Shri\n0\n";
    ASSERT_NO_THROW(playlist->deletePlaylist());
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_GetPlaylist_Existing)
{
    mockcin << "\nShri\n1\n2\n0\n";
    playlist->createPlaylist();

    ASSERT_TRUE(playlist->playListExists("Shri"));
    std::list<std::string> list = playlist->getPlaylist("Shri");
    std::cerr << list.size() << std::endl;
    ASSERT_TRUE(list.size() == 2);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_GetPlaylist_NonExisting)
{
    mockcin << "\nShri\n1\n0\n";
    playlist->createPlaylist();

    ASSERT_TRUE(playlist->playListExists("Shri"));
    std::list<std::string> list = playlist->getPlaylist("Ram");
    ASSERT_TRUE(list.size() == 0);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_WithoutPlaylist)
{
    ASSERT_NO_THROW(playlist->editPlaylist());
    EXPECT_TRUE(mockcout.str().find("\nPlaylist are not available. Create one first\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_WithPlaylist)
{
    MockForPlayLists mock;
    mockcin << "\nShri Ram\n0\n";
    mock.createPlaylist();

    EXPECT_CALL(mock, modifyPlaylist(::testing::_)).Times(1);
    mockcin << "\nShri Ram\n";
    mock.editPlaylist();

    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_AddSongInEmptyPlaylist)
{
    mockcin << "\nShri Ram\n0\n";
    playlist->createPlaylist();

    mockcin << "\nShri Ram\n1\n1\n0\n4\n";
    playlist->editPlaylist();

    std::string filePath = PLAYLISTS_PATH;
    filePath += "Shri_Ram.txt";
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_AddSongInExistingPlaylist)
{
    mockcin << "\nShri Ram\n1\n2\n0\n";
    playlist->createPlaylist();

    mockcin << "\nShri Ram\n1\n4\n3\n0\n4\n";
    playlist->editPlaylist();

    std::string filePath = PLAYLISTS_PATH;
    filePath += "Shri_Ram.txt";
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);

    std::ifstream file(filePath);
    std::string line;
    int count = 0;
    while (file >> line)
    {
        count++;
    }
    EXPECT_EQ(count, 4);
    file.close();
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_AddSongAlreadyAddedSong)
{
    mockcin << "\nShri Ram\n1\n2\n0\n";
    playlist->createPlaylist();

    mockcin << "\nShri Ram\n1\n1\n2\n0\n4\n";
    playlist->editPlaylist();

    std::string filePath = PLAYLISTS_PATH;
    filePath += "Shri_Ram.txt";
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);

    std::ifstream file(filePath);
    std::string line;
    int count = 0;
    while (file >> line)
    {
        count++;
    }
    EXPECT_EQ(count, 2);
    file.close();

    EXPECT_TRUE(mockcout.str().find("Already added") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_AddSongNonExistingSong)
{
    mockcin << "\nShri Ram\n1\n2\n0\n";
    playlist->createPlaylist();

    mockcin << "\nShri Ram\n1\n14\n20\n0\n4\n";
    playlist->editPlaylist();

    std::string filePath = PLAYLISTS_PATH;
    filePath += "Shri_Ram.txt";
    ASSERT_TRUE(std::filesystem::file_size(filePath) > 0);

    std::ifstream file(filePath);
    std::string line;
    int count = 0;
    while (file >> line)
    {
        count++;
    }
    EXPECT_EQ(count, 2);
    file.close();
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_DeleteSongs_NonEmptyPlaylist)
{
    mockcin << "\nShri Ram\n1\n2\n0\n";
    playlist->createPlaylist();

    mockcin << "\nShri Ram\n2\n2\n1\n0\n4\n";
    playlist->editPlaylist();

    std::string filePath = PLAYLISTS_PATH;
    filePath += "Shri_Ram.txt";
    ASSERT_TRUE(std::filesystem::file_size(filePath) == 0);
    EXPECT_TRUE(mockcout.str().find("\nDeleted Successfully\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_DeleteSongs_EmptyPlaylist)
{
    mockcin << "\nShri Ram\n0\n";
    playlist->createPlaylist();

    mockcin << "\nShri Ram\n2\n4\n";

    ASSERT_NO_THROW(playlist->editPlaylist());
    EXPECT_TRUE(mockcout.str().find("\nPlaylist is Empty!") != std::string::npos);

    std::string filePath = PLAYLISTS_PATH;
    filePath += "Shri_Ram.txt";
    ASSERT_TRUE(std::filesystem::file_size(filePath) == 0);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_MoveSongs_SamePosition)
{
    mockcin << "\nShri Ram\n1\n2\n3\n4\n5\n0\n";
    playlist->createPlaylist();
    std::list<std::string> listBeforeMovingSongs = playlist->getPlaylist("Shri_Ram");

    mockcin << "\nShri Ram\n3\n3\n3\n0\n4\n";
    playlist->editPlaylist();
    std::list<std::string> listAfterMovingSongs = playlist->getPlaylist("Shri_Ram");

    ASSERT_EQ(listBeforeMovingSongs, listAfterMovingSongs);
    ASSERT_TRUE(std::equal(listBeforeMovingSongs.begin(), listBeforeMovingSongs.end(), listAfterMovingSongs.begin()));
    EXPECT_TRUE(mockcout.str().find("\nOperation Successfull\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_MoveSongs_EmptyPlaylist)
{
    mockcin << "\nShri Ram\n0\n";
    playlist->createPlaylist();

    mockcin << "\nShri Ram\n3\n4\n";
    ASSERT_NO_THROW(playlist->editPlaylist());
    EXPECT_TRUE(mockcout.str().find("\nPlaylist is Empty!\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_MoveSongs_InvalidPosition)
{
    // moving from 3 position to > last position and 2 position to  < first position
    mockcin << "\nShri Ram\n1\n2\n3\n4\n5\n0\n";
    playlist->createPlaylist();
    std::list<std::string> listBeforeMovingSongs = playlist->getPlaylist("Shri_Ram");

    mockcin << "\nShri Ram\n3\n3\n8\n2\n-3\n0\n4\n";
    playlist->editPlaylist();
    std::list<std::string> listAfterMovingSongs = playlist->getPlaylist("Shri_Ram");

    auto iteratorBefore = listBeforeMovingSongs.begin();
    auto iteratorAfter = listAfterMovingSongs.begin();

    iteratorBefore++;
    ASSERT_EQ(*iteratorBefore, *iteratorAfter);

    iteratorBefore++;
    std::advance(iteratorAfter, 4);
    ASSERT_EQ(*iteratorBefore, *iteratorAfter);
    EXPECT_TRUE(mockcout.str().find("\nOperation Successfull\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_MoveSongs_Up)
{
    mockcin << "\nShri Ram\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n";
    playlist->createPlaylist();
    std::list<std::string> listBeforeMovingSongs = playlist->getPlaylist("Shri_Ram");

    mockcin << "\nShri Ram\n3\n3\n6\n0\n4\n";
    playlist->editPlaylist();
    std::list<std::string> listAfterMovingSongs = playlist->getPlaylist("Shri_Ram");

    auto iteratorBefore = listBeforeMovingSongs.begin();
    auto iteratorAfter = listAfterMovingSongs.begin();

    std::advance(iteratorBefore, 2);
    std::advance(iteratorAfter, 5);
    ASSERT_EQ(*iteratorBefore, *iteratorAfter);
    EXPECT_TRUE(mockcout.str().find("\nOperation Successfull\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlayListsClass_EditPlaylist_MoveSongs_Down)
{
    mockcin << "\nShri Ram\n1\n2\n3\n4\n5\n6\n7\n8\n9\n0\n";
    playlist->createPlaylist();
    std::list<std::string> listBeforeMovingSongs = playlist->getPlaylist("Shri_Ram");

    mockcin << "\nShri Ram\n3\n8\n3\n0\n4\n";
    playlist->editPlaylist();
    std::list<std::string> listAfterMovingSongs = playlist->getPlaylist("Shri_Ram");

    auto iteratorBefore = listBeforeMovingSongs.begin();
    auto iteratorAfter = listAfterMovingSongs.begin();

    std::advance(iteratorBefore, 7);
    std::advance(iteratorAfter, 2);
    ASSERT_EQ(*iteratorBefore, *iteratorAfter);
    EXPECT_TRUE(mockcout.str().find("\nOperation Successfull\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlaylistClass_ShowAvailablePlaylists_ExistingPlaylists)
{
    mockcin << "\nShri\n0\n";
    playlist->createPlaylist();

    playlist->showAvailablePlaylists();
    EXPECT_TRUE(mockcout.str().find("Shri\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlaylistClass_ShowAvailablePlaylists_NoExistingPlaylists)
{
    playlist->showAvailablePlaylists();
    EXPECT_TRUE(mockcout.str().find("\nPlaylist are not available. Create one first\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_PlaylistClass_PlaylistExist_ExistingPlaylists)
{
    mockcin << "\nShri\n0\n";
    playlist->createPlaylist();
    ASSERT_TRUE(playlist->playListExists("Shri"));
}

TEST_F(TestSuitForMusicPlayer, Test_PlaylistClass_PlaylistExist_NonExistingPlaylists)
{
    ASSERT_FALSE(playlist->playListExists("Shri"));
}

//
class MockForMusicPlayer : public MusicPlayer
{
public:
    MockForMusicPlayer(PlayLists &manager) : MusicPlayer(manager) {}
    MOCK_METHOD(void, displayUserGuidelines, (), (override));
    MOCK_METHOD(void, playSongs, (const std::list<std::string> &), (override));
};

TEST_F(TestSuitForMusicPlayer, Test_MusicPlayerClass_Play_WithoutPlaylist)
{
    musicPlayer->startPlaying();
    EXPECT_TRUE(mockcout.str().find("\nPlaylist are not available. Create one first\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_MusicPlayerClass_Play_EmptyPlaylist)
{
    mockcin << "\nShri\n0\n";
    playlist->createPlaylist();
    ASSERT_TRUE(playlist->playListExists("Shri"));

    mockcin << "Shri\n\n";
    musicPlayer->startPlaying();
    EXPECT_TRUE(mockcout.str().find("USER GUIDELINES") != std::string::npos);
    EXPECT_TRUE(mockcout.str().find("\nPlaylist is Empty!... Choose Another\n\n") != std::string::npos);
}

TEST_F(TestSuitForMusicPlayer, Test_MusicPlayerClass_Play_NonEmptyPlaylist)
{
    MockForMusicPlayer mock(*playlist);
    mockcin << "\nShri\n1\n2\n0\n";
    playlist->createPlaylist();
    ASSERT_TRUE(playlist->playListExists("Shri"));

    EXPECT_CALL(mock, displayUserGuidelines()).Times(1);
    EXPECT_CALL(mock, playSongs(::testing::_)).Times(1);

    mockcin << "Shri\n\n";
    mock.startPlaying();

    ASSERT_TRUE(::testing::Mock::VerifyAndClearExpectations(&mock));
    EXPECT_TRUE(mockcout.str().find("\n\nMUSIC STOPPED") != std::string::npos);
}
