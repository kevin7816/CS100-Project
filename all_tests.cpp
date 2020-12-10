#include "Tests/tests.hpp"
#include "Tests/play_tests.hpp"
#include "Tests/train_tests.hpp"
#include "Tests/text_tests.hpp"
#include "Tests/game_renderer_tests.hpp"
#include "Tests/ai_tests.hpp"
#include "Tests/matrix_tests.hpp"
#include "Tests/sensor_test.hpp"


int main(int argc, char * argv[]) {
    Tests* test;
    int tot_passed = 0;
    int tot_failed = 0;

    cout << "Performing Play Class Tests . . ." << endl << endl;
    test = new PlayTests();
    test->run_tests();
    tot_passed += test->passed;
    tot_failed += test->failed;
    delete test;
    cout << endl << "======================================================================================" << endl << endl;

    cout << "Performing Train Class Tests . . ." << endl << endl;
    test = new TrainTests();
    test->run_tests();
    tot_passed += test->passed;
    tot_failed += test->failed;
    delete test;
    cout << endl << "======================================================================================" << endl << endl;

    cout << "Performing Text Class Tests . . ." << endl << endl;
    test = new TextTests();
    test->run_tests();
    tot_passed += test->passed;
    tot_failed += test->failed;
    delete test;
    cout << endl << "======================================================================================" << endl << endl;

    cout << "Performing GameRenderer Class Tests . . ." << endl << endl;
    test = new GRTests();
    test->run_tests();
    tot_passed += test->passed;
    tot_failed += test->failed;
    delete test;
    cout << endl << "======================================================================================" << endl << endl;

    cout << "Performing AI Class Tests . . ." << endl << endl;
    test = new AITests();
    test->run_tests();
    tot_passed += test->passed;
    tot_failed += test->failed;
    delete test;
    cout << endl << "======================================================================================" << endl << endl;

    cout << "Performing Matrix Class Tests . . ." << endl << endl;
    test = new MatrixTests();
    test->run_tests();
    tot_passed += test->passed;
    tot_failed += test->failed;
    delete test;
    cout << endl << "======================================================================================" << endl << endl;

    // cout << "Performing Sensor Class Tests . . ." << endl << endl;
    // test = new SensorTests();
    // test->run_tests();
    // tot_passed += test->passed;
    // tot_failed += test->failed;
    // delete test;
    // cout << endl << "======================================================================================" << endl << endl;

    cout << "Total passed: " << tot_passed << endl;
    cout << "Total failed: " << tot_failed << endl;

    return 0;
}

//g++ all_tests.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/test