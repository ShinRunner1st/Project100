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

    Player(long double, string);
    ~Player();

    void player_export(string , long double );
};

Player::Player(long double x, string y)
{
    name = y;
    money = x;
    // import data to money
    //ifstream input_flie("Save.txt");
    //input_flie >> fixed >> money;
    //input_flie.close();
}

Player::~Player()
{
    player_export(name, money);

}

void Player::player_export(string playername, long double m)
{
    ifstream input_flie("Savegame.txt"); //read file
    stringstream temp_flie; //temp file
    string textline;
    char nameTemp[256];

    while (getline(input_flie, textline))
    {
        sscanf(textline.c_str(), "%s", nameTemp); //search name
        if (nameTemp == playername) temp_flie << playername + " " << m << endl; //if found write current playername and money to tempflie
        else temp_flie << textline << endl; //write same line to temp file
    }
    input_flie.close();

    ofstream output_flie("Savegame.txt"); //open file
    output_flie << temp_flie.rdbuf(); //copy temp to file
    output_flie.close();
}

// import and export data function

