#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<bits/stdc++.h>
#include<algorithm>

using namespace std;

class Player //test
{
    public:
    
    vector<int> hand; //max 2
    string name;
    int lv;
    int money;
    bool fold = false;

    Player();
    ~Player(){};
};

Player::Player()
{
    // import data to money
    money = 1000;
}

// import and export data funtion