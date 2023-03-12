#include "AI.h"

void show_card(const vector<int> card) // temp plain text show card function
{
    if(card.size() == 0);
    else
    {
        vector<string> s = FORFORFOR(card);
        for(int i = 0; i < card.size(); i++)
        {
            cout << s[i] << " ";
        }
    }
}

int show_choice(int previous = -1)
{
    int action = -1;
    switch (previous)
    {
    case -1:
        while(true)
        {
            cout << "Bet [1] | Fold [2] | Check [3]" << endl;
            cin >> action;
            if(action == 1 || action == 2 || action == 3) break;
            else
            {
                cout << "Wrong input try again" << endl;
                continue;
            }
        }
        break;
    case 0:
        while(true)
        {
            cout << "Raise [1] | Fold [2] | Check [3]" << endl;
            cin >> action;
            if(action == 1 || action == 2 || action == 3) break;
            else
            {
                cout << "Wrong input try again" << endl;
                continue;
            }
        }
        break;
    case 1:
        while(true)
        {
            cout << "Call [0] | Fold [2]" << endl;
            cin >> action;
            if(action == 0 || action == 2) break;
            else
            {
                cout << "Wrong input try again" << endl;
                continue;
            }
        }
        break;
    case 3:
        while(true)
        {
            cout << "Raise [1] | Fold [2] | Check [3]" << endl;
            cin >> action;
            if(action == 1 || action == 2 || action == 3) break;
            else
            {
                cout << "Wrong input try again" << endl;
                continue;
            }
        }
        break;
    default:
        cout << "BOOM YOU GOT BUG" << endl;
        break;
    }

    return action;
}

void show_lastaction(int previous)
{
    switch (previous)
    {
    case -1:
        break;
    case 0:
        cout << "Call ";
        break;
    case 1:
        cout << "Raise ";
        break;
    case 2:
        cout << "Fold ";
        break;
    case 3:
        cout << "Check ";
        break;
    default:
        cout << "BOOM YOU GOT BUG ";
        break;
    }
}

void show_cardrank(int rank)
{
    switch (rank)
    {
    case 0:
        cout << "High Card";
        break;
    case 1:
        cout << "Pair";
        break;
    case 2:
        cout << "Two Pair";
        break;
    case 3:
        cout << "Straight";
        break;
    case 4:
        cout << "Flush";
        break;
    case 5:
        cout << "Full house";
        break;
    case 6:
        cout << "Three of a Kind";
        break;
    case 7:
        cout << "Four of a Kind";
        break;
    case 8:
        cout << "Straight Flush";
        break;
    default:
        break;
    }
}