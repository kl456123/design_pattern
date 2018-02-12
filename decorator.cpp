
class VisualComponent{
    public:
        VisualComponent();
        virtual void Draw();
        virtual void Resize();
};


class Decorator:public VisualComponent{
    public:
        Decorator(VisualComponent*);
        virtual void Draw();
        virtual void Resize();
    private:
        VisualComponent* component_;
};

void Decorator::Draw(){
    component_->Draw();
}

void Decorator::Resize(){
    component_->Resize();
}

class BorderDecorator:public Decorator{
    public:
        BorderDecorator(VisualComponent*,int borderWidth);
        virtual void Draw();
        virtual void Resize();
    private:
        void DrawBorder(int);
    private:
        int width_;
};

void BorderDecorator::Draw(){
    Decorator::Draw();
    DrawBorder(width_);
}

class ScrollDecorator:public Decorator{
    public:
        ScrollDecorator(VisualComponent*);

};

class Window{
    public:
        void SetContents(VisualComponent*);
};
class TextView:public VisualComponent{};
void Window::SetContents(VisualComponent* contents){
}

int main(){
    Window* window = new Window;
    TextView* textview = new TextView;
    window->SetContents(textview);
    window->SetContents(new BorderDecorator(new ScrollDecorator(textview),1));
}


