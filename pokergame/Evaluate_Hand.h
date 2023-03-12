#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<bits/stdc++.h>
#include<algorithm>

using namespace std;

vector<string> straightpatterns = {"A2345","23456","34567","45678","56789","678910","789TJ","89TJQ","9TJQK"};

vector<int> Sort(vector<int> table_card, vector<int> hand)
{
    vector<int> Allsort = table_card;
    Allsort.push_back(hand[0]);
    Allsort.push_back(hand[1]);
    sort(Allsort.begin(), Allsort.end());
    
    return Allsort;
}

vector<string> FormatNumber(vector<int> card)
{
    vector<string> result;
    for(int i = 0; i < card.size(); i++)
    {
        switch (card[i]%13)
        {
        case 0:
            result.push_back("A");
            break;
        case 9:
            result.push_back("T");
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
            result.push_back(to_string(card[i]%13 + 1));
            break;
        }
    }

    return result;
}

vector<int> FormatRank(vector<int> card)
{
    vector<int> result;
    for(int i = 0; i < card.size(); i++)
    {
        if(card[i] < 13) result.push_back(0);
        else if(card[i] < 26) result.push_back(1);
        else if(card[i] < 39) result.push_back(2);
        else result.push_back(3);
    }

    return result;
}

int Calc_Rank(vector<string> input, vector<int> rank)
{
    int result = 0;
    int counter = 0;
    int counter_rank = 0;
    for (int i = 0; i < input.size(); i++)
    {
        counter += count(input.begin(), input.end(), input[i]);
        counter_rank += count(rank.begin(), rank.end(), rank[i]);
    }
    if (counter == input.size() + 2) //pair
    {
        result = 1;
    }
    if (counter == input.size() + 4)  //twopair
    {
        result = 2;
    }
    if (counter >= input.size()) //straight
    {
        string combined;
        for (int i = 0; i < input.size(); i++) combined += input[i];
        
        for (string x : straightpatterns)
        {
            sort(begin(combined), end(combined));
            sort(begin(x), end(x));
            std::string intersection;
            std::set_intersection(begin(combined), end(combined), begin(x), end(x),back_inserter(intersection));
            if(intersection.size() >= 5) result = 3;
        }
    }
    if(counter_rank == rank.size() + 20) //flush
    {
        result = 4;
    }
    if (counter == input.size() + 8) //fullhouse
    {
        result = 5;
    }
    if (counter == input.size() + 6) //threeofakind
    {
        result = 6;
    }
    if (counter == input.size() + 12) //fourofakind
    {
        result = 7;
    }
    if (counter >= input.size()) //straightflush
    {
        string combined;
        for (int i = 0; i < input.size() - 4; i++)
        {
            combined = input[i] + input[i + 1] + input[i + 2] + input[i + 3] + input[i + 4];
            for (string x : straightpatterns)
            {
                if (x == combined)
                {
                    result = 8;
                }
            }
        }
    }

    return result; //0 = highcard
}

int Evaluate_Hand(vector<int> table_card, vector<int> hand)
{
    vector<int> sSort = Sort(table_card, hand);
    return Calc_Rank(FormatNumber(sSort), FormatRank(sSort));
}

vector<string> FORFORFOR(vector<int> card)
{
    vector<string> output = FormatNumber(card);
    for(int i = 0; i < card.size(); i++)
    {
        if(card[i] < 13) output[i] += "C";
        else if(card[i] < 26) output[i] += "D";
        else if(card[i] < 39) output[i] += "H";
        else output[i] += "S";
    }
    return output;
}

// unfinish
/*int TieBreaker_Score(vector<int> table_card, vector<int> hand)
{
    vector<int> Card = Sort(table_card, hand); //(0,1,2,3,4) //(0,13,25,26,38)
    vector<string> Number = FormatNumber(Card); // (A,2,3,4,5) //(A,A,K,A,K)
    vector<int> Rank = FormatRank(Card); //(0,0,0,0,0) //(0,1,1,2,2)
    switch (Evaluate_Hand(table_card, hand))
    {
    case 4:
        return most_common(Rank);
        break;
    
    default:
        return Card.back();
        break;
    }

}*/