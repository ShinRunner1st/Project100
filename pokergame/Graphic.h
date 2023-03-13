#include "AI.h"
#include "Player.h"

using namespace std;

vector<string> FORMAT_RANK(vector<int> card)
{
    vector<string> output = FormatNumber(card);
    for(int i = 0; i < card.size(); i++)
    {
        if(card[i] < 13) output[i] += '\5';
        else if(card[i] < 26) output[i] += '\4';
        else if(card[i] < 39) output[i] += '\3';
        else output[i] += '\6';
    }
    return output;
}

vector<string> FORMAT_RANK_OUT(vector<int> card)
{
    vector<string> output = FormatNumber(card);
    for(int i = 0; i < card.size(); i++)
    {
        if(card[i] < 13) output[i] += 'C';
        else if(card[i] < 26) output[i] += 'D';
        else if(card[i] < 39) output[i] += 'H';
        else output[i] += 'S';
    }
    return output;
}

void old_show_card(const vector<int> card)
{
    vector<string> s = FORMAT_RANK(card);
    for(int i = 0; i < card.size(); i++)
    {
        cout << s[i] << " ";
    }
}

void show_card(const vector<int> card) // temp plain text show card function // set 33 (center)
{
    /*if(card.size() == 0);
    else
    {
        vector<string> s = FORMAT_RANK(card);
        for(int i = 0; i < card.size(); i++)
        {
            cout << s[i] << " ";
        }
    }*/
    double sset = floor(47.5+(-9.5*(double)card.size()));
    if(card.size() == 0);
    else
    {
        vector<string> s = FORMAT_RANK(card);
        int n = card.size();
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << " _______   ";
            else cout << " _______   ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset-10) << "|" << s[i][1] << "      |  ";
            else cout << "|" << s[i][1] << "      |  ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << "|       |  ";
            else cout << "|       |  ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset-7) << "|   " << s[i][0] << "   |  ";
            else cout << "|   " << s[i][0] << "   |  ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << "|       |  ";
            else cout << "|       |  ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << "|_______|  ";
            else cout << "|_______|  ";
        }
        cout << "\n";
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
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
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
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
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
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
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
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
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
    int set = 34;
    switch (rank)
    {
    case 0:
        cout << setw(set-3) << "High Card";
        break;
    case 1:
        cout << setw(set-5) << "Pair";
        break;
    case 2:
        cout << setw(set-4) << "Two Pair";
        break;
    case 3:
        cout << setw(set) << "Straight";
        break;
    case 4:
        cout << setw(set-5) << "Flush";
        break;
    case 5:
        cout << setw(set) << "Full house";
        break;
    case 6:
        cout << setw(set) << "Three of a Kind";
        break;
    case 7:
        cout << setw(set) << "Four of a Kind";
        break;
    case 8:
        cout << setw(set) << "Straight Flush";
        break;
    default:
        break;
    }
}

void screen_intro(long double money)
{
    cout << R"(
 .----------------.   .----------------.   .----------------.   .----------------.   .----------------. 
| .--------------. | | .--------------. | | .--------------. | | .--------------. | | .--------------. |
| |   ______     | | | |     ____     | | | |  ___  ____   | | | |  _________   | | | |  _______     | |
| |  |_   __ \   | | | |   .'    `.   | | | | |_  ||_  _|  | | | | |_   ___  |  | | | | |_   __ \    | |
| |    | |__) |  | | | |  /  .--.  \  | | | |   | |_/ /    | | | |   | |_  \_|  | | | |   | |__) |   | |
| |    |  ___/   | | | |  | |    | |  | | | |   |  __'.    | | | |   |  _|  _   | | | |   |  __ /    | |
| |   _| |_      | | | |  \  `--'  /  | | | |  _| |  \ \_  | | | |  _| |___/ |  | | | |  _| |  \ \_  | |
| |  |_____|     | | | |   `.____.'   | | | | |____||____| | | | | |_________|  | | | | |____| |___| | |
| |              | | | |              | | | |              | | | |              | | | |              | |
| '--------------' | | '--------------' | | '--------------' | | '--------------' | | '--------------' |
 '----------------'   '----------------'   '----------------'   '----------------'   '----------------' 
)";
    cout << fixed << setprecision(0) << setw(52) << "Money : " << money << endl;
    cout << "Start [Y] | [N]" << endl;
    cout << ": ";
}

void screen_result(Player player, AI ai, vector<int> table_card, long double pot, long double last_bet,int previous_choice)
{
    cout << "------------------------------------------------------" << endl;
    show_card(table_card); cout << endl;
    cout << setw(28) << "Pot : " << pot << endl << endl;
    cout << "------------------------------------------------------" << endl;
    //cout << "Last Bet : " << last_bet << endl;
    cout << setw(27) << "AI" << endl;
    show_card(ai.hand); show_cardrank(Evaluate_Hand(table_card, ai.hand)); cout << endl;
    cout << "Money : " << ai.money << endl;
    cout << "Action : "; show_lastaction(previous_choice); cout << endl;
    /*cout << "AI Money : " << ai.money << endl;
    cout << "Action : ";
    if(Evaluate_Hand(table_card, ai.hand) > Evaluate_Hand(table_card, player.hand))
    cout << "AI Win" << endl;
    else
    cout << "Player Win" << endl;*/
    cout << "------------------------------------------------------" << endl;
    cout << setw(29) << "Player" << endl;
    show_card(player.hand); show_cardrank(Evaluate_Hand(table_card, player.hand)); cout << endl;
    cout << "Player Money : " << player.money << endl;
    cout << "------------------------------------------------------" << endl;
    if(Evaluate_Hand(table_card, ai.hand) > Evaluate_Hand(table_card, player.hand))
    cout << "AI Win" << endl;
    else
    cout << "Player Win" << endl;
    cout << "------------------------------------------------------" << endl;
}

void screen_game(Player player, AI ai, vector<int> table_card, long double pot, long double last_bet,int previous_choice)
{
    cout << "------------------------------------------------------" << endl;
    show_card(table_card); cout << endl;
    cout << setw(28) << "Pot : " << pot << endl << endl;
    cout << "------------------------------------------------------" << endl;
    //cout << "Last Bet : " << last_bet << endl;
    cout << setw(27) << "AI" << endl;
    cout << "Money : " << ai.money << endl;
    cout << "Action : "; show_lastaction(previous_choice); cout << endl;
    cout << "------------------------------------------------------" << endl;
    cout << setw(29) << "Player" << endl;
    show_card(player.hand); cout << endl;
    cout << "Money : " << player.money << endl;
    cout << "------------------------------------------------------" << endl;
}