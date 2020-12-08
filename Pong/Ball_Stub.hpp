#ifndef __BALL_STUB_H__
#define __BALL_STUB_H__


#include "Object_Stub.hpp"
#include <vector>
#include<iostream>

class Ball : public Object {
    private:
        double speed=16.0;
        double velX=0;
        double velY=0;
        std::vector<double> rect;
    public:
        Ball() {
            rect.push_back(0);   //x = at 0
            rect.push_back(0);   //y = at 1
            rect.push_back(16);  //h = at 2
            rect.push_back(16);  //w = at 3
        }
        Ball(double x, double y) {
            rect.push_back(x);
            rect.push_back(y);
            rect.push_back(16);
            rect.push_back(16);
        }
        double getH(){
            return rect.at(3);
        } 
        void setH(double h){
            rect.at(3)=h;
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
        void setSpeed(double speed){
            this->speed=speed;
        }
        double getSpeed(){
            return speed;
        }
        void setVelX(double x){
            velX=x;
        }
        double getVelX(){
            return velX;
        }
        void setVelY(double y){
            velY=y;
        }
        double getVelY(){
            return velY;
        }
        void show(double renderer){
            std::cout << "Rendered Object" << std::endl;
        }
        std::vector<double> getRect(){
            return rect;
        }

};

#endif