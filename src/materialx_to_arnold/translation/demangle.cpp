#include "translation/demangle.h"

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

namespace MaterialXToArnold
{

std::string Demangle(const char* name)
{
    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

} // namespce MaterialXToArnold

#else

namespace MaterialXToArnold
{

}
// does nothing if not g++
std::string Demangle(const char* name)
{
    return name;
}

} // namespce MaterialXToArnold

#endif
