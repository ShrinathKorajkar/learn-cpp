#include <vector>

int maxProfit(std::vector<int> &prices)
{
    int maximumProfit = 0;
    int currentBuy = prices[0];
    int currentSell;

    for (int i = 1; i < prices.size(); i++)
    {
        currentSell = prices[i];
        maximumProfit = std::max(maximumProfit, currentSell - currentBuy);
        currentBuy = std::min(currentBuy, currentSell);
    }

    return maximumProfit;
}
