#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "sdl2lib/include/SDL2/SDL.h"
#include "Object.hpp"
#include "Controller.hpp"

class Player : public Object {
    private:
        SDL_Rect rect;
        Controller* controller;
    public:
        void get_input() {
            controller->move(this);
        }
        Player(Controller* controller, double x, double y, double h, double w) {
            this->controller = controller;
            rect.x=x;
            rect.y=y;
            rect.h=h;
            rect.w=w;
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
        void show(SDL_Renderer* renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
        SDL_Rect getRect(){
            return rect;
        }

};

#endif
