#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

const double INIT_TOTAL = 0.0;
constexpr double CHOCO_DISCOUT = 9.25 - 8.5;

struct Item {
    string name;
    double price;
};


struct TestPromotion{

    //return discounted amount
    double operator()(vector<Item *> &pitems) const {
            int chocolate_cake_no = 0;
            double total = 0.0;
            double ret = 0.0;

            for (auto i : pitems)
            {
                if (0 == i->name.compare("Chocolate Cake"))
                    chocolate_cake_no++;

                total += i->price;
            }

            if (2 <= chocolate_cake_no)
            {
                ret += (CHOCO_DISCOUT * chocolate_cake_no);
                total -= ret;
            }

            if (60.0 < total)
                ret += total * 0.1;

            return ret;
    }
};


template<typename Promo>
class CheckOut {
public:
    CheckOut() : total{ INIT_TOTAL} {}
    void Scan(Item *i);
    double Total();

private:
    vector<Item *> pitems;
    Promo promo;
    double total;
};

template<typename Promo>
void CheckOut<Promo>::Scan(Item *i)
{
    pitems.push_back(i);
    total = INIT_TOTAL;
}

template<typename Promo>
double CheckOut<Promo>::Total()
{
    if (INIT_TOTAL == total)
    {
        total = 0.0;
        for (auto i : pitems)
            total += i->price;

        //cout << "debug total w/o discout = " << total << endl;
        total -= promo(pitems);

        //rounding at 2 decimal point
        total = round(total * 100.0) / 100.0;
        //cout << "debug total w discout = " << total << ", discout =" << promo(pitems) << endl;
    }
    
    return total;
}

int main() 
{
    // make item map table
    map<int, Item> items
    {
        {1, {"Chocolate Cake", 9.25}},
        {2, {"Whisky", 45.0}},
        {3, {"T-Shirt", 19.95}}
    };

    auto t = new CheckOut<TestPromotion>;
    t->Scan(&items[1]);
    t->Scan(&items[2]);
    t->Scan(&items[3]);
    cout << "test 1 total = " << t->Total() << endl;
    delete t;

    t = new CheckOut<TestPromotion>;
    t->Scan(&items[1]);
    t->Scan(&items[3]);
    t->Scan(&items[1]);
    cout << "test 2 total = " << t->Total() << endl;
    delete t;

    t = new CheckOut<TestPromotion>;
    t->Scan(&items[1]);
    t->Scan(&items[2]);
    t->Scan(&items[1]);
    t->Scan(&items[3]);
    cout << "test 3 total = " << t->Total() << endl;
    delete t;


    //wait digit input before exit
    int i;
    cin >> i;

}