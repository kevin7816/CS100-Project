#ifndef __BALL_H__
#define __BALL_H__


#include "../sdl2lib/include/SDL2/SDL.h"
#include "Object.hpp"
#include "../definitions.hpp"

class Ball : public Object {
    private:
        double speed=BALL_SPEED;
        double velX=0;
        double velY=0;
        SDL_Rect rect;
        SDL_Color color;
    public:
        Ball() {
            rect.x=0;
            rect.y=0;
            rect.h=16;
            rect.w=16;
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;
        }
        Ball(double x, double y) {
            rect.x=x;
            rect.y=y;
            rect.h=16;
            rect.w=16;
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;
        }
        double getH(){
            return rect.h;
        }
        void setH(double h){
            rect.h=h;
        }
        double getX(){
            return rect.x;
        }
        void setX(double x){
            rect.x=x;
        }
        double getY(){
            return rect.y;
        }
        void setY(double y){
            rect.y=y;
        }
        double getW(){
            return rect.w;
        }
        void setW(double w){
            rect.w=w;
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
        void set_color(SDL_Color new_color) {
            color.r = new_color.r;
            color.g = new_color.g;
            color.b = new_color.b;
            color.a = new_color.a;
        }
        void show(SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
        SDL_Rect getRect(){
            return rect;
        }

};

#endif
