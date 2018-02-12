class Point{
    public:
        Point(const int,const int);
};
class Image{
    public:
        void Draw(Point );

};

extern Image* LoadAnImageFile(const char*);


// overload
class ImagePtr{
    public:
        ImagePtr(const char* imageFile);
        virtual ~ImagePtr();
        virtual Image* operator->();
        virtual Image& operator*();
    private:
        Image* LoadImage();
    private:
        Image* image_;
        const char* imageFile_;
};

ImagePtr::ImagePtr(const char* theImageFile){
    imageFile_ = theImageFile;
    image_=0;
}

//lazy load
Image* ImagePtr::LoadImage(){
    if(image_==0){
        image_=LoadAnImageFile(imageFile_);
    }
    return image_;
}
Image* ImagePtr::operator->(){
    return LoadImage();
}
Image& ImagePtr::operator*(){
    return *LoadImage();
}

int main(){
    ImagePtr image = ImagePtr("anImageFileName");
    image->Draw(Point(50,100));
}
