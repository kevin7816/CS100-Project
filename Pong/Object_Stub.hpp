#ifndef __OBJECT_STUB_H__
#define __OBJECT_STUB_H__

#include <vector>

class Object {
    private:
        double x;
        double y;
    public:
        Object() {
            // x=0.0;
            // y=0.0;
        }
        // Object(double x, double y){
        //     this->x=x;
        //     this->y=y;
        // }
        virtual void show(double renderer) = 0;
};

#endif