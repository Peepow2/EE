#include <iostream>

namespace mySpace
{
    class Square
    {
        private:
            float length_;
        
        public:
            void setLength(float length)
            {
                length_ = length;
            }
        
            float area()
            {
                return length_ * length_ ;
            }
    };
}


int main()
{
    mySpace::Square square;

    square.setLenth(10.0);
    std::cout << square.area();
    
    return 0;
}
