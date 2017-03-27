//
// Created by valeriy on 26.03.17.
//

#ifndef CPPEXCEPTIONS_MYEXCEPTION_H
#define CPPEXCEPTIONS_MYEXCEPTION_H

#include <string>
#include <iostream>
#include <cassert>
#include <memory>
#include <setjmp.h>

class MyException {
public:
    MyException( std::string message ) {
        this->message = message;
    }

    virtual ~MyException( ) {

    }

    std::string getMessage( ) {
        return this->message;
    }

private:
    std::string message;
};

class __ExceptionInfo {
public:
    jmp_buf buf;

    __ExceptionInfo *lastInfo;

    std::shared_ptr<MyException> exception;

    __ExceptionInfo( ) { }

    ~__ExceptionInfo( ) { }
};

extern __ExceptionInfo *__exception_info;
extern __ExceptionInfo *__tmp;
extern bool __catched;
extern int __jmp_value;

#define TRY \
__catched = false;\
__tmp = new __ExceptionInfo();\
__tmp->lastInfo = __exception_info; \
__exception_info = __tmp;\
__jmp_value = setjmp( __exception_info->buf );\
if ( !__jmp_value ) {

#define CATCH( TYPE, __name ) \
} \
if ( __jmp_value && __exception_info && std::dynamic_pointer_cast<TYPE>( __exception_info->exception )) {\
__catched = true;\
std::shared_ptr<TYPE> __name = std::dynamic_pointer_cast<TYPE>( __exception_info->exception ); \
__exception_info = __exception_info->lastInfo;

#define THROW( __exception ) \
if (!__exception_info) {\
assert(0);}\
__exception_info->exception = std::shared_ptr<MyException>( __exception ); \
longjmp( __exception_info->buf, 1 );


#define ETRY \
} \
if ( !__catched ) {\
THROW( __exception_info->exception ) }


#endif //CPPEXCEPTIONS_MYEXCEPTION_H
