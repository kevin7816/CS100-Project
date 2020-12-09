#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include "../sdl2lib/include/SDL2/SDL.h"
#include "../sdl2lib/include/SDL2/SDL_ttf.h"
#include "Object.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <utility>

using namespace std;

class Text : public Object {
    // private members
    private:
        const char* words = "";
        double size = 100;
        const char* font = "compile/pixel.ttf"; // or compile/pixel.ttf if run directly from terminal
        SDL_Rect text_rect {0, 0, 100, 100}; // default pos == (0,0) and (w,h) == (100,100)
        SDL_Color color = {255, 255, 255, 255}; // default white
        TTF_Font* text_font = nullptr;
        SDL_Surface* text_surface = nullptr;
        SDL_Texture* text_texture = nullptr;
       

    public:
        // constructors
        Text(const char* words) : words(words) {};

        Text(const char* words, double size) : words(words), size(size) {};
            
        Text(const char* words, double size, SDL_Color color) : words(words), size(size), color(color) {};

        Text(int num) { // for score
            words = to_string(num).c_str();
        };

        Text(const char* words, double size, pair<int,int> pos) : words(words), size(size) { // for score
            // words = to_string(num).c_str();
            text_rect.x = pos.first;
            text_rect.y = pos.second;
        };

        // destructor
        ~Text() {
            SDL_DestroyTexture(text_texture);
            TTF_CloseFont(text_font);
            text_texture = nullptr;
            text_font = nullptr;
        }

        // public functions
        void create(SDL_Renderer* renderer) {
            // open font
            text_font = TTF_OpenFontIndex(font, size, 0); // change last argument if font has different font faces
            if (text_font == nullptr) { 
                throw "Could not open font";
                return;
            }

            // create rect that will contain text
            set_text_rect_wh(text_rect.w, text_rect.h);

            // create text_surface, and text_texture for surface
            text_surface = TTF_RenderText_Solid(text_font, words, color);
            if (text_surface == nullptr) {
                throw "Could not create text surface";
                return;
            }

            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (text_texture == nullptr) {
                throw "Could not create text texture from text surface";
                return;
            }

            SDL_FreeSurface(text_surface); // done creating texture from surface -> can free surface immediately
            text_surface = nullptr;

            return;
        }
        void show(SDL_Renderer* renderer) {
            // display text
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
            // SDL_RenderPresent(renderer);

            return;
        }

        // setters
        void set_text_color(int r, int g, int b) {
            if (r > -1 && g > -1 && b > -1 && r < 256 && g < 256 && b < 256) {
                color = {(uint8_t)r, (uint8_t)g, (uint8_t)b, 255}; // default opacity = 255 = full
            }    
            else 
                throw "Invalid rbg values";
            return;
        }
        void set_text_size(double size) {
            if (size > 0)
                this->size = size;
            else 
                throw "Invalid size";
            return;
        }
        void set_text_pos(int pos_x, int pos_y) { 
            if (pos_x > -1 && pos_y > -1) {
                text_rect.x = pos_x;
                text_rect.y = pos_y;
            }
            else
                throw "Invalid position";
            return;
        }

        // getters
        string get_words() { return string(words); }
        double get_size() { return size; }
        pair<int,int> get_pos() { return make_pair(text_rect.x, text_rect.y); }
        int get_color_r() { return color.r; }
        int get_color_b() { return color.b; }
        int get_color_g() { return color.g; }
        int get_color_a() { return color.a; }
    
    // private functions
    private:
        // set width, height and position of text_rect according to length and size of text and window
        void set_text_rect_wh(int &width, int &height) { // text_rect.w and text_rect.h
            int text_w = 0;
            int text_h = 0;

            if ((TTF_SizeText(text_font, words, &text_w, &text_h) != -1)) { // get and store the string's width and height to w and h
                // do nothing. just need text_w and text_h to be passed in values
            }
            else {
                cout << "Failed loading width and height of text";
                return;
            }
            // set width and height of text_rect based on size of text
            width = text_w;
            height = text_h;

            return;
        }
};

#endif //__TEXT_HPP__
