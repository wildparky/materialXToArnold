#include "implementation.h"

#include <stdexcept>
#include <vector>
#include <iostream>

#include "macros.h"
#include "constants.h"
#include "configuration.h"
#include "arnold/procedural.h"
#include "arnold/facade.h"
#include "arnold/utility.h"
#include "materialx/facade.h"
#include "translation/interface.h"

namespace MaterialXToArnold
{

using AF = ArnoldFacade;
using MF = MaterialXFacade;

void ParametersImpl(typename AF::AtListT* params,
                    typename AF::AtNodeEntryT* nentry)
{
    const AF af {};  // Arnold Facade Free Functions Type
    InstallAllProceduralNodeParametersAndMetaData(af, params, nentry);
}

int ProceduralInitImpl(const typename AF::AtNodeT* node,
                       void** user_ptr)
{
    // Translate the MaterialX Docuement, catching exceptions and returning true
    // when no exception is thrown and false otherwise.
    const AF af{};
    const MF mf{};
    try
    {
        // Create a procedural node configuration based on user input from the
        // procedural node parameters
        Configuration config = ReadAllProceduralNodeParameters(af, node);

        using UserData = typename AF::UserDataT;
        UserData* user_data = new UserData();
        *user_ptr = static_cast<void*>(user_data);
        config.user_data_ptr_ = *user_ptr;

        // Translate the MaterialX document to Arnold based on the configuration
        Translate<AF, MF>(af, mf, config, NodeDeleter);
    }
    catch(std::exception& e)
    {
        MSG_ERROR(af, "Translation from MaterialX to Arnold unsuccessful "
                  "-- %s.",  e.what());
        return kFalse;
    }
    return kTrue;
}

int ProceduralCleanupImpl(const typename AF::AtNodeT*,
                          void* user_ptr)
{
    const AF af{};
    try
    {
        using UserData = typename AF::UserDataT;
        UserData* user_data = static_cast<UserData*>(user_ptr);
        delete user_data;
    }
    catch(std::exception& e)
    {
        MSG_ERROR(af, "Translation from MaterialX to Arnold unsuccessful "
                  "-- %s.",  e.what());
        return kFalse;
    }
    return kTrue;
}

int ProceduralNumNodesImpl(const typename AF::AtNodeT*,
                           void* user_ptr)
{
    std::vector<typename AF::AtNodeT*>* user_data =
            static_cast<std::vector<typename AF::AtNodeT*>*>(user_ptr);

    // Narrowing conversion from size_t to int should be ok here as Arnold
    // should not allow more than max int nodes to be created
    return static_cast<int>(user_data->size());
}

AtNode* ProceduralGetNodeImpl(const typename AF::AtNodeT*,
                              void* user_ptr, int i)
{
    std::vector<typename AF::AtNodeT*>* user_data =
            static_cast<std::vector<typename AF::AtNodeT*>*>(user_ptr);

    return (*user_data)[static_cast<size_t>(i)];

}

} // namespce MaterialXToArnold
