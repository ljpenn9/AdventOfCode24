#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

vector<int> merge_sort(vector<int> list)
{
    // cout << "list.size() = " << list.size() << endl;
    // cout << "LIST: [";
    // for (int i = 0; i < list.size()-1; i++)
    // {
    //     cout << list.at(i) << ", ";
    // }
    // cout << list.back() << "]" << endl;

    if (list.size() == 1)
    {
        return list;
    }
    int mid = list.size() / 2;

    vector<int> left, right;

    // cout << "mid = " << mid << endl;
    for (int i = 0; i < list.size(); i++)
    {
        // cout << "i = " << i << endl;
        if (i < mid)
            left.push_back(list.at(i));
        else
            right.push_back(list.at(i));
    }

    left = merge_sort(left);
    right = merge_sort(right);

    vector<int> sorted;
    int l = 0;
    int r = 0;
    while (l < left.size() && r < right.size())
    {
        if (left.at(l) < right.at(r))
        {
            // cout << "left less" << endl;
            sorted.push_back(left.at(l));
            l++;
        }
        else
        {
            // cout << "right less" << endl;
            sorted.push_back(right.at(r));
            r++;
        }
    }

    if (l < left.size())
    {
        while (l < left.size())
        {
            sorted.push_back(left.at(l));
            l++;
        }
    }
    if (r < right.size())
    {
        while (r < right.size())
        {
            sorted.push_back(right.at(r));
            r++;
        }
    }

    // cout << "SORTED: [";
    // for (int i = 0; i < sorted.size()-1; i++)
    // {
    //     cout << sorted.at(i) << ", ";
    // }
    // cout << sorted.back() << "]" << endl;

    return sorted;
}

int main() {
    vector<int> listA;
    vector<int> listB;
    ifstream input;
    int val = 0;

    input.open("input.txt");
    while(!input.eof())
    {
        input >> val;
        listA.push_back(val);
        input >> val;
        listB.push_back(val);
    }
    input.close();

    listA = merge_sort(listA);
    listB = merge_sort(listB);

    int dist_sum = 0;
    for (int i = 0; i < listA.size(); i++)
    {
        dist_sum += abs(listA.at(i) - listB.at(i));
    }

    cout << "TOTAL DISTANCE = " << dist_sum << endl;

    int sim_score = 0;
    for (int i = 0; i < listA.size(); i++)
    {
        int curr = listA.at(i);
        int found = 0;
        for (int b = 0; b < listB.size(); b++)
        {
            if (listB.at(b) == curr)
            {
                found++;
                listB.erase(listB.begin() + b);
                b--;
            }
        }
        sim_score += curr * found;
    }

    cout << "SIMILARITY SCORE = " << sim_score << endl;

    return 0;
}