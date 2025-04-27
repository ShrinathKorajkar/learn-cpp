#include "matchScheduler.h"
#include <vector>

int main()
{
    std::vector<std::string> teamsList = {"Team 1", "Team 2", "Team 3", "Team 4"};
    MatchScheduler scheduler(teamsList);

    scheduler.generateSchedule();
    scheduler.displaySchedule();

    return 0;
}
