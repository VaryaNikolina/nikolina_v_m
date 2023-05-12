#include <iostream>

class Orto{
    public:
    
    Point() = default;
    Point(double x, double y){
        x_(x);
        y_(y);
    };

    //bool operator==(Point& rhs){
    //    return ;
    //};
    //bool operator==(Point & rhs){
    //    return ;
    //};

    double Get_x() const{
        return x_;
    };
    double Get_y() const{
        return y_;
    }

    std::ostream& write_to(std::ostream& ostr){
        ostr << x << " " << y;
        return ostr;
    };

    std::ostream& read_from(std::istream istr){

    };

    inline std::ostream& operator (std::ostream& ostr, const Point& rhs){
        return rhs.write_to( & ostr);
    }

    private:

};

class Quad{
    
};

class Rect{

};

class Square{

};

int main(){

}