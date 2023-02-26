#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

class AI
{
    vector<string> straightpatterns = {"A2345","23456","34567","45678","56789","678910","78910J","8910JQ","910JQK"};

    public:
        vector<int> hand; //max 2
        string name;
        int lv;

        int Seclect_Action(vector<int>, int);
        int Calc_Hand(vector<int>);
        vector<int> Sort(vector<int>);
        vector<string> FormatNumber(vector<int>);
        
        bool isonepair(vector<string>);
        bool istwopairs(vector<string>);
        bool isthreeofakind(vector<string>);
        bool isfullhouse(vector<string>);
        bool isfourofakind(vector<string>);
        bool isstraight(vector<string>);
};

int AI::Seclect_Action(vector<int> table_card, int player_action) // 0 = Call , 1 = Raise , 2 = Fold , 3 = Bet(only player)
{
    int random = rand()% 100 + 1;
    int turn = table_card.size() - 4;
    switch (Calc_Hand(table_card))
    {
    case 0: //noting
        if(random < 40) return 2; // 30% fold
        else if(random < 10 && player_action != 1) return 1; // 10% raise
        else return 0; // 60% call
        break;

    case 1: //1 pair
        if(random < 10) return 2; // 10% fold
        else if(random < 50 && player_action != 1) return 1; // 40% raise
        else return 0; // 50% call
        break;

    case 2: //2 pairs
        if(random < 10) return 2; // 10% fold
        else if(random < 50 && player_action != 1) return 1; // 40% raise
        else return 0; // 50% call
        break;
    
    case 3: // 3 kind
        if(random < 5) return 2; // 5% fold
        else if(random < 75 && player_action != 1) return 1; // 70% raise
        else return 0; // 25% call
        break;

    case 4: // staight
        if(random < 5) return 2; // 5% fold
        else if(random < 85 && player_action != 1) return 1; // 80% raise
        else return 0; // 15% call
        break;

    case 5: // fullhouse
        if(random < 2) return 2; // 2% fold
        else if(random < 82 && player_action != 1) return 1; // 80% raise
        else return 0; // 13% call
        break;
    
    case 6: // 4 kind
        if(random < 1) return 2; // 1% fold
        else if(random < 91 && player_action != 1) return 1; // 90% raise
        else return 0; // 9% call
        break;
    }
    return 2;
}

int AI::Calc_Hand(vector<int> table_card)
{
    vector<string> Calc = FormatNumber(Sort(table_card));
    if (isfourofakind(Calc)) return 6;
    else if (isfullhouse(Calc)) return 5;
    else if (isstraight(Calc)) return 4;
    else if (isthreeofakind(Calc)) return 3;
    else if (istwopairs(Calc)) return 2;
    else if (isonepair(Calc)) return 1;
    else return 0;
}

vector<int> AI::Sort(vector<int> table_card)
{
    vector<int> Allsort = table_card;
    Allsort.push_back(hand[0]);
    Allsort.push_back(hand[1]);
    sort(Allsort.begin(), Allsort.end());
    
    return Allsort;
}

vector<string> AI::FormatNumber(vector<int> card)
{
    vector<string> result;
    for(int i = 0; i < card.size(); i++)
    {
        switch (card[i]%13)
        {
        case 0:
            result.push_back("A");
            break;
        case 1:
            result.push_back("2");
            break;
        case 2:
            result.push_back("3");
            break;
        case 3:
            result.push_back("4");
            break;
        case 4:
            result.push_back("5");
            break;
        case 5:
            result.push_back("6");
            break;
        case 6:
            result.push_back("7");
            break;
        case 7:
            result.push_back("8");
            break;
        case 8:
            result.push_back("9");
            break;
        case 9:
            result.push_back("10");
            break;
        case 10:
            result.push_back("J");
            break;
        case 11:
            result.push_back("Q");
            break;
        case 12:
            result.push_back("K");
            break;
        default:
            break;
        }
    }

    return result;
}

bool AI::isfourofakind(vector<string> input)
{
    bool result = false;
    int counter = 0;
    for (int i = 0; i < input.size(); i++)
    {
        counter += count(input.begin(), input.end(), input[i]);
    }
    if (counter == input.size() + 12)
    {
        result = true;
    }
    return result;
}

bool AI::isthreeofakind(vector<string> input)
{
    bool result = false;
    int counter = 0;
    for (int i = 0; i < input.size(); i++)
    {
        counter += count(input.begin(), input.end(), input[i]);
    }
    if (counter == input.size() + 6)
    {
        result = true;
    }
    return result;
}

bool AI::isfullhouse(vector<string> input)
{
    bool result = false;
    int counter = 0;
    for (int i = 0; i < input.size(); i++)
    {
        counter += count(input.begin(), input.end(), input[i]);
    }
    if (counter == input.size() + 8)
    {
        result = true;
    }
    return result;
}

bool AI::isstraight(vector<string> input)
{
    bool result = false;
    int counter = 0;
    for (int i = 0; i < input.size(); i++)
    {
        counter += count(input.begin(), input.end(), input[i]);
    }
    if (counter >= input.size())
    {
        string combined;
        for (int i = 0; i < input.size() - 4; i++)
        {
            combined = input[i] + input[i + 1] + input[i + 2] + input[i + 3] + input[i + 4];
            for (string x : straightpatterns)
            {
                if (x == combined)
                {
                    result = true;
                }
            }
        }
    }
    return result;
}

bool AI::istwopairs(vector<string> input)
{
    bool result = false;
    int counter = 0;
    for (int i = 0; i < input.size(); i++)
    {
        counter += count(input.begin(), input.end(), input[i]);
    }
    if (counter == input.size() + 4)
    {
        result = true;
    }
    return result;
}

bool AI::isonepair(vector<string> input)
{
    bool result = false;
    int counter = 0;
    for (int i = 0; i < input.size(); i++)
    {
        counter += count(input.begin(), input.end(), input[i]);
    }
    if (counter == input.size() + 2)
    {
        result = true;
    }
    return result;
}

//int main()
//{
//    srand(time(0));
//    AI test; //create ai
//    test.hand = {25,13}; // (K A)
//    vector<int> Table = {8,1,2,3,4}; // (9 2 3 4 5)
//
//    // Test
//    int AI_action = test.Seclect_Action(Table,0); // 0 = Call , 1 = Raise , 2 = Fold , 3 = Bet(only player)
//
//    if(AI_action == 0) cout << "Call";
//    else if (AI_action == 1) cout << "Raise";
//    else if (AI_action == 2) cout << "Fold";
//
//    return 0;
//}