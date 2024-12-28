#include <iostream>
#include <string>
using namespace std;
class Ant
{
protected:
    string description;
public:
    Ant(const string& desc) : description(desc) {}
    virtual string getDescription() const
    {
        return description;
    }
    virtual ~Ant() {}
};
class AntDecorator : public Ant
{
protected:
    Ant* baseAnt;
public:
    AntDecorator(Ant* ant) : Ant(ant->getDescription()), baseAnt(ant) {}
    virtual string getDescription() const override
    {
        return baseAnt->getDescription();
    }
    virtual ~AntDecorator()
    {
        delete baseAnt;
    }
};
class StrengthDecorator : public AntDecorator
{
private:
    int strength;
public:
    StrengthDecorator(Ant* ant, int str) : AntDecorator(ant), strength(str) {}
    string getDescription() const override
    {
        return baseAnt->getDescription() + ", Strength: " + std::to_string(strength);
    }
};
class SpeedDecorator : public AntDecorator
{
private:
    int speed;
public:
    SpeedDecorator(Ant* ant, int spd) : AntDecorator(ant), speed(spd) {}
    string getDescription() const override
    {
        return baseAnt->getDescription() + ", Speed: " + std::to_string(speed);
    }
};
int main()
{
    Ant* baseAnt = new Ant("Basic Ant");
    Ant* strongAnt = new StrengthDecorator(baseAnt, 10);
    Ant* fastStrongAnt = new SpeedDecorator(strongAnt, 5);
    cout << fastStrongAnt->getDescription() << "\n";
    delete fastStrongAnt;
    return 0;
}
