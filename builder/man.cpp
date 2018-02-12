#include <iostream>
#include <map>

//Builder pattern
// do not create object itself
enum Direction{North,South};
class Wall{};
// need it here
class Door;
class Room{
    public:
        Room(int n){
            n_=n;
        }
        virtual void SetSide(Direction dir,Wall* wall){}
        virtual void SetSide(Direction dir,Door* door){}
        int GetNum(){return n_;}
    private:
        int n_;
};
class Maze{
    public:
        virtual Room* RoomNo(int n){
            if(rooms_.find(n)!=rooms_.end()){
                return rooms_[n];
            }
            return 0;
        }
        virtual ~Maze(){}
        void AddRoom(Room* room){
            rooms_[room->GetNum()] = room;
        }
        std::map<int,Room*> rooms_;
};
class Door{
    public:
        Door(Room* r1,Room* r2){
        }
};


// data struction
class MazeBuilder{
    public:
        virtual void BuildMaze(){}
        virtual void BuildRoom(int room){}
        virtual void BuildDoor(int roomFrom,int roomTo){}
        virtual Maze* GetMaze(){return 0;}
    protected:
        MazeBuilder(){};
};

class StandardMazeBuilder:public MazeBuilder{
    public:
        StandardMazeBuilder(){
            _currentMaze =0;
        }
        ~StandardMazeBuilder(){
            delete _currentMaze;
        }
        virtual void BuildMaze(){
            _currentMaze = new Maze;
        }
        virtual Maze* GetMaze(){
            return _currentMaze;
        }
        virtual void BuildRoom(int n){
            if(!_currentMaze->RoomNo(n)){
                Room* room = new Room(n);
                _currentMaze->AddRoom(room);

                room->SetSide(North,new Wall);
                room->SetSide(South,new Wall);
                //...
            }
        }
        virtual void BuildDoor(int n1,int n2){
            Room* r1 = _currentMaze->RoomNo(n1);
            Room* r2 = _currentMaze->RoomNo(n2);
            Door* d = new Door(r1,r2);
            // bug here needing solving recurrent(Solverd!)
            r1->SetSide(CommonWall(r1,r2),d);
            r2->SetSide(CommonWall(r2,r1),d);
        }
    protected:
        Direction CommonWall(Room* r1,Room* r2){return North;}
        Maze* _currentMaze;
};

class CountingMazeBuilder:public MazeBuilder{
    public:
        CountingMazeBuilder(){
            rooms_=0;
            doors_=0;
        }
        virtual void BuildRoom(int ){
            rooms_++;
        }
        virtual void BuildDoor(int ,int){
            doors_++;
        }
        virtual void GetCounts(int &rooms,int & doors)const {
            rooms=rooms_;
            doors=doors_;
        }
    private:
        int rooms_;
        int doors_;

};




// algorithm
class MazeGame{
    public:
        Maze* CreateMaze(MazeBuilder& builder){
            builder.BuildMaze();
            builder.BuildRoom(1);
            builder.BuildRoom(2);
            builder.BuildDoor(1,2);
            return builder.GetMaze();
        }
        Maze* CreateComplexMaze(MazeBuilder& builder){
            builder.BuildRoom(1);
            //...
            builder.BuildRoom(100);
            return builder.GetMaze();
        }
};

int main(){
    Maze* maze;
    MazeGame game;
    StandardMazeBuilder builder;
    game.CreateMaze(builder);
    maze = builder.GetMaze();
    CountingMazeBuilder counting_builder;
    game.CreateMaze(counting_builder);
    int rooms,doors;
    counting_builder.GetCounts(rooms,doors);
    std::cout<<"The maze has "
        <<rooms<<" rooms and "
        <<doors<<" doors"<<std::endl;
    return 0;
}
