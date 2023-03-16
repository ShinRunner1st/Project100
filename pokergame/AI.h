#include "Evaluate_Hand.h"

using namespace std;

class AI
{
    long double defmoney;

    public:
    
    vector<int> hand; //max 2
    string name;
    int lv;
    long double money;
    bool fold = false;

    AI(long double);

    long double Raise();
    long double Call(long double);

    int Seclect_Action(vector<int>, int, int);
};

AI::AI(long double amount)
{
    defmoney = amount*15 - amount;
    money = amount*15 - amount;
}

long double AI::Call(long double playerbetamount)
{
    long double temp = money;
    if(money >= 0)
    {
        if(playerbetamount >= money)
        {
            money -= money; //all-in
            return temp;
        }
        else
        {
            money -= playerbetamount;
            return playerbetamount;
        }
    }
    else return 0;
}

long double AI::Raise()
{
    int random = rand()% 100 + 1;
    long double out = money;
    if(money > 2)
    {
        if(money <= defmoney / 2)
        {
            if(random < 10)
            {
                money -= out/10;
                return out/10; // 10% 1/10 money
            }
            else if(random < 40)
            {
                money -= out/2;
                return out/2; // 30% 1/2 money
            }
            else
            {
                money -= out;
                return out; // 60% allin
            }
        }
        else
        {
            if(random < 10)
            {
                money -= out;
                return out; // 10% allin
            }
            else if(random < 50)
            {
                money -= out/2;
                return out/2; // 40% 1/2 money
            }
            else
            {
                money -= out/10;
                return out/10; // 50% 1/10 money
            }
        }
    }
    else 
    {
        money -= out;
        return out; // allin
    }
}

int AI::Seclect_Action(vector<int> table_card, int player_action, int raise) // 0 = Call , 1 = Raise/Bet , 2 = Fold , 3 = Check
{
    if(money > defmoney) defmoney = money;
    int random = rand()% 100 + 1;
    int turn = table_card.size() - 4;
    if(money > 0)
    {
        switch (Evaluate_Hand(table_card, hand)) // (0 -> 1,2,3) (1 -> 0,2) (3 -> 1,2,3)
        {
        case 0: //noting
            if(random < 30) return 2; // 30% fold
            else if(random < 40 && player_action != 1 && raise < 2) return 1; // 10% raise
            else // 60% call
            {
                if(player_action == 0 || player_action == 3) return 3;
                else return 0;
            }
            break;

        case 1: //1 pair
            if(random < 10) return 2; // 10% fold
            else if(random < 50 && player_action != 1 && raise < 2) return 1; // 40% raise
            else if(player_action == 0 || player_action == 3) return 3;
            else return 0; // 50% call
            break;

        case 2: //2 pairs
            if(random < 10) return 2; // 10% fold
            else if(random < 50 && player_action != 1 && raise < 2) return 1; // 40% raise
            else if(player_action == 0 || player_action == 3) return 3;
            else return 0; // 50% call
            break;
        
        case 3: // 3 kind
            if(random < 5) return 2; // 5% fold
            else if(random < 75 && player_action != 1 && raise < 2) return 1; // 70% raise
            else if(player_action == 0 || player_action == 3) return 3;
            else return 0; // 25% call
            break;

        case 4: // staight
            if(random < 5) return 2; // 5% fold
            else if(random < 85 && player_action != 1 && raise < 2) return 1; // 80% raise
            else if(player_action == 0 || player_action == 3) return 3;
            else return 0; // 15% call
            break;

        case 5: // fullhouse
            if(random < 2) return 2; // 2% fold
            else if(random < 82 && player_action != 1 && raise < 2) return 1; // 80% raise
            else if(player_action == 0 || player_action == 3) return 3;
            else return 0; // 13% call
            break;
        
        case 6: // 4 kind
            if(random < 1) return 2; // 1% fold
            else if(random < 91 && player_action != 1 && raise < 2) return 1; // 90% raise
            else if(player_action == 0 || player_action == 3) return 3;
            else return 0; // 9% call
            break;
        
        case 7: // sf
            if(random < 1) return 2; // 1% fold
            else if(random < 91 && player_action != 1 && raise < 2) return 1; // 90% raise
            else if(player_action == 0 || player_action == 3) return 3;
            else return 0; // 9% call
            break;
        
        default:
            cout << "error 1" << endl;
            return 2;
            break;
        }
    }
    else
    {
        return 3; //check only
    }
}

/*
int main()
{
    srand(time(0));
    AI test(100000);
    test.hand = {25,13}; // (K A)
    vector<int> table = {8,1,2,3,4}; // (9 2 3 4 5)

    // Test
    int AI_action = test.Seclect_Action(table,0); // 0 = Call , 1 = Raise , 2 = Fold , 3 = Bet(only player)

    if(AI_action == 0) cout << "Call " << test.Call(); //บอทเลือก call ให้ใช้ Call เพื่อแสดงจำนวนเงินที่บอทลง ปล.หักเงินใน function แล้ว
    else if (AI_action == 1) cout << "Raise " << test.Raise(); //บอทเลือก raise ให้ใช้ Raise เพื่อสุ่มจำนวนเงิน และ แสดงจำนวนเงินที่บอทจะลงเพิ่ม ปล.หักเงินใน function แล้ว
    else if (AI_action == 2) cout << "Fold";

    cout << test.Calc_Hand(table);
    cout << endl;
    for(int i = 0; i < 7; i++) cout << test.FormatNumber(test.Sort(table))[i] << " ";
    cout << endl;
    cout << test.isstraight(test.FormatNumber(test.Sort(table)));

    cout << test.money << endl;
    cout << "Raise " << test.RaiseMoney() << endl;
    cout << test.money;

    return 0;
}*/