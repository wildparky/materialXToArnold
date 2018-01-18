#ifndef MTLX_TO_A_ARNOLD_FACADE_H
#define MTLX_TO_A_ARNOLD_FACADE_H

#ifndef PROCEDURAL_NAME
#error "Must provide -DPROCEDURAL_NAME value while compiling this file."
#endif

#include <memory>
#include <stdio.h>
#include <string.h>
#include <functional>
#include <cstring>
#include <utility>
#include <string>
#include <vector>

#include <ai.h>

namespace MaterialXToArnold
{

//
// A facade/adapter interface to the Arnold library to provide a simplifier
// interface to the Arnold library and to facilitate mocking it during testing.
// It's possible to use Google Mock to mock a free function (i.e. a C-style
// function or a static method). You just need to rewrite your code to use an
// interface see the Mocking Free Functions at:
// https://github.com/google/googletest/blob/master/googlemock/docs/CookBook.md
//
class ArnoldFacade
{

public:

    // -----------------------------------------------------------
    // Arnold Types
    // -----------------------------------------------------------

    using AtRGBT = AtRGB;
    using AtRGBAT = AtRGBA;
    using AtVectorT = AtVector;
    using AtVector2T = AtVector2;
    using AtStringT = AtString;
    using AtArrayT = AtArray;
    using AtMatrixT = AtMatrix;
    using AtEnumT = AtEnum;
    using AtListT = AtList;

    using AtNodeT = AtNode;
    using AtNodeEntryT = AtNodeEntry;
    using AtParamEntryT = AtParamEntry;

    // Some custom types to use with the Arnold interface
    using UserDataT = std::vector<AtNodeT*>;

    using AtNodeTDeleterFncPtrT = bool(*)(ArnoldFacade::AtNodeT*,
                                          const ArnoldFacade& af);

    using AtNodeTDeleterBindT =
        std::_Bind<bool (*(std::_Placeholder<1>,
                           ArnoldFacade))(AtNode*, ArnoldFacade const&)>;

    using AtNodeTUniquePtrT =
        std::unique_ptr<ArnoldFacade::AtNodeT,
                        ArnoldFacade::AtNodeTDeleterBindT>;

    // -----------------------------------------------------------
    // AiUniverse API (ai_universe.h)
    // -----------------------------------------------------------
    AtNodeT* AiUniverseGetOptions() const;

    // -----------------------------------------------------------
    // AtParamEntry API (ai_params.h)
    // -----------------------------------------------------------

    void  AiNodeParamByte   (AtListT* params, int varoffset, const char* pname,
                          uint8_t pdefault) const;
    void  AiNodeParamInt(AtListT* params, int varoffset, const char* pname,
                         int pdefault) const;
    void  AiNodeParamUInt(AtListT* params, int varoffset, const char* pname,
                          unsigned int pdefault) const;
    void  AiNodeParamBool(AtListT* params, int varoffset, const char* pname,
                          bool pdefault) const;
    void  AiNodeParamFlt(AtListT* params, int varoffset, const char* pname,
                         float pdefault) const;
    void  AiNodeParamRGB(AtListT* params, int varoffset, const char* pname,
                         float r, float g, float b) const;
    void  AiNodeParamRGBA(AtListT* params, int varoffset, const char* pname,
                          float r, float g, float b, float a) const;
    void  AiNodeParamVec(AtListT* params, int varoffset, const char* pname,
                         float x, float y, float z) const;
    void  AiNodeParamVec2(AtListT* params, int varoffset, const char* pname,
                          float x, float y) const;
    void  AiNodeParamStr(AtListT* params, int varoffset, const char* pname,
                         const char* pdefault) const;
    void  AiNodeParamPtr(AtListT* params, int varoffset, const char* pname,
                         void* pdefault) const;
    void  AiNodeParamNode(AtListT* params, int varoffset, const char* pname,
                          AtNodeT* pdefault) const;
    void  AiNodeParamArray(AtListT* params, int varoffset, const char* pname,
                           AtArrayT* pdefault) const;
    void  AiNodeParamMtx(AtListT* params, int varoffset, const char* pname,
                         AtMatrixT matrix) const;
    void  AiNodeParamEnum(AtListT* params, int varoffset, const char* pname,
                          int pdefault, AtEnumT enum_type) const;
    void  AiNodeParamClosure(AtListT* params, int varoffset,
                             const char* pname) const;



    // -----------------------------------------------------------
    // AtEnum API ai_enum.h
    // -----------------------------------------------------------
    int         AiEnumGetValue(AtEnum enum_type, const char* string);
    const char* AiEnumGetString(AtEnum enum_type, int index);


    // -----------------------------------------------------------
    // AtNode API ai_nodes.h
    // -----------------------------------------------------------

    // AtNode Methods

    AtNodeT* AiNode(const AtStringT nentry_name,
                    const AtStringT name = AtStringT(),
                    const AtNodeT* parent = NULL) const;

    AtNodeT* AiNodeLookUpByName(const AtStringT name,
                                const AtNodeT* parent = NULL) const;

    // bool AiNodeDeclare(AtNode* node, const AtString param, const char* declaration);
    // const AtUserParamEntry* AiNodeLookUpUserParameter (const AtNode* node, const AtString param);
    // bool AiNodeIs(const AtNode* node, AtString str);
    // void AiNodeReset(AtNode* node);
    // void AiNodeResetParameter(AtNode* node, const char* param);
    // AtNode*AiNodeClone(const AtNode* node, const AtString new_name = AtString(), const AtNode* parent = NULL);
    bool AiNodeDestroy(AtNodeT*) const;
    // bool AiNodeLink(AtNode* src,  const char* input, AtNode* target);
    // bool AiNodeLinkOutput(AtNode* src,  const char* output, AtNode* target, const char* input);
    // bool AiNodeUnlink(AtNode* node, const char* input);
    // bool AiNodeIsLinked(const AtNode* node, const char* input);
    // AtNode* AiNodeGetLink(const AtNode* node, const char* input, int* comp = NULL);
    const char* AiNodeGetName(const AtNodeT* node) const;
    const AtNodeEntryT* AiNodeGetNodeEntry(const AtNodeT* node) const;
    // void* AiNodeGetLocalData(const AtNode* node);
    // void AiNodeSetLocalData(AtNode* node, void* data);
    // void* AiNodeGetPluginData(const AtNode* node);
    // void AiNodeSetDisabled(AtNode* node, bool disabled);
    // bool AiNodeIsDisabled(const AtNode* node);
    // AtNode* AiNodeGetParent(const AtNode* node);
    // AtUserParamIterator* AiNodeGetUserParamIterator(const AtNode* node);

    // Parameter Writers
    void AiNodeSetByte  (AtNodeT* node, const AtStringT param,
                         uint8_t val) const;
    void AiNodeSetInt   (AtNodeT* node, const AtStringT param, int val) const;
    void AiNodeSetUInt  (AtNodeT* node, const AtStringT param,
                         unsigned int val) const;
    void AiNodeSetBool  (AtNodeT* node, const AtStringT param, bool val) const;
    void AiNodeSetFlt   (AtNodeT* node, const AtStringT param, float val) const;
    void AiNodeSetPtr   (AtNodeT* node, const AtStringT param, void* val) const;
    void AiNodeSetArray (AtNodeT* node, const AtStringT param,
                         AtArray* val) const;
    void AiNodeSetMatrix(AtNodeT* node, const AtStringT param,
                         AtMatrix val) const;
    void AiNodeSetStr   (AtNodeT* node, const AtStringT param,
                         const AtStringT str) const;
    void AiNodeSetRGB   (AtNodeT* node, const AtStringT param,
                         float r, float g, float b) const;
    void AiNodeSetRGBA  (AtNodeT* node, const AtStringT param,
                         float r, float g, float b, float a) const;
    void AiNodeSetVec   (AtNodeT* node, const AtStringT param,
                         float x, float y, float z) const;
    void AiNodeSetVec2  (AtNodeT* node, const AtStringT param,
                         float x, float y) const;

    // Parameter Readers
    uint8_t AiNodeGetByte(const AtNodeT* node, const AtStringT param) const;
    int AiNodeGetInt(const AtNodeT* node, const AtStringT param) const;
    unsigned int AiNodeGetUInt  (const AtNodeT* node,
                                 const AtStringT param) const;
    bool AiNodeGetBool(const AtNodeT* node, const AtStringT param) const;
    float AiNodeGetFlt(const AtNodeT* node, const AtStringT param) const;
    AtRGBT AiNodeGetRGB(const AtNodeT* node, const AtStringT param) const;
    AtRGBAT AiNodeGetRGBA(const AtNodeT* node, const AtStringT param) const;
    AtVectorT AiNodeGetVec(const AtNodeT* node, const AtStringT param) const;
    AtVector2T AiNodeGetVec2(const AtNodeT* node, const AtStringT param) const;
    AtStringT AiNodeGetStr(const AtNodeT* node, const AtStringT param) const;
    void* AiNodeGetPtr(const AtNodeT* node, const AtStringT param) const;
    AtArrayT* AiNodeGetArray(const AtNodeT* node, const AtStringT param) const;
    AtMatrixT AiNodeGetMatrix(const AtNodeT* node, const AtStringT param) const;


    // -----------------------------------------------------------
    // AtNodeEntry API (ai_node_entry.h)
    // -----------------------------------------------------------

    // AtNodeEntry Methods
    const AtParamEntryT* AiNodeEntryLookUpParameter(
            const AtNodeEntryT* nentry, const AtStringT param) const;
    const AtNodeEntryT* AiNodeEntryLookUp(const AtStringT name) const;
    AtStringT AiNodeEntryGetNameAtString(const AtNodeEntryT* nentry) const;

    // -----------------------------------------------------------
    // Node Metadata API  (ai_metadata.h)
    // -----------------------------------------------------------

    void AiMetaDataSetStr(AtNodeEntry* nentry,
                          const char* param,
                          const char* name,
                          const char* value) const;


    // -----------------------------------------------------------
    // Message Logging API
    // -----------------------------------------------------------

    typedef void (*MsgFunc) (const char* format, ...);

    template<typename ...Args>
    void MsgFuncTrace(const MsgFunc msgFunc,
                      const char* file,
                      const int line,
                      const char* func,
                      const char* format,
                      Args &&...args) const
    {
        char prefixedFormat[BUFSIZ] = {0};
        strcat (prefixedFormat, "[%s] "); // type
        strcat (prefixedFormat, "[%s | %d | %s] "); // file, line, and func
        strcat (prefixedFormat, format);
        (*msgFunc)(prefixedFormat, PROCEDURAL_NAME, file, line, func,
                   std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void MsgFuncPrefix(const MsgFunc msgFunc,
                       const char* format,
                       Args &&...args) const
    {
        char prefixedFormat[BUFSIZ] = {0};
        strcat (prefixedFormat, "[%s] "); // type
        strcat (prefixedFormat, format);
        (*msgFunc)(prefixedFormat, PROCEDURAL_NAME,
                   std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgInfo(const char* file,
                   const int line,
                   const char* func,
                   const char* format,
                   Args &&...args) const
    {
        MsgFuncTrace(this->ai_msg_info_func_ptr, file, line, func, format,
                     std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgInfo(const char* format,
                   Args &&...args) const
    {
        MsgFuncPrefix(this->ai_msg_info_func_ptr, format,
                      std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgDebug(const char* file,
                   const int line,
                   const char* func,
                   const char* format,
                   Args &&...args) const
    {
        MsgFuncTrace(this->ai_msg_debug_func_ptr, file, line, func, format,
                     std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgDebug(const char* format,
                    Args &&...args) const
    {
        MsgFuncPrefix(this->ai_msg_debug_func_ptr, format,
                      std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgWarning(const char* file,
                   const int line,
                   const char* func,
                   const char* format,
                   Args &&...args) const
    {
        MsgFuncTrace(this->ai_msg_warning_func_ptr, file, line, func, format,
                     std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgWarning(const char* format,
                      Args &&...args) const
    {
        MsgFuncPrefix(this->ai_msg_warning_func_ptr, format,
                      std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgError(const char* file,
                   const int line,
                   const char* func,
                   const char* format,
                   Args &&...args) const
    {
        MsgFuncTrace(this->ai_msg_error_func_ptr, file, line, func, format,
                     std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgError(const char* format,
                      Args &&...args) const
    {
        MsgFuncPrefix(this->ai_msg_error_func_ptr, format,
                      std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgFatal(const char* file,
                   const int line,
                   const char* func,
                   const char* format,
                   Args &&...args) const
    {
        MsgFuncTrace(this->ai_msg_fatal_func_ptr, file, line, func, format,
                     std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void AiMsgFatal(const char* format,
                      Args &&...args) const
    {
        MsgFuncPrefix(this->ai_msg_fatal_func_ptr, format,
                      std::forward<Args>(args)...);
    }

private:

    MsgFunc ai_msg_info_func_ptr {::AiMsgInfo};
    MsgFunc ai_msg_debug_func_ptr {::AiMsgDebug};
    MsgFunc ai_msg_warning_func_ptr {::AiMsgWarning};
    MsgFunc ai_msg_error_func_ptr {::AiMsgError};
    MsgFunc ai_msg_fatal_func_ptr {::AiMsgFatal};

}; // class ArnoldFacade

// -----------------------------------------------------------
// Custom Node Deleter
// -----------------------------------------------------------

bool NodeDeleter(typename ArnoldFacade::AtNodeT* node, const ArnoldFacade& af);

} // namespace MaterialXToArnold

#endif // MTLX_TO_A_ARNOLD_FACADE_H
