#include <iostream>
#include "MyException.h"

class MyException1 : public MyException {
public:
    MyException1( const std::string &message ) : MyException( message ) { }

    ~MyException1( ) { }

};

class MyException2 : public MyException {
public:
    MyException2( const std::string &message ) : MyException( message ) { }

    ~MyException2( ) { }

};

__ExceptionInfo *__exception_info = 0;
__ExceptionInfo *__tmp;
bool __catched;
int __jmp_value;

int main( int argc, char **argv ) {
    TRY
        TRY
            THROW( new MyException1( "lalala" ))
        CATCH(MyException2, ex)
            std::cout << ex->getMessage() << "\n";
            THROW( new MyException2(ex->getMessage() + "1"))
        CATCH(MyException1, ex)
            std::cout << ex->getMessage() << "\n";
            THROW( new MyException1(ex->getMessage() + "1"))
        ETRY
    CATCH( MyException1, ex )
        std::cout << ex->getMessage() << "\n";
//        THROW(new MyException1("fdfdf"))
    CATCH( MyException2, ex )
        std::cout << ex->getMessage() << "\n";
    ETRY

    return 0;
}