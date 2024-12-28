#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

class Meadow
{
private:
    static Meadow* instance;
    map<int, string> colonies;
    Meadow() { cout << "Meadow created.\n"; }

public:
    static Meadow* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Meadow();
        }
        return instance;
    }

    void addColony(int id, const string& species)
    {
        colonies[id] = species;
    }

    void removeColony(int id)
    {
        colonies.erase(id);
    }

    void displayColonies()
    {
        cout << "Colonies in Meadow:\n";
        for (const auto& colony : colonies)
        {
            cout << "ID: " << colony.first << ", Species: " << colony.second << "\n";
        }
    }

    bool isOnlyOneColony()
    {
        return colonies.size() <= 1;
    }

    ~Meadow()
    {
        cout << "Meadow destroyed.\n";
    }
};

Meadow* Meadow::instance = nullptr;

class Ant
{
protected:
    string type;

public:
    Ant(const string& antType) : type(antType) {}
    virtual void takeAction() = 0;
    virtual ~Ant() {}
    string getType() const { return type; }
};

class Drone : public Ant
{
public:
    Drone() : Ant("Drone") {}
    void takeAction() override
    {
        cout << "Drone is gathering food.\n";
    }
};

class Warrior : public Ant
{
public:
    Warrior() : Ant("Warrior") {}
    void takeAction() override
    {
        cout << "Warrior is fighting enemies.\n";
    }
    void battle(Warrior* opponent)
    {
        cout << "Warrior battling another Warrior!\n";
        if (rand() % 2 == 0)
        {
            cout << "Winner gets stronger and kills the loser.\n";
            delete opponent;
        }
        else
        {
            cout << "Winner gets stronger and kills the loser.\n";
            delete this;
        }
    }
};

class Queen : public Ant
{
public:
    Queen() : Ant("Queen") {}
    void takeAction() override
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

class Room
{
private:
    int capacity;
    int antsResting;

public:
    Room(int cap) : capacity(cap), antsResting(0) {}
    bool canRest()
    {
        return antsResting < capacity;
    }
    void restAnt()
    {
        if (canRest())
        {
            antsResting++;
            cout << "Ant is resting in the room.\n";
        }
    }
    void consumeFood()
    {
        cout << "Ants in the room are consuming food.\n";
    }
    void clearRoom()
    {
        antsResting = 0;
    }
};

template <typename T>
class AntFarm
{
private:
    vector<Ant*> ants;
    vector<Room> rooms;

public:
    void addAnt(Ant* ant)
    {
        ants.push_back(ant);
    }
    void addRoom(Room room)
    {
        rooms.push_back(room);
    }
    void simulateTick()
    {
        for (Ant* ant : ants)
        {
            ant->takeAction();
        }
        for (Room& room : rooms)
        {
            if (room.canRest())
            {
                room.restAnt();
            }
            room.consumeFood();
        }
    }
    void displaySummary()
    {
        cout << "AntFarm Summary:\n";
        cout << "Total Ants: " << ants.size() << "\n";
        for (Ant* ant : ants)
        {
            cout << "- " << ant->getType() << "\n";
        }
        cout << "Total Rooms: " << rooms.size() << "\n";
    }
    ~AntFarm()
    {
        for (Ant* ant : ants)
        {
            delete ant;
        }
    }
};

void handleCLI()
{
    srand(time(0));
    Meadow* meadow = Meadow::getInstance();
    map<int, AntFarm<Ant>*> farms;
    int colonyCount = 0;

    while (true)
    {
        cout << "\n--- Menu ---\n";
        cout << "1. Display all colonies\n";
        cout << "2. Spawn a new colony\n";
        cout << "3. Give resources to a colony\n";
        cout << "4. Simulate ticks\n";
        cout << "5. Display colony summary\n";
        cout << "6. Exit simulation\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            meadow->displayColonies();
        }
        else if (choice == 2)
        {
            int x, y;
            cout << "Enter the coordinates (x, y) and species: ";
            string species;
            cin >> x >> y >> species;
            int id = ++colonyCount;
            AntFarm<Ant>* farm = new AntFarm<Ant>();
            farm->addAnt(AntFactory::createAnt("Queen"));
            farms[id] = farm;
            meadow->addColony(id, species);
            cout << "Spawned colony " << id << " of species " << species << " at (" << x << ", " << y << ").\n";
        }
        else if (choice == 3)
        {
            int id;
            string type;
            int count;
            cout << "Enter colony ID, ant type, and count: ";
            cin >> id >> type >> count;
            if (farms.find(id) != farms.end())
            {
                for (int i = 0; i < count; ++i)
                {
                    farms[id]->addAnt(AntFactory::createAnt(type));
                }
                cout << "Added " << count << " " << type << "(s) to colony " << id << ".\n";
            }
            else
            {
                cout << "Colony " << id << " not found.\n";
            }
        }
        else if (choice == 4)
        {
            int ticks;
            cout << "Enter the number of ticks: ";
            cin >> ticks;
            cout << "Simulating " << ticks << " tick(s):\n";
            for (int t = 0; t < ticks; ++t)
            {
                for (auto& pair : farms)
                {
                    pair.second->simulateTick();
                }
            }
        }
        else if (choice == 5)
        {
            int id;
            cout << "Enter colony ID to display summary: ";
            cin >> id;
            if (farms.find(id) != farms.end())
            {
                farms[id]->displaySummary();
            }
            else
            {
                cout << "Colony " << id << " not found.\n";
            }
        }
        else if (choice == 6)
        {
            cout << "Exiting the simulation...\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }

    }

    for (auto& pair : farms)
    {
        delete pair.second;
    }
}

int main()
{
    handleCLI();
    return 0;
}
