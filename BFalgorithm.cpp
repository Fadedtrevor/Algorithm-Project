/* 
Brute force algorithm for coin change problem, which is finding the optimal solution
of finding the minimum number of coins needed to make up a given amount. As well as factoring
in 50 cent and dollar coins. */

#include <iostream>
#include <vector>

using namespace std;

// A recursive function to find the best solution
void findBestSolution(int remaining, int coinIndex, const vector<int>& coins, vector<int>& used,
                      int& bestCoinCount, vector<int>& bestUsed)
{
    if (remaining == 0) // Goofy base case
    {
        int total = 0;
        for (int count : used)
        {
            total += count;
        }

        if (total < bestCoinCount)
        {
            bestCoinCount = total;
            bestUsed = used;
        }
        return;
    }

    if (coinIndex == coins.size()) // Checking to see if we used all the coins
    {
        return;
    }

    int coin = coins[coinIndex];
    for (int count = 0; coin * count <= remaining; ++count) // Standard iteration stuff
    {
        used[coinIndex] = count;
        findBestSolution(
            remaining - coin * count,
            coinIndex + 1,
            coins,
            used,
            bestCoinCount,
            bestUsed
        );
    }
}

int main()
{
    vector<int> coins = {1, 5, 10, 25, 50, 100};

    int amount;

    cout << "Enter the amount in cents: ";
    cin >> amount;

    if (amount < 0) // Checking if amount is negative
    {
        cout << "Amount cannot be negative." << endl;
        return 1;
    }

    vector<int> used(coins.size(), 0);
    vector<int> bestUsed;
    int bestCoinCount = amount + 1;

    // Calling the recursive function to find best solution
    findBestSolution(amount, 0, coins, used, bestCoinCount, bestUsed);

    cout << "Minimum number of coins needed: " << bestCoinCount << endl;
    cout << "Coin combination: ";

    // Display the best coin combination
    bool first = true;
    for (int i = coins.size() - 1; i >= 0; --i)
    {
        if (bestUsed[i] > 0)
        {
            if (!first)
            {
                cout << ", ";
            }

            cout << bestUsed[i] << " x " << coins[i] << " cent";
            if (coins[i] != 1)
            {
                cout << "s";
            }

            first = false;
        }
    }

    if (first) // Checking if no coins were used
    {
        cout << "none";
    }

    cout << endl;
}