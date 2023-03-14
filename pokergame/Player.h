#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<fstream>

using namespace std;

class Player //test
{
    public:
    
    vector<int> hand; //max 2
    string name;
    int lv;
    long double money;
    bool fold = false;

    Player();
    ~Player();
};

Player::Player()
{
    // import data to money
    ifstream input_flie("Save.txt");
    input_flie >> fixed >> money;
    input_flie.close();
}

Player::~Player()
{
    ofstream output_flie("Save.txt");
    output_flie << fixed << money;
    output_flie.close();
}
// import and export data funtion