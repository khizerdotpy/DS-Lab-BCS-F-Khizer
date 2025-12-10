#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct MatchInfo
{
    vector<int> indices;
    int comparisonCount;
};

MatchInfo bruteForceMatching(const string &txt, const string &pattern)
{
    MatchInfo info;
    info.comparisonCount = 0;

    int n = txt.size();
    int m = pattern.size();

    if (n == 0 || m == 0 || m > n)
        return info;

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m)
        {
            info.comparisonCount++;
            if (txt[i + j] != pattern[j])
            {
                break;
            }
            j++;
        }

        if (j == m)
            info.indices.push_back(i);
    }

    return info;
}

int main()
{
    string text = "the quick brown fox jumps over the lazy dog";
    string path = "the";

    MatchInfo result = bruteForceMatching(text, path);

    cout << "Positions Found: [";
    for (int i = 0; i < result.indices.size(); i++)
    {
        cout << result.indices[i];
        if (i + 1 < result.indices.size())
            cout << ", ";
    }
    cout << "]" << endl;
    cout << "Comparisons Made: " << result.comparisonCount << endl;

    return 0;
}
