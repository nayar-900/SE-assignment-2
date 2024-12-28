#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
class Ant
{
protected:
    string type;
public:
    Ant(const string& antType) : type(antType) {}
    virtual void takeAction() = 0;
    virtual ~Ant() {}
};
class Drone : public Ant
{
public:
    Drone() : Ant("Drone") {}
    void takeAction() override
    {
        cout << "Drone is gathering food.\n";
        cout << endl;
    }
};
class Warrior : public Ant
{
public:
    Warrior() : Ant("Warrior") {}
    void takeAction() override
    {
        cout << "Warrior is fighting.\n";
        cout << endl;
    }
};
class Queen : public Ant
{
public:
    Queen() : Ant("Queen") {}
    void takeAction() override
    {
        cout << "Queen is spawning eggs.\n";
        cout << endl;
    }
};
class Mediator
{
private:
    vector<Ant*> ants;
public:
    void addAnt(Ant* ant)
    {
        ants.push_back(ant);
    }
    void simulateTick()
    {
        cout << "Simulating tick...\n";
        cout << endl;
        for (size_t i = 0; i < ants.size(); i++)
        {
            ants[i]->takeAction();
        }
    }
    ~Mediator()
    {
        for (Ant* ant : ants)
        {
            delete ant;
        }
    }
};
int main()
{
    Mediator mediator;
    mediator.addAnt(new Drone());
    mediator.addAnt(new Warrior());
    mediator.addAnt(new Queen());
    mediator.simulateTick();
    return 0;
}
