#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../sdl2lib/include/SDL2/SDL.h"
#include "Object.hpp"
#include "Controller.hpp"

class Player : public Object {
    private:
        SDL_Rect rect;
        Controller* controller;
        SDL_Color color;

        unsigned fitness;
        unsigned previousY;
    public:
        void get_input() {
            controller->move(this);
        }
        Player(Controller* controller, double x, double y, double h, double w) {
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = 255;
            this->controller = controller;
            rect.x=x;
            rect.y=y;
            rect.h=h;
            rect.w=w;

            fitness = 0;
            previousY = rect.y;
        }
        ~Player() {
            delete controller;
        }

        double get_previousY() {
            return previousY;
        }
        void set_previousY(double x) {
            previousY = x;
        }
        unsigned get_fitness() {
            return fitness;
        }
        void increment_fittness() {
            ++fitness;
        }

        Controller* getController() {
            return controller;
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
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
            SDL_RenderPresent(renderer);
        }
        void randomize_color() {
            color.r = fRand(0,255);
            color.g = fRand(0,255);
            color.b = fRand(0,255);
        }
        SDL_Color get_color() {
            return color;
        }
        SDL_Rect getRect(){
            return rect;
        }
    private:
        float fRand(float fMin, float fMax) {
            float f = (float)rand() / RAND_MAX;
            return fMin + f * (fMax - fMin);
        }

};

#endif
