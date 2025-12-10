#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> rabinKarpSearch(const string &str, const string &pattern, vector<int> &clashList)
{
    const int d = 256;
    const int mod = 10;

    int n = str.size();
    int m = pattern.size();

    vector<int> foundIndices;

    if (m == 0 || n == 0 || m > n)
        return foundIndices;

    int h = 1;

    for (int i = 0; i < m - 1; i++)
        h = (h * d) % mod;

    int pHash = 0;
    int tHash = 0;

    for (int i = 0; i < m; i++)
    {
        pHash = (d * pHash + pattern[i]) % mod;
        tHash = (d * tHash + str[i]) % mod;
    }

    for (int i = 0; i <= n - m; i++)
    {
        if (pHash == tHash)
        {
            bool found = true;

            for (int j = 0; j < m; j++)
            {
                if (str[i + j] != pattern[j])
                {
                    found = false;
                    clashList.push_back(i);
                    break;
                }
            }

            if (found)
                foundIndices.push_back(i);
        }

        if (i < n - m)
        {
            tHash = (d * (tHash - str[i] * h) + str[i + m]) % mod;
            if (tHash < 0)
                tHash += mod;
        }
    }

    return foundIndices;
}

int main()
{
    string inputText =  "Data structures and algorithms are fun. Algorithms make tasks easier.";
    string inputPattern = "Algorithms";


    vector<int> collisionList;
    vector<int> results = rabinKarpSearch(inputText, inputPattern, collisionList);

    cout << "Pattern found at: [";
    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i];
        if (i + 1 < results.size())
            cout << ", ";
    }
    cout << "]" << endl;

    if (!collisionList.empty())
    {
        cout << "False-positive hash matches (collisions detected): [";
        for (int i = 0; i < collisionList.size(); i++)
        {
            cout << collisionList[i];
            if (i + 1 < collisionList.size())
                cout << ", ";
        }
        cout << "]" << endl;
    }
    else
        cout << "No hash collisions encountered." << endl;

    return 0;
}
