//
//  macros.h
//  pxlframework
//
//  Created by Axel Guilmin on 27/08/13.
//
//


#ifndef __pxlframework__macros__
#define __pxlframework__macros__


// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
// Then, in class Foo:
//
//class Foo
//{
//public:
//    Foo(int f);
//    ~Foo();
//
//private:
//    DISALLOW_COPY_AND_ASSIGN(Foo);
//};


#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
TypeName(const TypeName&);               \
void operator=(const TypeName&)


#define RAD_TO_DEG 57.2957795131   // 1 rad = 57.2957795131 deg
#define DEG_TO_RAD 0.0174532925199 // 1 deg = 0.0174532925199 rad


#endif




