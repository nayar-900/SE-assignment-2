#include <iostream>
#include <string>
using namespace std;
class Ant
{
protected:
    string type;
public:
    Ant(const string& antType) : type(antType) {}
    virtual void action() = 0;
    virtual ~Ant() {}
};
class Drone : public Ant
{
public:
    Drone() : Ant("Drone") {}
    void action() override
    {
        cout << "Drone is gathering food.\n";
    }
};
class Warrior : public Ant
{
public:
    Warrior() : Ant("Warrior") {}
    void action() override
    {
        cout << "Warrior is fighting enemies.\n";
    }
};
class Queen : public Ant
{
public:
    Queen() : Ant("Queen") {}
    void action() override
    {
        cout << "Queen is spawning eggs.\n";
    }
};

class AntFactory
{
public:
    static Ant* createAnt(const string& type)
    {
        if (type == "Drone") return new Drone();
        if (type == "Warrior") return new Warrior();
        if (type == "Queen") return new Queen();
        return nullptr;
    }
};
int main()
{
    Ant* drone = AntFactory::createAnt("Drone");
    Ant* warrior = AntFactory::createAnt("Warrior");
    Ant* queen = AntFactory::createAnt("Queen");
    drone->action();
    warrior->action();
    queen->action();
    delete drone;
    delete warrior;
    delete queen;
    return 0;
}
