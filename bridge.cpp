class View;
class Coord{
    public:
        Coord(const Coord& other){}
};
class Point{
    public:
        Point(const Coord& x,const Coord& y):x_(x),y_(y){}
        Coord X()const {return x_;}
        Coord Y()const{return y_;}
    private:
        const Coord x_;
        const Coord y_;
};

class WindowImp{
    public:
        virtual void DeviceBitmap(const char* name,const float a, const float b){}
        virtual void DeviceRect(const Coord x1,const Coord y1,const Coord x2,const Coord y2){
        }
};

// system-specific state
class XWindowImp:public WindowImp{
    public:
        XWindowImp(){}
        virtual void DeviceRect(Coord x1,Coord y1,Coord x2,Coord y2){
            int x = round(min(x1,x2));
            //...
            XDrawRectangle();
        }
        // remainder of public interface...
    private:
        Display* dpy_;
};

class PMWindowImp:public WindowImp{
    public:
        PMWindowImp(){}
        virtual void DeviceRect(){}
};



class Window{
    public:
        Window(View* contents){
        }
        virtual void DrawContents(){}
        void DrawRect(const Point& p1,const Point& p2){
            WindowImp* imp= GetWindowImp();
            imp->DeviceRect(p1.X(),p1.Y(),p2.X(),p2.Y());
        }
    protected:
        virtual WindowImp* GetWindowImp(){
            if(imp_==0){
            return WindowSystemFactory::Instance()->MakeWindowImp();
            }
            return imp_;
        }
    private:
        WindowImp* imp_;
        View* contents_;
};






class ApplicationWindow:public Window{
    public:
        virtual void DrawContents();
};


class IconWindow: public Window{
    public:
        virtual void DrawContents(){
            WindowImp* imp = GetWindowImp();
            if(imp!=0){
                imp->DeviceBitmap(bitmapName_,0.0,0.0);
            }
        }
    private:
        const char* bitmapName_;
};
