#ifndef __PLAYER_STUB_H__
#define __PLAYER_STUB_H__

#include "Object_Stub.hpp"
#include <vector>
#include <iostream>

class Player : public Object {
    private: 
        std::vector<double> rect;
    public: 
        Player(double x, double y, double h, double w) {
            rect.push_back(x);  //x = at 0
            rect.push_back(y);  //y = at 1
            rect.push_back(h);  //h = at 2
            rect.push_back(w);  //w = at 3
        }
        double getH(){
            return rect.at(2);
        } 
        void setH(double h){
            rect.at(2)=h;
        }
        double getX(){
            return rect.at(0);
        } 
        void setX(double x){
            rect.at(0)=x;
        }
        double getY(){
            return rect.at(1);
        } 
        void setY(double y){
            rect.at(1)=y;
        }
        double getW(){
            return rect.at(3);
        } 
        void setW(double w){
            rect.at(3)=w;
        }
        void show(double renderer){
            std::cout << "Rendered Object" << std::endl;
        }
        std::vector<double> getRect(){
            return rect;
        }
        
};

#endif