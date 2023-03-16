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

void show_card(const vector<int> card) // temp plain text show card function //54/2=27 + string/2
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
    double sset = ceill(38.5+(-5.5*(double)card.size()));
    if(card.size() == 0);
    else
    {
        vector<string> s = FORMAT_RANK(card);
        int n = card.size();
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << " _______   "; //11
            else cout << " _______   ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset-10) << "|" << s[i][1] << "      |  "; //1
            else cout << "|" << s[i][1] << "      |  ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << "|       |  "; //11
            else cout << "|       |  ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(s[i][0] == 'T')
            {
                if(i == 0) cout << setw(sset-7) << "|   " << "10" << "  |  "; //5
                else cout << "|   " << "10" << "  |  ";
            }
            else
            {
                if(i == 0) cout << setw(sset-7) << "|   " << s[i][0] << "   |  "; //5
                else cout << "|   " << s[i][0] << "   |  ";
            }
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << "|       |  "; //11
            else cout << "|       |  ";
        }
        cout << "\n";
        for (int i = 0; i < n; i++)
        {
            if(i == 0) cout << setw(sset) << "|_______|  "; //11
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
            cout << setw(44) << "| Bet [1] | Fold [2] | Check [3] |" << endl;
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
            cin >> action;
            if(action == 1 || action == 2 || action == 3)
            {
                if(action == 1) printf("\033[A\33[2K\r\033[A\33[2K\r");
                break;
            }
            else
            {
                printf("\033[A\33[2K\r\033[A\33[2K\r\033[A\33[2K\r");
                //cout << "Wrong input try again" << endl;
                //cout << "------------------------------------------------------" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //printf("\033[A\33[2K\r\033[A\33[2K\r\033[A\33[2K\r");
                continue;
            }
        }
        break;
    case 0:
        while(true)
        {
            cout << setw(45) << "| Raise [1] | Fold [2] | Check [3] |" << endl;
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
            cin >> action;
            if(action == 1 || action == 2 || action == 3)
            {
                if(action == 1) printf("\033[A\33[2K\r\033[A\33[2K\r");
                break;
            }
            else
            {
                printf("\033[A\33[2K\r\033[A\33[2K\r\033[A\33[2K\r");
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
        break;
    case 1:
        while(true)
        {
            cout << setw(39) << "| Call [1] | Fold [2] |" << endl;
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
            cin >> action;
            if(action == 1 || action == 2) break;
            else
            {
                printf("\033[A\33[2K\r\033[A\33[2K\r\033[A\33[2K\r");
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
        if(action == 1) action = 0;
        break;
    case 3:
        while(true)
        {
            cout << setw(45) << "| Raise [1] | Fold [2] | Check [3] |" << endl;
            cout << "------------------------------------------------------" << endl;
            cout << ": ";
            cin >> action;
            if(action == 1 || action == 2 || action == 3)
            {
                if(action == 1) printf("\033[A\33[2K\r\033[A\33[2K\r");
                break;
            }
            else
            {
                printf("\033[A\33[2K\r\033[A\33[2K\r\033[A\33[2K\r");
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    int set = 27; //+ string/2
    switch (rank)
    {
    case 0:
        cout << setw(set+5) << "High Card"; //9/2 5
        break;
    case 1:
        cout << setw(set+2) << "Pair"; //4/2 2
        break;
    case 2:
        cout << setw(set+4) << "Two Pair"; //8/2 4
        break;
    case 3:
        cout << setw(set+4) << "Straight"; //8/2 4
        break;
    case 4:
        cout << setw(set+3) << "Flush"; //5/2 3
        break;
    case 5:
        cout << setw(set+5) << "Full house"; //10/2 5
        break;
    case 6:
        cout << setw(set+8) << "Three of a Kind"; //15/2 8
        break;
    case 7:
        cout << setw(set+7) << "Four of a Kind"; //14/2 7
        break;
    case 8:
        cout << setw(set+7) << "Straight Flush"; //14/2 7
        break;
    default:
        break;
    }
}

void screen_intro(long double money) //104/2 52
{
    system("cls");
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
    cout << fixed << setprecision(0) << setw(52) << "Money : " << money << endl << endl;
    cout << setw(56) << "Start [Y]" << endl;
    cout << setw(56) << "Exit  [N]" << endl << endl;
    cout << ": ";
}

void screen_result(Player player, AI ai, vector<int> table_card, long double pot, long double last_bet,int previous_choice) //54/2=27 + string/2
{
    system("cls");
    cout << "------------------------------------------------------" << endl;
    show_card(table_card); cout << endl;
    cout << setw(30) << "Pot : " << pot << endl << endl;
    cout << "------------------------------------------------------" << endl;
    //cout << "Last Bet : " << last_bet << endl;
    cout << setw(28) << "AI" << endl;
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
    cout << setw(30) << "Player" << endl;
    show_card(player.hand); show_cardrank(Evaluate_Hand(table_card, player.hand)); cout << endl;
    cout << "Player Money : " << player.money << endl;
    cout << "------------------------------------------------------" << endl;
    if(Evaluate_Hand(table_card, ai.hand) > Evaluate_Hand(table_card, player.hand))
    cout << setw(30) << "AI Win" << endl;
    else
    cout << setw(32) << "Player Win" << endl;
    cout << "------------------------------------------------------" << endl;
}

void screen_game(Player player, AI ai, vector<int> table_card, long double pot, long double last_bet,int previous_choice)
{
    system("cls");
    cout << "------------------------------------------------------" << endl;
    show_card(table_card); cout << endl;
    cout << setw(30) << "Pot : " << pot << endl << endl;
    cout << "------------------------------------------------------" << endl;
    //cout << "Last Bet : " << last_bet << endl;
    cout << setw(28) << "AI" << endl;
    cout << "Money : " << ai.money << endl;
    cout << "Action : "; show_lastaction(previous_choice); cout << endl;
    cout << "------------------------------------------------------" << endl;
    cout << setw(30) << "Player" << endl;
    show_card(player.hand); cout << endl;
    cout << "Money : " << player.money << endl;
    cout << "------------------------------------------------------" << endl;
}



void screen_loadGame(string playerName, long double &money) {

    
    ifstream file("Savegame.txt");
    string line;

    
    while (getline(file, line)) {
        
        char name[100];
        long double cash;
        sscanf(line.c_str(), "%s %Lf", name, &cash);

        
        if (playerName == name) {
            
            money = cash;
            file.close();
            return;
        }

    }
    file.close();

    
    money = 20000;
   
    ofstream outfile("Savegame.txt", ios_base::app);
    outfile << playerName << " " << money << endl;
    outfile.close();

}

void screen_welcome(){
         cout << R"(
                                                               
                                                  ___                                                                                
                                                  `MM                                                                                
                                                   MM                                                                                
                          ____    _    ___  ____   MM   ____     _____  ___  __    __     ____                                       
                          `MM(   ,M.   )M' 6MMMMb  MM  6MMMMb.  6MMMMMb `MM 6MMb  6MMb   6MMMMb                                      
                           `Mb   dMb   d' 6M'  `Mb MM 6M'   Mb 6M'   `Mb MM69 `MM69 `Mb 6M'  `Mb                                     
                            YM. ,PYM. ,P  MM    MM MM MM    `' MM     MM MM'   MM'   MM MM    MM                                     
                            `Mb d'`Mb d'  MMMMMMMM MM MM       MM     MM MM    MM    MM MMMMMMMM                                     
                             YM,P  YM,P   MM       MM MM       MM     MM MM    MM    MM MM                                           
68b                          `MM'  `MM'   YM    d9 MM YM.   d9 YM.   ,M9 MM    MM    MM YM    d9                                     
Y89                           YP  / YP     YMMMM9 _MM_ YMMMM9   YMMMMM9 _MM_  _MM_  _MM_ YMMMM9                                      
___ ___  __  __ ____  ___   ___  /M          ____    ___  _____  ___   ___ ___  __      ___  __      ___    ___  __    __     ____   
`MM `MM 6MMb `M6MMMMb `MM    MM /MMMMM       `MM(    )M' 6MMMMMb `MM    MM `MM 6MM      `MM 6MMb   6MMMMb   `MM 6MMb  6MMb   6MMMMb  
 MM  MMM9 `Mb MM'  `Mb MM    MM  MM           `Mb    d' 6M'   `Mb MM    MM  MM69 "       MMM9 `Mb 8M'  `Mb   MM69 `MM69 `Mb 6M'  `Mb 
 MM  MM'   MM MM    MM MM    MM  MM            YM.  ,P  MM     MM MM    MM  MM'          MM'   MM     ,oMM   MM'   MM'   MM MM    MM 
 MM  MM    MM MM    MM MM    MM  MM             MM  M   MM     MM MM    MM  MM           MM    MM ,6MM9'MM   MM    MM    MM MMMMMMMM 
 MM  MM    MM MM    MM MM    MM  MM             `Mbd'   MM     MM MM    MM  MM           MM    MM MM'   MM   MM    MM    MM MM       
 MM  MM    MM MM.  ,M9 YM.   MM  YM.  ,          YMP    YM.   ,M9 YM.   MM  MM           MM    MM MM.  ,MM   MM    MM    MM YM    d9 
_MM__MM_  _MM_MMYMMM9   YMMM9MM_  YMMM9           M      YMMMMM9   YMMM9MM__MM_         _MM_  _MM_`YMMM9'Yb._MM_  _MM_  _MM_ YMMMM9  
              MM                                 d'                                                                                  
              MM                             (8),P                                                                                   
             _MM_                             YMM                                                                                    

)";
}