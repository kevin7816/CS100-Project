#ifndef __TESTS_H__
#define __TESTS_H__

class Tests {
    public:
        Tests() {}
        // virtual ~Tests() = 0;
        virtual void run_tests() = 0;
        int passed = 0;
        int failed = 0;
};
// Tests::~Tests() {}

#endif
