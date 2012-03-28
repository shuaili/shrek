#ifndef SHREK_COMMON_H_
#define SHREK_COMMON_H_

#include <cassert>
#include <iostream>
#include <string>
#include <stdint.h>
#include <tr1/memory>
#include <tr1/functional>

#define SHREK_BEGIN_NAMESPACE(x) namespace shrek { namespace x{ 

#define SHREK_END_NAMESPACE(x) } }

#define SHREK_USE_ROOT_NAMESPACE using namespace shrek;

#define SHREK_USE_NAMESPACE(x) using namespace shrek::x

#define SHREK_NS(x) shrek::x

#define SHREK_ALIAS_NAMESAPCE(x, y) namespace shrek { namespace x = y; }

#define SHREK_TYPEDEF_PTR(x) typedef std::tr1::shared_ptr<x> x##Ptr

/* define for close assign operator and copy constructor;should not be called if not implemented */
#define COPY_CONSTRUCTOR(T) \
    T(const T &); \
    T & operator=(const T &)

#define DISALLOW_COPY_AND_ASSIGN(T)             \
    COPY_CONSTRUCTOR(T)

#define DELETE(x) do {             \
    if(x){                                  \
    delete x;                           \
    x = NULL;                           \
    }                                       \
    }while(0)

#define DELETE_ARRAY(x) do {             \
    if(x){                                  \
    delete [] x;                           \
    x = NULL;                           \
    }                                       \
    }while(0)

#endif /*SHREK_COMMON_H_*/
