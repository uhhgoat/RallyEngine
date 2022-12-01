#include "M_Assert.h"
void __M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg)
{
    if (!expr)
    {

        DebugMsg::out("\n\tAssert failed:\t%s \n\tExpected:\t\t%s \n\tSource:\t\t\t%s, line %d\n\n", msg, expr_str, file, line);

        assert(!"CHECK CONSOLE FOR ERROR");
    }
}