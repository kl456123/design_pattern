class GlyphContext;
class Glyph{
    public:
        virtual ~Glyph();
        virtual void Draw(Window*, GlyphContext&);
        virtual void SetFont(Font*, GlyphContext&);

        virtual Font* GetFont(GlyphContext&);

        virtual void First(GlyphContext&);
        virtual void Next(GlyphContext&);
        virtual bool IsDone(GlyphContext&);
        virtual Glyph* Current(GlyphContext&);
        virtual void Insert(Glyph*, GlyphContext&);
        virtual void Remove(GlyphContext&);
    protected:
        Glyph();
};

// GlyphContext acts as a repository of extrinsic state
class Character:public Glyph{
    public:
        Character(char);
        virtual void Draw(Window*, GlyphContext&);
    private:
        char charcode_;
};

class GlyphContext{
    public:
        GlyphContext();
        virtual ~GlyphContext();
        virtual void Next(int step = 1);
        virtual void Insert(int quantity = 1);

        virtual Font* GetFont();
        virtual void SetFont(Font*, int span = 1);
    private:
        int index_;
        BTree* fonts_;
};
const int NCHARCODES = 128;
class Row{};
class Column{};
class GlyphFactory{
    public:
        GlyphFactory();
        virtual ~GlyphFactory(){}
        virtual Character* CreateCharacter(char);
        virtual Row* CreateRow();
        virtual Column* CreateColumn();
        //...
    private:
        Character* character_[NCHARCODES];
};

GlyphFactory::GlyphFactory(){
    for(int i = 0;i<NCHARCODES;++i){
        character_[i] = 0;
    }
}

Character* GlyphFactory::CreateCharacter(char c){
    if(!character_[c]){
        character_[c]=new Character(c);
    }
    return character_[c];
}

Row* GlyphFactory::CreateRow(){
    return new Row;
}

Column* GlyphFactory::CreateColumn(){
    return new Column;
}

int main(){
    GlyphContext gc;
    Font* times12 = new Font("Times-Roman-12");
    gc.SetFont(times12,6);

    gc.Insert(6);
}
