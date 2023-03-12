#include "Player.h"
#include "Graphic.h"
#include <conio.h>
#include <cctype>

using namespace std;

class GameLoop
{
    bool End = false;

    public:
    vector<int> table_card;
    int pot = 0;
    int last_bet = 0;
    int previous_choice = -1;
    int round = 0;
    int check_count = 0;
    int raise_count = 0;
    int call_count = 0;

    GameLoop(Player &);
    ~GameLoop(){}
    vector<int> create_deck();
    void Deal_card(vector<int> &, vector<int> &);
    void render(Player, AI);
    int RIPMONEY(int &);
};

vector<int> GameLoop::create_deck() {
    vector<int> deck(52);
    for (int i = 0; i < 52; ++i) 
    {
        deck[i] = i;
    }
    srand(time(nullptr));
    for (int i = 51; i > 0; --i) 
    {
        int j = rand() % (i + 1);
        swap(deck[i], deck[j]);
    }
    return deck;
}

GameLoop::GameLoop(Player &player)
{
    vector<int> deck = create_deck(); // create deck
    AI *ai = new AI(1000); // create ai
    system("cls");
    while(!End)
    {
        for(int i = 0; i < 2; i++) // deal 2 card to any player
        {
            Deal_card(deck, player.hand);
            Deal_card(deck, ai->hand);
        }

        do
        {
            if(round == 0)
            {
                for(int i = 0; i < 3; i++) Deal_card(deck, table_card); // deal 3 card to table
            }
            else Deal_card(deck, table_card); // deal 1 card to table
            check_count = 0;
            raise_count = 0;
            call_count = 0;
            round++;
            
            start:
            render(player, *ai);
            
            previous_choice = show_choice(previous_choice); // (-1 -> 1,2,3) (0 -> 1,2,3) (1 -> 0,2) (3 -> 1,2,3)
            if(previous_choice == 3) check_count++; // check 3
            else if(previous_choice == 1) // raise 1
            {
                last_bet = RIPMONEY(player.money);
                pot += last_bet;
                raise_count++;
            }
            else if (previous_choice == 0) // call 0
            {
                pot += RIPMONEY(player.money);
                last_bet = 0;
                call_count++;
            }
            else // fold 2
            {
                player.fold = true;
                goto end;
            }
            
            previous_choice = ai->Seclect_Action(table_card, previous_choice, raise_count); // (0 -> 1,2,3) (1 -> 0,2) (3 -> 1,2,3)
            if(previous_choice == 3) check_count++; // check 3
            else if(previous_choice == 1) // raise 1
            {
                last_bet = ai->Raise();
                pot += last_bet;
                raise_count++;
            }
            else if(previous_choice == 0) // call 0
            {
                pot += ai->Call(last_bet);
                last_bet = 0;
                call_count++;
            }
            else // fold 2
            {
                ai->fold = true;
                goto end;
            }

            if((check_count >= 2 || call_count >= 2))
            {
                if(table_card.size() < 5) continue;
                else break;
            }
            else goto start;

        }
        while(table_card.size() < 5); // gameplay loop
        round++;

        end:
        if(table_card.size() < 5)
        {
            if(player.fold == false)
            {
                render(player, *ai);
                player.money += pot;
                cout << "+" << pot << endl;
            }
            else render(player, *ai);
            End = true;
        }
        else
        {
            render(player, *ai);
            if(Evaluate_Hand(table_card, ai->hand) > Evaluate_Hand(table_card, player.hand))
            {
                ai->money += pot;
            }
            else
            {
                player.money += pot;
                cout << "+" << pot << endl;
            }
            End = true;
        }
    }

    cout << "Press Enter to Continue" << endl;
    getch();
    player.hand.clear();
    player.fold = false;
    delete ai;
    system("cls");
    
}

void GameLoop::Deal_card(vector<int> &deck, vector<int> &to)
{
    to.push_back(deck.back());
    deck.pop_back();
}

int GameLoop::RIPMONEY(int &money)
{
    int rip = 0;
    if(previous_choice == 1) // bet/raise
    {
        while(true)
        {
            cout << "Input money : ";
            cin >> rip;
            if(rip > money)
            {
                cout << "Not have enough money" << endl;
                continue;
            }
            else break;
        }
        money -= rip;
    }
    else if(previous_choice == 0) //call
    {
        if(money <= last_bet)
        {
            rip = money;
            money -= rip; //all-in
        }
        else
        {
            rip = last_bet;
            money -= rip;
        }
    }

    return rip;
}

void GameLoop::render(Player player, AI ai) // plain text graphic
{
    if(round < 4)
    {
        cout << "-----------------------------" << endl;
        cout << "Table : "; show_card(table_card); cout << endl;
        cout << "Pot : " << pot << endl << endl;
        cout << "Action : "; show_lastaction(previous_choice); cout << endl; 
        cout << "Last Bet : " << last_bet << endl;
        cout << "AI Money : " << ai.money << endl;
        cout << "-----------------------------" << endl;
        cout << "Player : "; show_card(player.hand); cout << endl;
        cout << "Player Money : " << player.money << endl;
        cout << "-----------------------------" << endl;
    }
    else // show all hand
    {
        cout << "-----------------------------" << endl;
        cout << "Table : "; show_card(table_card); cout << endl;
        cout << "Pot : " << pot << endl << endl;
        cout << "Action : "; show_lastaction(previous_choice);
        if(Evaluate_Hand(table_card, ai.hand) > Evaluate_Hand(table_card, player.hand))
        cout << "AI Win" << endl;
        else
        cout << "Player Win" << endl;
        cout << "Last Bet : " << last_bet << endl;
        cout << "AI Money : " << ai.money << endl;
        cout << "-----------------------------" << endl;
        cout << "Ai : "; show_card(ai.hand); cout << " "; show_cardrank(Evaluate_Hand(table_card, ai.hand)); cout << endl;
        cout << "Player : "; show_card(player.hand); show_cardrank(Evaluate_Hand(table_card, player.hand)); cout << endl;
        cout << "Player Money : " << player.money << endl;
        cout << "-----------------------------" << endl;
    }
}

int main()
{
    char Isloop;
    Player player; //import save data into this first
    while(true)
    {
        system("cls");
        cout << "Money : " << player.money << endl;
        cout << "Start/Continue? [Y]/[N]" << endl;
        cin >> Isloop;

        if(toupper(Isloop) == 'Y')
        {
            GameLoop *g = new GameLoop(player);
            delete g;
        }
        else
        {
            break;
        }
    }
    cout << "Quitting";

    return 0;
}