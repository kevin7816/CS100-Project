#include <iostream>
#include "../Pong/GameRenderer.hpp"
#include "../Pong/Ball.hpp"

class GRTests {
    private: 
        GameRenderer gr;
        std::string err_msg = "";
    public:
        int failed = 0;
        int passed = 0;

        void add_test(std::vector<Object*> objects, std::string name) { 
            int orig_size = gr.gameObjects.size();

            for (auto i : objects) {
                gr.add(i);
            }

            if (gr.gameObjects.size() != (objects.size() + orig_size)) {
                std::cout << gr.gameObjects.size() << " " << objects.size() + orig_size << std::endl;
                failed++;
                std::cout << "[FAILED] " << name << ": Failed to add all game objects to GameRenderer's vector\n";
            } else {
                passed++;
                std::cout << "[PASSED] " << name << ": All game objects are successfully added to GameRenderer's vector" << std::endl;
            }

            std::cout << std::endl;
            return;
        }

        void add_test(Object* object, std::string name) { 
            bool is_added = 0;
            int orig_size = gr.gameObjects.size();

            gr.add(object);

            for (unsigned i = 0; i < gr.gameObjects.size(); i++) {
               if (gr.gameObjects.at(i) == object) {
                   is_added = 1; // object is added
                   break;
               }
            }

            if ((gr.gameObjects.size() != (orig_size + 1)) && is_added == 0) {
                failed++;
                std::cout << "[FAILED] " << name << ": Failed to add an object from GameRenderer's vector\n"
                          << "       Object is not found inside vector\n"
                          << "       Vector's size is not increased by 1\n";
            } else {
                passed++;
                std::cout << "[PASSED] " << name << ": Object is successfully added to GameRenderer's vector" << std::endl;
            }

            std::cout << std::endl;
            return;  
        }

        void add_test_fail(Object* object, std::string name) {
            try {
                gr.add(object);
            }
            catch (const char* msg) {
                err_msg = msg;
            }

            if (err_msg != "Object is already in vector") {
                failed++;
                std::cout << "[FAILED] " << name << ": Did not fail as expected" << std::endl
                            << "       Expect: Error message \"Object is already in vector\"\n"
                            << "       Actual: " << err_msg << std::endl;
            } else {
                passed++;
                std::cout << "[PASSED] " << name << ": Failed as expected" << std::endl;
            }

            std::cout << std::endl;
            return;
        }

        void remove_test(Object* object, std::string name) {
            bool is_removed = 1;
            int orig_size = gr.gameObjects.size();

            gr.remove(object);

            for (unsigned i = 0; i < gr.gameObjects.size(); i++) {
               if (gr.gameObjects.at(i) == object) {
                   is_removed = 0; // object is NOT removed
                   break;
               }
            }

            if ((gr.gameObjects.size() != (orig_size - 1)) && is_removed == 0) {
                failed++;
                std::cout << "[FAILED] " << name << ": Failed to remove an object from GameRenderer's vector\n"
                          << "       Object is still found inside vector\n"
                          << "       Vector's size is not decreased by 1\n";
            } else {
                passed++;
                std::cout << "[PASSED] " << name << ": Object is successfully removed to GameRenderer's vector" << std::endl;
            }

            std::cout << std::endl;
            return;           
        }

        void remove_test_fail(Object* object, std::string name) {
            try {
                gr.remove(object);
            }
            catch (const char* msg) {
                err_msg = msg;
            }

            if (err_msg != "Object is not in vector") {
                failed++;
                std::cout << "[FAILED] " << name << ": Did not fail as expected" << std::endl
                            << "       Expect: Error message \"Object is not in vector\"\n";
            } else {
                passed++;
                std::cout << "[PASSED] " << name << ": Failed as expected" << std::endl;
            }

            std::cout << std::endl;
            return;
        }

};

int main(int argc, char * argv[]) {
    GRTests test;
    Object* o1 = new Ball();
    Object* o2 = new Ball();
    Object* o3 = new Ball();

    std::vector<Object*> objects;
    objects.push_back(o2);
    objects.push_back(o3);

    test.add_test(o1, "Add_Basic"); // add o1
    test.add_test(objects, "Add_Multiple"); // add o2, o3
    test.add_test_fail(o1, "Add_Duplicate"); // add o1 again
    test.add_test_fail(o2, "Add_Duplicate"); // add o1 again
    test.add_test_fail(o3, "Add_Duplicate"); // add o1 again
    test.remove_test(o3, "Remove_Basic"); // remove o3
    test.remove_test_fail(o3, "Remove_Duplicate"); // remove o3 again
    test.remove_test(o1, "Remove_Basic"); // remove o1
    test.remove_test(o2, "Remove_Basic"); // remove o2
    test.remove_test_fail(o1, "Remove_Duplicate"); // remove o1 again
    test.remove_test_fail(o2, "Remove_Duplicate"); // remove o2 again

    std::cout << "-------------------\n"
              << "Passed " << test.passed << " tests\n"
              << "Failed " << test.failed << " tests\n"
              << "-------------------\n";

    delete o1;
    delete o2;
    delete o3;

    return 0;
}


//g++ game_renderer_tests.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o gr_test