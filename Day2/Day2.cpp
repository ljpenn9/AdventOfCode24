#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<int> parse(string report)
{
    int i = 0;
    int space;
    vector<int> ans;
    string sub = "";
    // cout << "report:" << report << endl;
    while (i < report.size())
    {
        space = report.find_first_of(' ', i);
        if (space == string::npos)
        {
            space = report.size();
        }
        // cout << "space = " << space << endl;
        sub = report.substr(i, space-i);
        // cout << "sub = " << sub << endl;
        ans.push_back(stoi(sub));
        i = space + 1;
    }
    return ans;
}

bool check_safe(vector<int> report)
{
    bool safe = true;
    bool removed = false;
    char inc_dec = 'i';
    if (report.at(0) < report.at(1))
    {
        inc_dec = 'i';
    }
    else
    {
        inc_dec = 'd';
    }
    int i = 1;
    while (safe && i < report.size())
    {
        if ((report.at(i) > report.at(i-1) && inc_dec == 'd'))
        {
            if (removed)
                safe = false;
            else
                removed = true;
        }
        else if ((report.at(i) < report.at(i-1) && inc_dec == 'i'))
        {
            if (removed)
                safe = false;
            else
                removed = true;
        }
        else if ((abs(report.at(i) - report.at(i-1)) > 3) || (abs(report.at(i) - report.at(i-1)) < 1))
        {
            if (removed)
                safe = false;
            else
                removed = true;
        }
        i++;
    }

    return safe;
}

int main()
{
    ifstream input;
    string report = "";
    vector<vector<int> > soln;

    input.open("input.txt");
    while(!input.eof())
    {
        getline(input, report);
        soln.push_back(parse(report));
    }
    input.close();

    int safe_sum = 0;
    for (int i = 0; i < soln.size(); i++)
    {
        if (check_safe(soln.at(i)))
            safe_sum++;
    }

    cout << "SAFE SUM = " << safe_sum << endl;

    // for (int i = 0; i < soln.size(); i++)
    // {
    //     vector<int> curr = soln.at(i);
    //     cout << "[";
    //     for (int k = 0; k < curr.size()-1; k++)
    //     {
    //         cout << curr.at(k) << ", ";
    //     }
    //     cout << curr.back() << "] || safe: " << check_safe(curr) << endl;
    // }

    return 0;
}