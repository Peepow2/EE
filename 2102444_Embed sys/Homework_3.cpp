#include <iostream>

namespace mySpace
{
    class Square
    {
        private:
            float length_;

        public:
            Square()
            {
                setLength(1);
            }

            void setLength(float length)
            {
                if (length > 0)
                    length_ = length;
            }

            float area()
            {
                return length_ * length_;
            }
    };
}

int main()
{
    mySpace::Square X;
    mySpace::Square &Y = X;
    Y.setLength(4.0);

    std::cout << "Hello World!\n";
    std::cout << "Set Y's length to 4.\n";
    std::cout << "X's area is " << X.area() << ".\n";
    std::cout << "Y's Address is " << &Y << ".\n";
    std::cout << "X's Address is " << &X << ".\n";

    mySpace::Square *p;
    p = new mySpace::Square();

    std::cout << "p's Address is " << &p << ".\n";
    std::cout << "p points to " << p << ".\n";
    std::cout << "p->area() is " << p->area() << ".\n\n";

    mySpace::Square SSquare[] = {mySpace::Square(), 
                                 mySpace::Square(), 
                                 mySpace::Square()};

    for(int i=0;i<3;i++)
        SSquare[i].setLength(float(i+1));

    for(int i=0;i<3;i++)
    {
        std::cout << "SSquare[" << i << "] is at " << &SSquare[i]
                  << " with the area of " << SSquare[i].area() << ".\n";
    }
    std:: cout << "\n";

    mySpace::Square *HSquare;
    HSquare = new mySpace::Square[3];

    for(int i=0;i<3;i++)
        HSquare[i].setLength(float(i+1));

    for(int i=0;i<3;i++)
    {
        std::cout << "HSquare[" << i << "] is at " << &HSquare[i]
                      << " with the area of " << HSquare[i].area() << ".\n";
    }

    delete [] HSquare;
    delete p;

    return 0;
} // https://onlinegdb.com/lNYQk1aO-
