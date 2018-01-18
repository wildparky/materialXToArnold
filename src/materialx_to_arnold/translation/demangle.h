#ifndef MTLX_TO_A_TRANSLATION_DEMANGLE_H
#define MTLX_TO_A_TRANSLATION_DEMANGLE_H

// https://stackoverflow.com/questions/281818

#include <string>
#include <typeinfo>

namespace MaterialXToArnold
{

std::string Demangle(const char* name);

template <class T>
std::string DemangleType(const T& t)
{
    return Demangle(typeid(t).name());
}

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_TRANSLATION_DEMANGLE_H
