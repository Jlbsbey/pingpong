class Figure{
    protected:
        double x_;
        double y_;
        double dx_;
        double dy_;
    public:
        Figure(){}
        virtual ~Figure(){}
        virtual void Reset();
        virtual void Draw();
        virtual void Move();
        virtual double getx(){};
        virtual double gety(){};
        virtual double geta();
};