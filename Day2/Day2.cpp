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
    while (i < report.size())
    {
        space = report.find_first_of(' ', i);
        if (space == string::npos)
        {
            space = report.size();
        }
        sub = report.substr(i, space-i);
        ans.push_back(stoi(sub));
        i = space + 1;
    }
    return ans;
}

bool check_safe(vector<int> report)
{
    bool increasing = false;

    if (report.at(0) < report.at(1))
    {
        increasing = true;
    }

    if ((abs(report.at(0) - report.at(1)) > 3) || (abs(report.at(0) - report.at(1)) < 1))
    {
        return false;
    }

    int i = 2;
    while (i < report.size())
    {
        if ((report.at(i) > report.at(i-1) && !increasing))
        {
            return false;
        }
        if ((report.at(i) < report.at(i-1) && increasing))
        {
            return false;
        }
        if ((abs(report.at(i) - report.at(i-1)) > 3) || (abs(report.at(i) - report.at(i-1)) < 1))
        {
            return false;
        }
        ++i;
    }
    return true;
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
        {
            safe_sum++;
        }
        else
        {
            for (int k = 0; k < soln.at(i).size(); ++k)
            {
                vector<int> test = soln.at(i);
                test.erase(test.begin() + k);
                if (check_safe(test))
                {
                    safe_sum++;
                    break;
                }
            }
        }
    }

    cout << "SAFE SUM = " << safe_sum << endl;

    return 0;
}