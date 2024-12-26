#include <iostream>
#include <string>
#include <vector>

class OceanCreature;
class Amphibious;
class TerrestrialCreature;
class Bird;
class Waterfowl;

class Visitor
{
public:
    virtual void VisitOceanCr(const OceanCreature*)      = 0;
    virtual void VisitAmphibious(const Amphibious*)      = 0;
    virtual void VisitTerrCr(const TerrestrialCreature*) = 0;
    virtual void VisitBird(const Bird*)                  = 0;
    virtual void VisitWaterfowl(const Waterfowl*)        = 0;
};

#pragma region Creatures

class GenericCreature
{
public:
    virtual void Accept(Visitor*) = 0;
};

class OceanCreature : public GenericCreature
{
public:
    void Accept(Visitor* v) override { v->VisitOceanCr(this); };
    void swim() const { std::cout << "Swimming" << std::endl; }
    void eat() const { std::cout << "Fish is eating" << std::endl; }
};


class Amphibious : public OceanCreature
{
public:
    void Accept(Visitor* v) override { v->VisitAmphibious(this); };
    void walk() const { std::cout << "Walking" << std::endl; }
    virtual void eat() const { std::cout << "Amphibious is eating" << std::endl; }
};


class TerrestrialCreature : public Amphibious
{
public:
    void Accept(Visitor* v) override { v->VisitTerrCr(this); };
    virtual void eat() const { std::cout << "Terrestrial is eating" << std::endl; }
protected:
    using Amphibious::swim;
};


class Bird : public TerrestrialCreature
{
public:
    void Accept(Visitor* v) override { v->VisitBird(this); };
    void fly() const { std::cout << "Flying" << std::endl; }
    virtual void eat() const { std::cout << "Bird is eating" << std::endl; }
protected:
    using TerrestrialCreature::swim;
};


class Waterfowl : public Bird
{
public:
    void Accept(Visitor* v) override { v->VisitWaterfowl(this); };
    virtual void eat() const { std::cout << "Waterfowl is eating" << std::endl; }
    using Bird::swim;
    using Bird::walk;
};

#pragma endregion

class VisitorFeeder : public Visitor
{
public:
    virtual void VisitOceanCr(const OceanCreature* fish)
    {
        std::cout << "Feeding fish" << std::endl;
        fish->swim();
        fish->eat();
        std::cout << "Fish is now fed" << std::endl;
    }
    virtual void VisitAmphibious(const Amphibious* amph)
    {
        std::cout << "Feeding amphibious" << std::endl;
        amph->walk();
        amph->walk();
        amph->eat();
        std::cout << "Amphibious is still hungry" << std::endl;
    }
    virtual void VisitTerrCr(const TerrestrialCreature* ter)
    {

        std::cout << "Feeding terrestrial" << std::endl;
        ter->eat();
        ter->eat();
        ter->eat();
        std::cout << "Terrestrial is now fat" << std::endl;
    }
    virtual void VisitBird(const Bird* bird)
    {
        std::cout << "Feeding bird by throwing food" << std::endl;
        try
        {
            throw "food";
            bird->eat();
        }
        catch (...)
        {
            bird->fly();
            std::cout << "Bird got scared and flew away" << std::endl;
            return;
        }
        
        std::cout << "Bird is fed" << std::endl;
    }
    virtual void VisitWaterfowl(const Waterfowl* wf)
    {
        std::cout << "Feeding waterfowl" << std::endl;
        wf->fly();
        wf->walk();
        wf->swim();
        wf->eat();
        wf->eat();
        std::cout << "Waterfowl is now fed" << std::endl;
    }
};

class VisitorTrainer : public Visitor
{
public:
    virtual void VisitOceanCr(const OceanCreature* fish)
    {
        std::cout << "Traing fish" << std::endl;
        fish->swim();
        fish->swim();
        std::cout << "Fish is now better at swimming" << std::endl;
    }
    virtual void VisitAmphibious(const Amphibious* amph)
    {
        std::cout << "Traing amphibious" << std::endl;
        amph->swim();
        amph->walk();
        std::cout << "Amphibious is now better at swimming and walking" << std::endl;
    }
    virtual void VisitTerrCr(const TerrestrialCreature* ter)
    {
        std::cout << "Traing terrestrial" << std::endl;
        ter->walk();
        ter->walk();
        std::cout << "Terrestrial is now better at walking" << std::endl;
    }
    virtual void VisitBird(const Bird* bird)
    {
        std::cout << "Traing bird" << std::endl;
        bird->fly();
        bird->walk();
        std::cout << "Bird is now better at flying" << std::endl;
    }
    virtual void VisitWaterfowl(const Waterfowl* wf)
    {
        std::cout << "Traing waterfowl" << std::endl;
        wf->fly();
        wf->walk();
        wf->swim();
        std::cout << "Waterfowl is now better at everything" << std::endl;
    }
};

int main()
{
    std::vector<GenericCreature*> zoo;
    OceanCreature fish;
    Amphibious beaver;
    TerrestrialCreature cat;
    Bird sparrow;
    Waterfowl seagull;
    zoo.push_back(&fish);
    zoo.push_back(&beaver);
    zoo.push_back(&cat);
    zoo.push_back(&sparrow);
    zoo.push_back(&seagull);
    Visitor* feeder = new VisitorFeeder();
    Visitor* trainer = new VisitorTrainer();


    std::cout << "Feeder visiting zoo" << std::endl;
    for (auto iter = zoo.begin(); iter != zoo.end(); iter++)
    {
        (*iter)->Accept(feeder);
        std::cout << std::endl;
    }

    std::cout << "Trainer visiting zoo" << std::endl;
    for (auto iter = zoo.begin(); iter != zoo.end(); iter++)
    {
        (*iter)->Accept(trainer);
        std::cout << std::endl;
    }

    return 0;
}