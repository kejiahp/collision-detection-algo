
class Application
{
protected:
    int height;
    int width;
    float timeinterval;
    float nRange;
public:
    virtual void initGraphics();
    virtual void display();
    virtual void resize(int width, int height);
    virtual void update();
    float getTimeinterval();
    void setTimeinterval(float timeint);
    int getheight();
    int getwidth();
};



    

