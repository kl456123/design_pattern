#include <iostream>
#include <list>
class Composite;
class Component{
    public:
        virtual Composite* GetComposite(){return 0;}
};


class Composite:public Component{
    public:
        void Add(Component* );
        virtual Composite* GetComposite(){return this;}
};

class Leaf:public Component{
    //...
};

/**
 *equipment
 *
 */
class Equipment{
    public:
        virtual ~Equipment(){}
        const char* Name(){return name_;}
        virtual Watt Power(){}
        virtual Currency NetPrice(){}
        virtual void Add(Equipment*);
        virtual void Remove(Equipment*);
        virtual Iterator* CreateIterator();
    protected:
        Equipment(const char* name){name_ = name;}
    private:
        const char* name_;
};

class FloppyDisk:public Equipment{
    public:
        FloppyDisk(const char* name):Equipment(name){}
        virtual ~FloppyDisk();
        virtual Watt Power();
        virtual Currency NetPrice();
};

class CompositeEquipment: public Equipment{
    public:
        virtual ~CompositeEquipment();
        virtual Watt Power();
        virtual Currency NetPrice();
        virtual void Add(Equipment*);
        virtual void Remove(Equipment*);
        virtual Iterator* CreateIterator(){
            Iterator* i = CreateIterator();
            Currency total = 0;

            for(i->First();!i->IsDone();i->Next()){
                total += i->CurrentItem()->NetPrice();
            }
            // after new
            delete i;
            return total;
        }
    protected:
        CompositeEquipment(const char*);
    private:
        std::list<Equipment> equiment_;
};


class Chassis: public CompositeEquipment{
    public:
        Chassis(const char*){
        }
        virtual ~Chassis(){
        }
        virtual Watt Power(){
        }
        virtual Currency NetPrice(){
        }
        virtual Currency DiscountPrice(){
        }
};
class Cabinet:public CompositeEquipment{
    public:
        Cabinet(const char* name){
            // bug here
            name_= name;
        }
    private:
        const char* name_;
};

void client(){
    Cabinet* cabinet = new Cabinet("PC Cabinet");
    Chassis* chassis = new Chassis("PC Chassis");
    cabinet->Add(chassis);
    Bus* bus = new Bus("MCA Bus");
    bus->Add(new Card("16Mbs Token Ring"));

    chassis->Add(bus);
    chassis->Add(new FloppyDisk("3.5in Floppy"));
    chassis->NetPrice();
}



int main(){
    Composite* aComposite = new Composite;
    Leaf* aLeaf = new Leaf;

    Component* aComponent;
    Composite* test;
    aComponent = aComposite;
    // composite
    if(test = aComponent->GetComposite()){
        test->Add(new Leaf);
    }
    aComponent = aLeaf;
// leaf
    if(test = aComponent->GetComposite()){
        test->Add(new Leaf);
    }
    return 0;
}
