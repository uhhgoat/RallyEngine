//Referenced from StackOVerflow user: Eugene Magdalits
//https://stackoverflow.com/questions/3692954/add-custom-messages-in-assert
#ifndef M_ASSERT_H
#define M_ASSERT_H

#include <iostream>
#include <DebugOut.h>

#ifndef NDEBUG
#   define M_Assert(Expr, Msg) \
    __M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_Assert(Expr, Msg) ;
#endif

void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg);
#endif