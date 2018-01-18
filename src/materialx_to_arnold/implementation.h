#ifndef MTLX_TO_A_IMPLEMENTATION_H
#define MTLX_TO_A_IMPLEMENTATION_H

#include "arnold/facade.h"

//
// These functions:
//  - Facilitate the dependency injection (template method) of the Arnold and
//    MaterialX facade classes into the implementation
//  - Handle the Arnold User Data resource management
//  - Dispatch calls to the required functions in this library to perform the
//    MaterialX to Arnold translation during the procedural initialization
//
// Recall that Dependency Injection (Template Method) makes the code more
// friendly to unit testing. Google calls this hi-perf dependency injection. See
// the section  Mocking Nonvirtual Methods at:
// https://github.com/google/googletest/blob/master/googlemock/docs/CookBook.md
//
namespace MaterialXToArnold
{

void ParametersImpl(typename ArnoldFacade::AtListT* params,
                    typename ArnoldFacade::AtNodeEntryT* nentry);

int ProceduralInitImpl(const typename ArnoldFacade::AtNodeT* node,
                       void** user_ptr);

int ProceduralCleanupImpl(const typename ArnoldFacade::AtNodeT* node,
                          void* user_ptr);

int ProceduralNumNodesImpl(const typename ArnoldFacade::AtNodeT* node,
                           void* user_ptr);

AtNode* ProceduralGetNodeImpl(const typename ArnoldFacade::AtNodeT* node,
                              void* user_ptr, int i);

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_IMPLEMENTATION_H
