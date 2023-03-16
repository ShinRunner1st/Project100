#include "Graphic.h"
#include <conio.h>
#include <cctype>

using namespace std;

class GameLoop
{
    bool End = false;
    vector<int> player_save_hand;
    int last_player_action = -1;

    public:
    vector<int> table_card;
    long double pot = 0;
    int last_bet = 0;
    int previous_choice = -1;
    int round = 0;
    int check_count = 0;
    int raise_count = 0;
    int call_count = 0;

    GameLoop(Player &);
    ~GameLoop();
    vector<int> create_deck();
    void Deal_card(vector<int> &, vector<int> &);
    void render(Player, AI);
    long double RIPMONEY(long double &);
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
    pot += screen_bet(player.money);
    AI *ai = new AI(pot); // create ai
    pot *= 2;
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
            last_player_action = previous_choice;
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
                cout << "+ " << pot << endl;
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
                if(player.fold == false)
                {
                    player.money += pot;
                    cout << "+ " << pot << endl;
                }
            }
            End = true;
        }
    }

    cout << endl << "Press Enter to Continue" << endl;
    getch();
    delete ai;
    player_save_hand = player.hand;
    player.hand.clear();
    player.fold = false;
}

void GameLoop::Deal_card(vector<int> &deck, vector<int> &to)
{
    to.push_back(deck.back());
    deck.pop_back();
}

long double GameLoop::RIPMONEY(long double &money)
{
    long double rip = 0;
    if(previous_choice == 1) // bet/raise
    {
        while(true)
        {
            cout << "------------------------------------------------------" << endl;
            cout << "Input money : ";
            cin >> rip;
            if((rip > money) || (rip <= 0))
            {
                printf("\033[A\33[2K\r\033[A\33[2K\r");
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else break;
        }
        money -= ceill(rip);
    }
    else if(previous_choice == 0) //call
    {
        if(money <= last_bet)
        {
            rip = money;
            money -= ceill(rip); //all-in
        }
        else
        {
            rip = last_bet;
            money -= ceill(rip);
        }
    }

    return ceill(rip);
}

void GameLoop::render(Player player, AI ai) // plain text graphic
{
    if(round < 4)
    {
        screen_game(player, ai, table_card, pot, last_bet, previous_choice);
    }
    else // show all hand
    {
        screen_result(player, ai, table_card, pot, last_bet, previous_choice);
    }
}

int main()
{
    char Isloop;
    string playerName;

    screen_welcome();
    getline(cin,playerName);
    //screen_loadGame(playerName, money);

    Player *player = new Player(playerName); //import save data into this first
    while(true)
    {
        //system("cls");
        screen_intro(player->money);
        cin >> Isloop;

        if(toupper(Isloop) == 'Y')
        {
            GameLoop *g = new GameLoop(*player);
            delete g;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(toupper(Isloop) == 'N')
        {
            delete player;
            break;
        }
        else
        {
            printf("\033[A\33[2K\r");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << ": ";
        }
    }

    system("cls");
    cout << "Quitting...";
    getch();

    return 0;
}

GameLoop::~GameLoop()
{
    vector<string> tb = FORMAT_RANK_OUT(table_card);
    vector<string> pl = FORMAT_RANK_OUT(player_save_hand);
    ofstream output_flie("History.txt", ios::app);
    output_flie << "------------------------------------------------------" << endl;
    output_flie << "Table : ";
    for(int i = 0; i < tb.size(); i++)
    {
        output_flie << tb[i] << " ";
    }
    output_flie << endl;
    output_flie << "Player : ";
    for(int i = 0; i < pl.size(); i++)
    {
        output_flie << pl[i] << " ";
    }
    output_flie << endl << "Last Action : " << lastaction(previous_choice);
    output_flie << endl << "Player Action : " << lastaction(last_player_action) << endl;
    output_flie << "Hand Rank : " << cardrank(Evaluate_Hand(table_card, player_save_hand)) << endl;
    output_flie << "Pot : " << pot << endl;
    output_flie.close();
}