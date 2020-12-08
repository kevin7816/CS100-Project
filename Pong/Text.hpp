#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include "sdl2lib/include/SDL2/SDL.h"
#include "sdl2lib/include/SDL2/SDL_ttf.h"
#include "Object.hpp"
#include "../definitions.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <utility>

using namespace std;

class Text : public Object {
    friend class GameRenderer; // so that GameRenderer can check which score to render

    // private members
    private:
        const char* words = "";
        pair<int, const char*> score = make_pair(-1, words); // -1 == not a score; 0 == score_left; 1 == score_right
        double size = 100;
        TTF_Font* text_font = nullptr;
        SDL_Surface* text_surface = nullptr;
        SDL_Texture* text_texture = nullptr;
        SDL_Color color = {255, 255, 255, 255}; // default white
        SDL_Rect text_rect;  

    public:
        // constructors
        Text(const char* words) : words(words) {};

        Text(const char* words, double size) : words(words), size(size) {};
            
        Text(const char* words, double size, SDL_Color color) : words(words), size(size), color(color) {};

        Text(int num, double size, pair<int,int> pos, int s) : size(size) { // for score
            words = to_string(num).c_str();
            text_rect.x = pos.first;
            text_rect.y = pos.second;
            score.first = s;
            score.second = words;
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
            text_font = TTF_OpenFontIndex(FONT, size, 0); // change last argument if font has different font faces
            if (text_font == nullptr) { 
                fprintf(stderr, "Could not open font\n", SDL_GetError());
                return;
            }

            // create rect that will contain text
            set_text_rect_wh(text_rect.w, text_rect.h);

            // create text_surface, and text_texture for surface
            text_surface = TTF_RenderText_Solid(text_font, words, color);
            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
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
        void set_text_color(unsigned char r, unsigned char b, unsigned char g) {
            color = {r, b, g, 255}; // default opacity = 255 = full
            return;
        }
        void set_text_size(double size) {
            this->size = size;
            return;
        }
        void set_text_pos(int pos_x, int pos_y) { 
            text_rect.x = pos_x;
            text_rect.y = pos_y;
            return;
        }
        int get_text_pos_x() { 
            return text_rect.x;
        }
    
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
                cout << "Failed loading width and height of text." << endl;
            }
            // set width and height of text_rect based on size of text
            width = text_w; 
            height = text_h; 

            return;
        }
};

#endif //__TEXT_HPP__