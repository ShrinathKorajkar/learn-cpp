/**
 * @file matchScheduler.h
 * @brief This file contains declarations for functions and classes related to
 *        scheduling cricket matches.
 *
 * The MatchScheduler class declared in this file is used to schedule the
 * cricket league matches in such a way based on number of teams
 * - There should be be 2 round of matches against same team
 * - There should be minimum 2 day gap for one team to play next match
 *
 * @note
 * - There is only one match in a day.
 * - There can be days where there is no match played, as it is not possible to
 *   have a schedule where there is a game every day and there is a minimum of 2
 *   days gap between consecutive matches played by the same team.
 */

#ifndef MATCHSCHEDULER_H
#define MATCHSCHEDULER_H

#include <string>
#include <vector>
#include <map>

class MatchScheduler
{
private:
    std::vector<std::string> teamsList;
    std::vector<std::pair<int, int>> matchesPair;
    std::map<int, std::pair<std::string, std::string>> matchSchedule;

    const int MIN_DAY_GAP = 2; // minimum days of gap between consecutive matches played by the same team

public:
    MatchScheduler(const std::vector<std::string> &teamsList);
    void generateSchedule();
    void displaySchedule() const;

private:
    void generateMatchPairs();
    void generateMatchSchedule();
    bool canScheduleMatch(const std::pair<int, int> &matchPair, const std::vector<int> &lastMatchDay, int currentDay) const;
    void scheduleMatch(const std::pair<int, int> &matchPair, std::vector<int> &lastMatchDay, int currentDay);
};

#endif // MATCHSCHEDULER_H
