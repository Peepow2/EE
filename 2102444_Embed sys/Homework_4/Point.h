#pragma once

#include <iostream>
#include <cmath>

using std::cout;

namespace mySpace 
{
    class Point 
    {
        private:
            float x_, y_;
            
        public:
            // Default constructor
            Point(float x = 1.0, float y = 1.0) : x_(x), y_(y) 
            {
                std::cout << "Default constructor called: (" << x_ << ", " << y_ << ")" << std::endl;
            }
            
            // Copy constructor
            Point(const Point& other) : x_(std::abs(other.x_)), y_(std::abs(other.y_)) 
            {
                std::cout << "Copy constructor called: (" << x_ << ", " << y_ << ")" << std::endl;
            }
            
            // Destructor
            ~Point() 
            {
                std::cout << "Destructor called for: (" << x_ << ", " << y_ << ")" << std::endl;
            }
            
            // Function to compute length from origin
            float length() const 
            {
                return std::sqrt(x_ * x_ + y_ * y_);
            }
            
            // Function to print x, y, and length
            void print() const 
            {
                std::cout << "Point: (" << x_ << ", " << y_ << ") Length: " << length() << std::endl;
            }
    };
}

namespace mySpace {
    const int ONE {1};
}
