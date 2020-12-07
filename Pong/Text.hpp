#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include "sdl2lib/include/SDL2/SDL.h"
#include "sdl2lib/include/SDL2/SDL_ttf.h"
#include "Object.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <utility>

// #include <type_traits>
// #include <typeinfo>
// #ifndef _MSC_VER
// #   include <cxxabi.h>
// #endif
// #include <memory>
// #include <string>
// #include <cstdlib>

using namespace std;

// template <class T> std::string type_name() {
//     typedef typename std::remove_reference<T>::type TR;
//     std::unique_ptr<char, void(*)(void*)> own (
//         #ifndef _MSC_VER
//             abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
//         #else
//             nullptr,
//         #endif
//             std::free
//     );
//     std::string r = own != nullptr ? own.get() : typeid(TR).name();
//     if (std::is_const<TR>::value)
//         r += " const";
//     if (std::is_volatile<TR>::value)
//         r += " volatile";
//     if (std::is_lvalue_reference<T>::value)
//         r += "&";
//     else if (std::is_rvalue_reference<T>::value)
//         r += "&&";
//     return r;
// }

class Text : public Object {
    // private members
    public:
        const char* words = "";
        pair<int, const char*> score = make_pair(-1, words); // -1 == not a score; 0 == score_left; 1 == score_right
        const char* font = "pixel.ttf";
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
            
        Text(const char* words, const char* font, double size, SDL_Color color) : words(words), font(font), size(size), color(color) {};

        Text(const char* words, double size, pair<int,int> pos, int s) : words(words), size(size) {
            text_rect.x = pos.first;
            text_rect.y = pos.second;
            score.first = s;
            score.second = words;
        };

        // Text(int num, int s) {
        //     cout << "hi" << endl;
        //     words = to_string(num).c_str();
        //     score.first = s;
        //     score.second = words;
        //     cout << "score.first: " << score.first << endl;
        //     cout << "score.first: " << score.second << endl;
        // };
        
        // destructor
        ~Text() {
            SDL_DestroyTexture(text_texture);
            SDL_FreeSurface(text_surface);
            TTF_CloseFont(text_font);
        }
        
        // public functions
        void show(SDL_Renderer* renderer) {
            text_font = TTF_OpenFontIndex(font, size, 0); // change last argument if font has different font faces
            if (text_font == nullptr) { 
                TTF_SetError("Loading failed :( (code: %d)", 142);
                cout << "Error: " << TTF_GetError() << endl;
                return;
            }

            // create rect that will contain text
            set_text_rect_wh(text_rect.w, text_rect.h);
            // words = to_string(23).c_str();
            // std::cout << "decltype(words) in Text show() is " << type_name<decltype(words)>() << '\n';
            // cout << words << endl << endl;

            // create text_surface, and text_texture for surface
            text_surface = TTF_RenderText_Solid(text_font, words, color);
            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

            // display text
            SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
            // SDL_RenderPresent(renderer);

            return;
        }
        void set_words(const char* new_words) {
            words = new_words;
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
        void set_text_pos_x(int pos_x) { 
            text_rect.x = pos_x;
            return;
        }
        void set_text_pos_y(int pos_y) { 
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