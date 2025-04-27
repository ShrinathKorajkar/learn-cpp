#include "matchScheduler.h"
#include <iostream>
#include <limits>

MatchScheduler::MatchScheduler(const std::vector<std::string> &teamsList) : teamsList(teamsList) {}

void MatchScheduler::generateSchedule()
{
    generateMatchPairs();
    generateMatchSchedule();
}

void MatchScheduler::displaySchedule() const
{
    for (const auto &matchInfo : matchSchedule)
    {
        int day = matchInfo.first;
        std::string team1 = matchInfo.second.first;
        std::string team2 = matchInfo.second.second;
        std::cout << "Day " << day << ": " << team1 << " vs " << team2 << std::endl;
    }
}

void MatchScheduler::generateMatchPairs()
{
    int numOfTeams = teamsList.size();

    for (int firstTeamIndex = 0; firstTeamIndex < numOfTeams; ++firstTeamIndex)
    {
        for (int secondTeamIndex = firstTeamIndex + 1; secondTeamIndex < numOfTeams; ++secondTeamIndex)
        {
            // adding pairs twice to ensure two rounds of matches against the same team
            matchesPair.push_back({firstTeamIndex, secondTeamIndex});
            matchesPair.push_back({secondTeamIndex, firstTeamIndex});
        }
    }
}

void MatchScheduler::generateMatchSchedule()
{
    std::vector<int> lastMatchDay(teamsList.size(), std::numeric_limits<int>::min());
    int currentDay = 1;

    while (!matchesPair.empty())
    {
        for (auto iterator = matchesPair.begin(); iterator != matchesPair.end(); ++iterator)
        {
            auto matchPair = *iterator;
            if (canScheduleMatch(matchPair, lastMatchDay, currentDay))
            {
                scheduleMatch(matchPair, lastMatchDay, currentDay);
                iterator = matchesPair.erase(iterator);
                break;
            }
        }
        currentDay++;
    }
}

bool MatchScheduler::canScheduleMatch(const std::pair<int, int> &matchPair, const std::vector<int> &lastMatchDay, int currentDay) const
{
    return lastMatchDay[matchPair.first] < currentDay - MIN_DAY_GAP && lastMatchDay[matchPair.second] < currentDay - MIN_DAY_GAP;
}

void MatchScheduler::scheduleMatch(const std::pair<int, int> &matchPair, std::vector<int> &lastMatchDay, int currentDay)
{
    matchSchedule[currentDay] = {teamsList[matchPair.first], teamsList[matchPair.second]};
    lastMatchDay[matchPair.first] = currentDay;
    lastMatchDay[matchPair.second] = currentDay;
}
