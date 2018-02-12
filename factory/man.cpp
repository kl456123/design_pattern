#include <iostream>
#include <string>

class Base{
    public:
        virtual void print()=0;

};
class Derived: public Base{
    public:
        void print(){
        }
};

Base* f(){
    return new Derived();
}

// products text
class Text{
    public:
        Text(){
        }
        virtual void printOperatorSystem()=0;
        // private:
        // const std::string operator_systerm_;
};


class UnixText: public Text{
    public:
        UnixText(){
        }
        void printOperatorSystem(){
            std::cout<<"UniText"<<std::endl;
        }
};

class WindowsText: public Text{
    public:
        WindowsText(){
        }
        void printOperatorSystem(){
            std::cout<<"WindowsText"<<std::endl;
        }
};

// products botton
class Botton{
    public:
        virtual void printOperatorSystem()=0;
};

class WindowsBotton: public Botton{
    public:
        void printOperatorSystem(){
            std::cout<<"WindowsBotton"<<std::endl;
        }
};
class UnixBotton: public Botton{
    public:
        void printOperatorSystem(){
            std::cout<<"UnixBotton"<<std::endl;
        }

};

// factory
class AbstractFactory{
    public:
        virtual Botton* createBotton()=0;
        virtual Text* createText()=0;
};


class UnixFactory: public AbstractFactory{
    public:
        Botton* createBotton(){
            return new UnixBotton();
        }
        Text* createText(){
            return new UnixText();
        }
};
class WindowsFactory: public AbstractFactory{
    public:
        Botton* createBotton(){
            return new WindowsBotton();
        }
        Text* createText(){
            return new WindowsText();
        }
};


// maze problem
enum Direction{North,East,South,West};

class Spell{};
class Wall{};
class BombedWall:public Wall{};
class Room{
    public:
        Room(int n){}
        virtual void SetSide(Direction dir,Wall* aWall){
        }
        // virtual void SetSide(Direction dir,Wall* aWall){
        // }
};
class RoomWithABomb:public Room{
    public:
        RoomWithABomb(int n):Room(n){}
};
class EnchantedRoom:public Room{
    public:
        EnchantedRoom(int n,Spell* spell):Room(n){}
};
class Door{
    public:
        Door(Room* r1 , Room* r2){}
};
class DoorNeedingSpell:public Door{
    public:
        DoorNeedingSpell(Room* r1,Room* r2):Door(r1,r2){}
};
class Maze{
    public:
        virtual void AddRoom(Room* r){}
};

class MazeFactory {
    public:
        // MazeFactory();
        virtual Maze* MakeMaze() const
        { return new Maze; }
        virtual Wall* MakeWall() const
        { return new Wall; }
        virtual Room* MakeRoom(int n) const
        { return new Room(n); }
        virtual Door* MakeDoor(Room* r1, Room* r2) const
        { return new Door(r1, r2); }
};


class EnchantedMazeFactory:public MazeFactory{
    public:
        EnchantedMazeFactory(){}
        virtual Room* MakeRoom(int n)const {
            return new EnchantedRoom(n,CastSpell());
        }
        virtual Door* MakeDoor(Room* r1,Room* r2)const
        {return new DoorNeedingSpell(r1,r2);}
    protected:
        Spell* CastSpell()const {}
};

class BombedMazeFactory:public MazeFactory{
    public:
        Wall* MakeWall()const {
        return new BombedWall;
        }
        Room* MakeRoom(int n)const {
            return new RoomWithABomb(n);
        }
};
class MazeGame{
    public:
        // two rooms with a door between them
        Maze* CreateMaze(MazeFactory& factory){
            Maze* aMaze = factory.MakeMaze();
            Room* r1 = factory.MakeRoom(1);
            Room* r2 = factory.MakeRoom(2);
            Door* aDoor = factory.MakeDoor(r1,r2);

            aMaze->AddRoom(r1);
            aMaze->AddRoom(r2);

            r1->SetSide(North,factory.MakeWall());
            // r1->SetSide(East,aDoor);
            r1->SetSide(South,factory.MakeWall());
            r1->SetSide(West,factory.MakeWall());

            r2->SetSide(North,factory.MakeWall());
            r2->SetSide(East,factory.MakeWall());
            r2->SetSide(South,factory.MakeWall());
            // r2->SetSide(West,factory.MakeWall());
            return aMaze;
        }
};



int main(){
    UnixFactory* unix_factory = new UnixFactory();
    Text* unix_text = unix_factory->createText();
    unix_text->printOperatorSystem();
    Botton* unix_botton = unix_factory->createBotton();
    unix_botton->printOperatorSystem();

    // the same as before
    WindowsFactory* windows_factory = new WindowsFactory();
    windows_factory->createText();
    windows_factory->createBotton();

    MazeGame game;
    BombedMazeFactory factory;
    game.CreateMaze(factory);

    return 0;
}
