#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> buildBadCharTable(const string &pattern)
{
    const int d = 256;
    vector<int> lastOccured(d, -1);

    for (int i = 0; i < pattern.size(); i++)
        lastOccured[pattern[i]] = i;

    return lastOccured;
}

vector<int> computeSuffixArray(const string &pattern)
{
    int m = pattern.size();
    vector<int> suffix(m, -1);
    suffix[m - 1] = m;

    int g = m - 1, f = 0;

    for (int i = m - 2; i >= 0; i--)
    {
        if (i > g && suffix[i + m - 1 - f] < i - g)
        {
            suffix[i] = suffix[i + m - 1 - f];
        }
        else
        {
            g = min(g, i);
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                g--;
            suffix[i] = f - g;
        }
    }
    return suffix;
}

vector<int> buildGoodSuffixTable(const string &pattern)
{
    int m = pattern.size();
    vector<int> suffix = computeSuffixArray(pattern);
    vector<int> goodSuffix(m, m);

    for (int i = m - 1; i >= 0; i--)
    {
        if (suffix[i] == i + 1)
        {
            for (int j = 0; j < m - 1 - i; j++)
            {
                if (goodSuffix[j] == m)
                    goodSuffix[j] = m - 1 - i;
            }
        }
    }

    for (int i = 0; i <= m - 2; i++)
        goodSuffix[m - 1 - suffix[i]] = m - 1 - i;

    return goodSuffix;
}

vector<int> boyerMoore(const string &text, const string &pattern)
{
    int n = text.size();
    int m = pattern.size();
    vector<int> foundPos;

    if (m == 0 || n == 0 || m > n)
        return foundPos;

    vector<int> bc = buildBadCharTable(pattern);
    vector<int> gs = buildGoodSuffixTable(pattern);

    int shift = 0;

    while (shift <= n - m)
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0)
        {
            foundPos.push_back(shift);
            shift += gs[0];
        }
        else
        {
            int moveBC = j - bc[text[shift + j]];
            int moveGS = gs[j];
            shift += max(1, max(moveBC, moveGS));
        }
    }

    return foundPos;
}

int main()
{
    string dnaSequence = "ACGTACGTGACG";
    string pattern = "ACG";

    vector<int> hits = boyerMoore(dnaSequence, pattern);

    cout << "Pattern found at : [";
    for (int i = 0; i < hits.size(); i++)
    {
        cout << hits[i];
        if (i + 1 < hits.size())
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
