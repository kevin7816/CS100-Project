#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include "sdl2lib/include/SDL2/SDL.h"
#include "sdl2lib/include/SDL2/SDL_ttf.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Text {
    // private members
    private:
        const char* words;
        const char* font = "arial.ttf";
        double size = 100;
        int text_rect_pos = 5; // default pos of rect is middle
        TTF_Font* text_font;
        SDL_Renderer* renderer;
        SDL_Surface* text_surface;
        SDL_Texture* text_texture;
        SDL_Color color = {255, 255, 255, 255}; // default white
        SDL_Rect text_rect;  

    public:
        // constructors
        Text(SDL_Renderer* renderer, const char* words) 
            : renderer(renderer), words(words) {};
        Text(SDL_Renderer* renderer, const char* words, const char* font) 
            : renderer(renderer), words(words), font(font) {};
        Text(SDL_Renderer* renderer, const char* words, const char* font, double size, SDL_Color color) 
            : renderer(renderer), words(words), font(font), size(size), color(color) {};
        
        // destructor
        ~Text() {
            SDL_FreeSurface(text_surface);
            TTF_CloseFont(text_font);
            TTF_Quit();
        }
        
        // public functions
        void render_text() {
            // initialize ttf
            TTF_Init();
            if (TTF_Init() < 0) {
                fprintf(stderr, "Could not init TTF\n", SDL_GetError());
                return;
            }

            // get font
            text_font = TTF_OpenFontIndex(font, size, 0); // change last argument if font has different font faces
            if (text_font == nullptr) { 
                TTF_SetError("Loading failed :( (code: %d)", 142);
                cout << "Error: " << TTF_GetError() << endl;
                return;
            }
            
            // create text_surface, and text_texture for surface
            text_surface = TTF_RenderText_Blended(text_font, words, color);
            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
             
            // create rect that will contain text
            // set width, height and position of text_rect according to length and size of text and window
            set_text_rect_wh(text_rect.w, text_rect.h);

            // set text_rect position
            if (text_rect_pos == -1) // if user doesn't choose default pos or choose pos manually, display text middle of screen
                default_rect_pos(text_rect.x, text_rect.y, 5); 
            else if (text_rect_pos != 0) // if user doesn't set position manually
                default_rect_pos(text_rect.x, text_rect.y, text_rect_pos);
            // if user sets position manually, don't call default_rect_pos()

            // display text
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
            SDL_RenderPresent(renderer);

            return;
        }
        void set_text_color(int r, int b, int g) {
            color = {r, b, g, 255}; // default opacity = 255 = full
            return;
        }
        void set_text_size(double size) {
            this->size = size;
            return;
        }
        //use default positions
        void set_text_pos(int pos) {
            text_rect_pos = pos;
            return;
        }
        // set positions manually
        void set_text_pos(int pos_x, int pos_y) { 
            text_rect_pos == 0;
            text_rect.x = pos_x;
            text_rect.y = pos_y;
            return;
        }
        

    // private functions
    private:
        // set position of text_rect in the middle of screen
        void default_rect_pos(int &rect_x, int &rect_y, int pos) {
            int window_w = 0;
            int window_h = 0; 
            int rect_w = text_rect.w; 
            int rect_h = text_rect.h;

            int text_w = 0;
            int text_h = 0;
            if ((TTF_SizeText(text_font, words, &text_w, &text_h) != -1)) { // get and store the string's width and height to w and h
                // do nothing. just need text_w and text_h to be passed in values            
            } 
            else {
                cout << "Failed loading width and height of text." << endl;
            }

            if ((SDL_GetRendererOutputSize(renderer, &window_w, &window_h)) != -1) { // get and store the string's width and height to w and h
                if (pos = 5) {
                    rect_x = window_w/2 - rect_w/2; 
                    rect_y = window_h/2 - rect_h/2;
                }
            } 
            else {
                cout << "Failed setting position of text_rect." << endl;
            }
        }
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