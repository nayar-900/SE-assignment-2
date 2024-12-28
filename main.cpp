#include <iostream>
using namespace std;
class Meadow
{
private:
    static Meadow* instance;
    Meadow()
    {
        cout << "Meadow created.\n";
    }

public:

    static Meadow* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Meadow();
        }
        return instance;
    }
    void simulate()
    {
         cout << "Simulating Meadow ...\n";
    }
};
Meadow* Meadow::instance = nullptr;
int main()
{
    Meadow* meadow1 = Meadow::getInstance();
    Meadow* meadow2 = Meadow::getInstance();
    meadow1->simulate();
    if (meadow1 == meadow2)
    {
        cout << "Singleton pattern works. Only one meadow exists.\n";
    }
    return 0;
}
