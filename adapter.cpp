#include <iostream>

class Coord{
    public:
        Coord operator+(Coord& coord){}
};
class Point{
    public:
        Point(Coord coord1,Coord coord2){}
};
class Shape{
    public:
        Shape(){}
        virtual void BoundingBox(Point& bottomLeft,Point& topRight)const {}
        virtual Manipulator* CreateMainpulator()const;
};

class TextView{
    public:
        TextView();
        void GetOrigin(Coord& x, Coord& y)const;
        void GetExtent(Coord& width,Coord& height)const;
        virtual bool IsEmpty()const{}
};

class TextShape:public Shape,private TextView{
    public:
        TextShape();
        virtual void BoundingBox(Point& bottomLeft,Point& topRight)const{
            Coord bottom,left,width,height;
            this->GetOrigin(bottom,left);
            this->GetExtent(width,left);

            bottomLeft = Point(bottom,left);
            topRight = Point(bottom+height,left+width);
        }
        virtual bool IsEmpty() const{
            return TextView::IsEmpty();
        }
        virtual Manipulator* CreateManipulator()const{
            return new TextManipulator(this);
        }
};

// another approach

class TextShape_:public Shape{
    public:
        TextShape_(TextView* t){
            text_ = t;
        }
        void BoundingBox(Point& bottomLeft,Point& topRight)const{
            Coord bottom,left,width,height;
            text_->GetOrigin(bottom,left);
            text_->GetExtent(bottom,left);
            bottomLeft = Point(bottom,left);
            topRight = Point(bottom+ height,left+width);
        }
        bool IsEmpty(){
            return text_->IsEmpty();
        }
        virtual Manipulator* CreateManipulator()const{
            return new TextManipulator(this);
        }
    private:
        TextView* text_;
};
