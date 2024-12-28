#include <iostream>
#include <string>
using namespace std;
class AntFarm
{
private:
    string name;
    int numRooms;

public:
    AntFarm() : name(""), numRooms(0) {}
    void setName(const string& farmName)
    {
        name = farmName;
    }
    void setRooms(int rooms)
    {
        numRooms = rooms;
    }
    void display() const
    {
        cout << "AntFarm: " << name << ", Rooms: " << numRooms << "\n";
    }
};
class AntFarmBuilder
{
private:
    AntFarm* antFarm;

public:
    AntFarmBuilder()
    {
        antFarm = new AntFarm();
    }
    void setName(const string& name)
    {
        antFarm->setName(name);
    }
    void setRooms(int rooms)
    {
        antFarm->setRooms(rooms);
    }
    AntFarm* getAntFarm()
    {
        return antFarm;
    }
};
int main()
{
    AntFarmBuilder builder;
    builder.setName("Alpha Colony");
    builder.setRooms(5);
    AntFarm* farm = builder.getAntFarm();
    farm->display();
    delete farm;
    return 0;
}
