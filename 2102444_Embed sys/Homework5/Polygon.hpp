#pragma once

#include "Point.h"
#include <vector> 

namespace mySpace 
{
    using std::vector;
    using std::cout;
    using Points = vector<Point>;
    
    // Polygon with a vector of N_ Points
    class Polygon 
    {
        private:
            Points P_;    // Main Attribute
            int N_;       // Auxillary Attribute
        public:
            // default constructor
            Polygon () {N_=0;}

            // constructor with a vector of N points
            Polygon (Points P) : P_(P) {N_=P.size();}
            
            // length from P_[i] to P_[i+1]
            float length(int i=0) 
            {
                // check if valid value of i and N
                if ((i>=0) && (i < N_) && (N_>1)) 
                {
                    return P_[i].length(nextPoint(i));
                }
                    
                else // otherwise return 0
                    return 0;
            }
            
            // print info of Polygon
            void print() 
            {
                cout << "A Polygon with " << N_ << " points.\n"; 
                
                // traditional for loop
                // int i and j is only local to the for loop
                for (int i=0; i<N_ ; i++) 
                {
                    cout << "P" <<i << " is @"; P_[i].print(); cout<<".\n";
                }
                
                // another int i but available outside while loop (inside print)
                int i=0;
                
                // while loop
                while (i<N_) 
                {
                    // j is local to the while loop
                    cout << "Line P"<<i << "-P" << nextIndex(i)<<" is "<< length(i) << " unit long.\n";
                    i++;
                }
                cout << "Hence its perimeter = " << perimeter() << " unit long.\n";
                cout << "Its area is " << area() << " unit2.\n";
                cout << "\n";
            }

            float perimeter() 
            {
                float sum = 0;
                for (int i=0; i<N_; i++)
                    sum += length(i);
                return sum;
            }

            float area() 
            { 
                float Area {0}; 
                float up = 0, down = 0;
                
                for(int i=0; i<N_ ;i++)
                {
                    int j = (i + 1) % N_;
                    
                    up   += P_[i].X() * P_[j].Y();
                    down += P_[i].Y() * P_[j].X();
                }
                Area = std::abs(up-down) * 0.5;
                return Area;
            }

            void moveX(float X) 
            {
                moveXY(X);            
            }
            
            void moveY(float Y) 
            {
                for (int i=0; i<N_ ; i++) 
                    P_[i].moveRelative(0,Y);
            }
            
            void moveXY(float X, float Y=0) 
            {
                for (int i=0; i<N_ ; i++) 
                     P_[i].moveRelative(X,Y);
            }
            
            
            void scale(float factor) 
            {   
                float x1, y1, xc, yc;
                x1 = -P_[0].X();
                y1 = -P_[0].Y();
                
                moveXY(x1,y1);
                
                Points &H = P_;
                for (int i=0; i<N_ ; i++) 
                {
                     xc = P_[0].X() * factor;
                     yc = P_[0].Y() * factor;
                     H.erase(H.begin());
                     H.push_back(Point(xc, yc));
                }
                moveXY(-x1,-y1);
            }

            Point nextPoint(int i) 
            {
                return P_[ nextIndex(i) ];
                
            }

            // next Index is i+1 if i+1 is not N_ otherwise zero.
            int nextIndex(int i) 
            {
                return (i+1) % N_;
            }
    };
}
