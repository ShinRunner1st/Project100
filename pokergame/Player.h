#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>

using namespace std;

class Player
{
public:

    vector<int> hand; //max 2
    string name;
    int lv;
    long double money;
    bool fold = false;

    Player(string);
    ~Player();

    void player_import(string);
    void player_export();
};

Player::Player(string n)
{
    player_import(n);
}

Player::~Player()
{
    player_export();
}

void Player::player_import(string playerName) {

    ifstream file("Savegame.txt");
    string line;
    
    while (getline(file, line)) {
        
        char n[256];
        long double cash;
        sscanf(line.c_str(), "%s %Lf", n, &cash);

        if (playerName == n) {
            
            name = playerName;
            money = cash;
            file.close();
            return;
        }

    }
    file.close();

    money = 20000; //new account
   
    ofstream outfile("Savegame.txt", ios_base::app);
    outfile << playerName << " " << money << endl;
    outfile.close();
    
    name = playerName;
}

void Player::player_export()
{
    ifstream input_flie("Savegame.txt"); //read file
    stringstream temp_flie; //temp file
    string textline;
    char nameTemp[256];

    while (getline(input_flie, textline)) //linear search
    {
        sscanf(textline.c_str(), "%s", nameTemp); //search name
        if (nameTemp == name) temp_flie << name << " " << money << endl; //if found write current playername and money to tempflie
        else temp_flie << textline << endl; //write same line to temp file
    }
    input_flie.close();

    ofstream output_flie("Savegame.txt"); //open file
    output_flie << temp_flie.rdbuf(); //copy temp to file
    output_flie.close();
}

// import and export data function

