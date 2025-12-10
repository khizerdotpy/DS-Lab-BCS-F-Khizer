#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> createLPS(const string &pattern)
{
    int m = pattern.size();
    vector<int> prefix(m, 0);

    int length = 0;
    int idx = 1;

    while (idx < m)
    {
        if (pattern[idx] == pattern[length])
        {
            length++;
            prefix[idx] = length;
            idx++;
        }
        else
        {
            if (length != 0)
            {
                length = prefix[length - 1];
            }
            else
            {
                prefix[idx] = 0;
                idx++;
            }
        }
    }
    return prefix;
}

vector<int> KMP(const string &text, const string &pattern, vector<int> &lps)
{
    int n = text.size();
    int m = pattern.size();

    vector<int> hits;
    if (m == 0 || n == 0 || m > n)
        return hits;

    lps = createLPS(pattern);

    int i = 0;
    int j = 0;

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            hits.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return hits;
}

int main()
{
    string inputText = "ababababc";
    string inputPattern = "abab";

    vector<int> prefixTable;
    vector<int> occurrences = KMP(inputText, inputPattern, prefixTable);

    cout << "Pattern found at positions: [";
    for (int i = 0; i < occurrences.size(); i++)
    {
        cout << occurrences[i];
        if (i + 1 < occurrences.size())
            cout << ", ";
    }
    cout << "]" << endl;

    cout << "LPS Array: [";
    for (int i = 0; i < prefixTable.size(); i++)
    {
        cout << prefixTable[i];
        if (i + 1 < prefixTable.size())
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
