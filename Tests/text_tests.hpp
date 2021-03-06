#ifndef __TEXTTESTS_H__
#define __TEXTTESTS_H__

#include "../Pong/Text.hpp"
#include "tests.hpp"

class TextTests : public Tests {
    private: 
        Text* message;
        string err_msg = "";
    public:
        virtual void run_tests() {
            // constructors test
            message = new Text("message");
            constructor_tests(1, message, message->get_words(), message->get_size(), message->get_pos(), message->get_color_r(), message->get_color_g(), message->get_color_b(), message->get_color_a());
            delete message;

            message = new Text("message", 50);
            constructor_tests(2, message, message->get_words(), message->get_size(), message->get_pos(), message->get_color_r(), message->get_color_g(), message->get_color_b(), message->get_color_a());
            delete message;

            message = new Text("message", 70, {76, 187, 223, 255});
            constructor_tests(3, message, message->get_words(), message->get_size(), message->get_pos(), message->get_color_r(), message->get_color_g(), message->get_color_b(), message->get_color_a());
            delete message;

            message = new Text(to_string(10).c_str());
            constructor_tests(4, message, message->get_words(), message->get_size(), message->get_pos(), message->get_color_r(), message->get_color_g(), message->get_color_b(), message->get_color_a());
            delete message;

            message = new Text(to_string(100).c_str(), 90, make_pair(0,0));
            constructor_tests(5, message, message->get_words(), message->get_size(), message->get_pos(), message->get_color_r(), message->get_color_g(), message->get_color_b(), message->get_color_a());
            delete message;


            // functions test
            message = new Text("message");
            function_tests(message);
            delete message;

            message = new Text("message", 50);
            function_tests(message);
            delete message;

            message = new Text("message", 70, {76, 187, 223, 255});
            function_tests(message);
            delete message;

            message = new Text(to_string(10).c_str());
            function_tests(message);
            delete message;

            message = new Text(to_string(100).c_str(), 90, make_pair(0,0));
            function_tests(message);
            delete message;

            std::cout << "-------------------\n";
            SetColor(2);
            std::cout << "Passed " << passed << " tests\n";
            SetColor(4);
            std::cout << "Failed " << failed << " tests\n";
            SetColor(7);
            std::cout << "-------------------\n";

            return;
        }

        void constructor_tests(int num, Text* message, string words, int size, pair<int,int> pos, int r, int g, int b, int a) {
            if (message->get_words() != words) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Text words\n"
                    << "       Expected: \"" << words << "\"\n"
                    << "       Actual: " << message->get_words() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Text words" << endl;
            }
            if (message->get_size() != size) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Text size\n"
                    << "       Expected: " << size << endl
                    << "       Actual: " << message->get_size() << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Text size" << endl;
            }
            if (message->get_pos() != pos) {
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Text pos\n"
                    << "       Expected: " << pos.first << ", " << pos.second << ")" << endl
                    << "       Actual: (" << message->get_pos().first << ", " << message->get_pos().second << ")" << endl;
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Text pos" << endl;
            }
            if (message->get_color_r() != r || message->get_color_g() != g || message->get_color_b() != b || message->get_color_a() != a) { 
                failed++;
                cout << "[FAILED] Constructor_" << num << "_Test: Text color\n"
                    << "       Expect: {" << r << ", " << g << ", " << b << ", " << a << "}\n"
                    << "       Actual: {" << message->get_color_r() << ", " << message->get_color_g() << ", " << message->get_color_b() << ", " << message->get_color_a() << "}\n";
            } else {
                passed++;
                cout << "[PASSED] Constructor_" << num << "_Test: Text color" << endl;
            }
            
            cout << endl;
            return;
        }

        void function_tests(Text* message) {
            // testing set_text_color()
            message->set_text_color(100, 150, 200);
            if (message->get_color_r() != 100 || message->get_color_g() != 150 || message->get_color_b() != 200 || message->get_color_a() != 255) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_Color: Failed changing text's color" << endl
                    << "       Expect: {100, 150, 200, 255} \n"
                    << "       Actual: {" << message->get_color_r() << ", " << message->get_color_g() << ", " << message->get_color_b() << ", " << message->get_color_a() << "}\n";
            } else {
                passed++;
                cout << "[PASSED] Set_Color: Text color is changed" << endl;
            }

            try {
                message->set_text_color(300, 150, 200); // out of range r value
            } catch (const char* msg) {
                err_msg = msg; 
            }
            if (err_msg != "Invalid rbg values") {
                failed++;
                cout << "[FAILED] Set_Color_Fail: Did not fail as expected" << endl
                     << "       Expect: Error message \"Invalid rbg values\"\n";
            } else {
                passed++;
                cout << "[PASSED] Set_Color_Fail: Failed as expected" << endl;
            }

            // testing set_text_size()
            message->set_text_size(78);
            if (message->get_size() != 78) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_Size: Failed changing text's size" << endl
                    << "       Expected: 78\n"
                    << "       Actual: " << message->get_size() << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_Size: Text size is changed" << endl;
            }

            try {
                message->set_text_size(-20); // negative size
            } catch (const char* msg) {
                err_msg = msg; 
            }
            if (err_msg != "Invalid size") {
                failed++;
                cout << "[FAILED] Set_Size_Fail: Did not fail as expected" << endl
                     << "       Expect: Error message \"Invalid size\"\n";
            } else {
                passed++;
                cout << "[PASSED] Set_Size_Fail: Failed as expected" << endl;
            }

            // tesing set_text_pos()
            message->set_text_pos(111, 222);
            if (message->get_pos() != make_pair(111, 222)) { // if color is not default white
                failed++;
                cout << "[FAILED] Set_Pos: Failed changing text's position" << endl
                    << "       Expected: (111, 222)\n"
                    << "       Actual: (" << message->get_pos().first << ", " << message->get_pos().second << ")" << endl;
            } else {
                passed++;
                cout << "[PASSED] Set_Pos: Text position is changed" << endl;
            }

            try {
                message->set_text_pos(-20, 10); // negative pos_x
            } catch (const char* msg) {
                err_msg = msg; 
            }
            if (err_msg != "Invalid position") {
                failed++;
                cout << "[FAILED] Set_Pos_Fail: Did not fail as expected" << endl
                     << "       Expect: Error message \"Invalid position\"\n";
            } else {
                passed++;
                cout << "[PASSED] Set_Pos_Fail: Failed as expected" << endl;
            }

            cout << endl;
            return;
        }

        
};

#endif
//g++ text_tests.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o text_test