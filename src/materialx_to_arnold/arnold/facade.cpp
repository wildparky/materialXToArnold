#include "arnold/facade.h"

#include <string>
#include <sstream>

#include "macros.h"
#include "constants.h"

#include <ai.h>

namespace MaterialXToArnold
{

using AF = ArnoldFacade;

// -----------------------------------------------------------
// AiUniverse API (ai_universe.h)
// -----------------------------------------------------------
AF::AtNodeT* AF::AiUniverseGetOptions() const
{
    return ::AiUniverseGetOptions();
}

// --------------------------------------
// AtParamEntry API Start (ai_params.h)
// --------------------------------------

void  AF::AiNodeParamByte(AtListT* params, int varoffset, const char* pname,
                          uint8_t pdefault) const
{
    ::AiNodeParamByte(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamInt(AtListT* params, int varoffset, const char* pname,
                         int pdefault) const
{
    ::AiNodeParamInt(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamUInt(AtListT* params, int varoffset, const char* pname,
                          unsigned int pdefault) const
{
    ::AiNodeParamUInt(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamBool(AtListT* params, int varoffset, const char* pname,
                          bool pdefault) const
{
    ::AiNodeParamBool(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamFlt(AtListT* params, int varoffset,  const char* pname,
                         float pdefault) const
{
    ::AiNodeParamFlt(params, varoffset,  pname, pdefault);
}

void  AF::AiNodeParamRGB(AtListT* params, int varoffset, const char* pname,
                         float r, float g, float b) const
{
    ::AiNodeParamRGB(params, varoffset, pname, r, g, b);
}

void  AF::AiNodeParamRGBA(AtListT* params, int varoffset,  const char* pname,
                          float r, float g, float b, float a) const
{
    ::AiNodeParamRGBA(params, varoffset,  pname, r, g, b, a);
}

void  AF::AiNodeParamVec(AtListT* params, int varoffset, const char* pname,
                         float x, float y, float z) const
{
    ::AiNodeParamVec(params, varoffset, pname, x, y, z);
}

void  AF::AiNodeParamVec2(AtListT* params, int varoffset, const char* pname,
                          float x, float y) const
{
    ::AiNodeParamVec2(params, varoffset, pname, x, y);
}

void  AF::AiNodeParamStr(AtListT* params, int varoffset, const char* pname,
                         const char* pdefault) const
{
    ::AiNodeParamStr(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamPtr(AtListT* params, int varoffset, const char* pname,
                         void* pdefault) const
{
    ::AiNodeParamPtr(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamNode(AtListT* params, int varoffset, const char* pname,
                          AtNodeT* pdefault) const
{
    ::AiNodeParamNode(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamArray(AtListT* params, int varoffset, const char* pname,
                           AtArrayT* pdefault) const
{
    ::AiNodeParamArray(params, varoffset, pname, pdefault);
}

void  AF::AiNodeParamMtx(AtListT* params, int varoffset, const char* pname,
                         AtMatrixT matrix) const
{
    ::AiNodeParamMtx(params, varoffset, pname, matrix);
}

void  AF::AiNodeParamEnum(AtListT* params, int varoffset, const char* pname,
                          int pdefault, AtEnum enum_type) const
{
    ::AiNodeParamEnum(params, varoffset, pname, pdefault, enum_type);
}

void  AF::AiNodeParamClosure(AtListT* params, int varoffset, const char* pname
                             ) const
{
    ::AiNodeParamClosure(params, varoffset, pname);
}


// -----------------------------------------------------------
// AtNode API ai_nodes.h
// -----------------------------------------------------------

// AtNode Methods

AF::AtNodeT* AF::AiNode(const AtStringT nentry_name, const AtStringT name,
                        const AtNodeT* parent) const
{
   return ::AiNode(nentry_name, name, parent);
}

AF::AtNodeT* AF::AiNodeLookUpByName(const AtStringT name,
                                    const AtNodeT* parent) const
{
   return ::AiNodeLookUpByName(name, parent);
}

bool AF::AiNodeDestroy(AtNodeT* node) const
{
   return ::AiNodeDestroy(node);
}

const char* AF::AiNodeGetName(const AtNodeT* node) const
{
    return ::AiNodeGetName(node);
}

const AF::AtNodeEntryT* AF::AiNodeGetNodeEntry(const AtNodeT* node) const
{
    return ::AiNodeGetNodeEntry(node);
}

// AtNode Parameter Writers
void AF::AiNodeSetByte(AtNodeT* node, const AtStringT param,
                      uint8_t val) const
{
    ::AiNodeSetByte(node, param, val);
}

void AF::AiNodeSetInt(AtNodeT* node, const AtStringT param, int val) const
{
    ::AiNodeSetInt(node, param, val);
}

void AF::AiNodeSetUInt(AtNodeT* node, const AtStringT param,
                       unsigned int val) const
{
    ::AiNodeSetUInt(node, param, val);
}

void AF::AiNodeSetBool(AtNodeT* node, const AtStringT param, bool val) const
{
    ::AiNodeSetBool(node, param, val);
}

void AF::AiNodeSetFlt(AtNodeT* node, const AtStringT param, float val) const
{
    ::AiNodeSetFlt(node, param, val);
}

void AF::AiNodeSetPtr(AtNodeT* node, const AtStringT param, void* val) const
{
    ::AiNodeSetPtr(node, param, val);
}

void AF::AiNodeSetArray(AtNodeT* node, const AtStringT param,
                         AtArrayT* val) const
{
    ::AiNodeSetArray(node, param, val);
}

void AF::AiNodeSetMatrix(AtNodeT* node, const AtStringT param,
                     AtMatrixT val) const
{
    ::AiNodeSetMatrix(node, param, val);
}

void AF::AiNodeSetStr(AtNodeT* node, const AtStringT param,
                     const AtStringT str) const
{
    ::AiNodeSetStr(node, param, str);
}

void AF::AiNodeSetRGB(AtNodeT* node, const AtStringT param,
                     float r, float g, float b) const
{
    ::AiNodeSetRGB(node, param, r, g, b);
}

void AF::AiNodeSetRGBA(AtNodeT* node, const AtStringT param,
                     float r, float g, float b, float a) const
{
    ::AiNodeSetRGBA(node, param, r, g, b, a);
}

void AF::AiNodeSetVec(AtNodeT* node, const AtStringT param,
                     float x, float y, float z) const
{
    ::AiNodeSetVec(node, param, x, y, z);
}

void AF::AiNodeSetVec2(AtNodeT* node, const AtStringT param,
                       float x, float y) const
{
    ::AiNodeSetVec2(node, param, x, y);
}

// AtNode Parameter Readers
uint8_t AF::AiNodeGetByte(const AtNodeT* node, const AtStringT param) const
{
    return ::AiNodeGetByte(node, param);
}

int AF::AiNodeGetInt(const AtNodeT* node, const AtStringT param) const
{
    return ::AiNodeGetInt(node, param);
}

unsigned int AF::AiNodeGetUInt(const AtNodeT* node,
                               const AtStringT param) const
{
    return ::AiNodeGetUInt(node, param);
}

bool AF::AiNodeGetBool(const AtNodeT* node, const AtStringT param) const
{
    return ::AiNodeGetBool(node, param);
}

float AF::AiNodeGetFlt(const AtNodeT* node, const AtStringT param) const
{
    return ::AiNodeGetFlt(node, param);
}

AF::AtRGBT AF::AiNodeGetRGB(const AtNodeT* node, const AtStringT param) const
{
    return ::AiNodeGetRGB(node, param);

}

AF::AtRGBAT AF::AiNodeGetRGBA(const AtNodeT* node, const AtStringT param) const
{
    return ::AiNodeGetRGBA(node, param);
}

AF::AtVectorT AF::AiNodeGetVec(const AtNodeT* node, const AtStringT param) const
{
    return ::AiNodeGetVec(node, param);
}

AF::AtVector2T AF::AiNodeGetVec2(const AtNodeT* node,
                                 const AtStringT param) const
{
    return ::AiNodeGetVec2(node, param);
}

AF::AtStringT AF::AiNodeGetStr(const AtNodeT* node,
                               const AtStringT param) const
{
    return ::AiNodeGetStr(node, param);
}

void* AF::AiNodeGetPtr(const AtNodeT* node,
                       const AtStringT param) const
{
    return ::AiNodeGetPtr(node, param);
}

AF::AtArrayT* AF::AiNodeGetArray(const AtNodeT* node,
                                 const AtStringT param) const
{
    return ::AiNodeGetArray(node, param);
}

AF::AtMatrixT AF::AiNodeGetMatrix(const AtNodeT* node,
                                  const AtStringT param) const
{
    return ::AiNodeGetMatrix(node, param);
}


// -----------------------------------------------------------
// AtNodeEntry API (ai_node_entry.h)
// -----------------------------------------------------------

// AtNodeEntry Methods
const AF::AtParamEntryT* AF::AiNodeEntryLookUpParameter(
        const AtNodeEntryT* nentry,
        const AtStringT param) const
{
    return ::AiNodeEntryLookUpParameter(nentry, param);
}

const AF::AtNodeEntryT* AF::AiNodeEntryLookUp(const AtStringT name) const
{
    return ::AiNodeEntryLookUp(name);

}

AF::AtStringT AF::AiNodeEntryGetNameAtString(const AtNodeEntryT* nentry) const
{
    return ::AiNodeEntryGetNameAtString(nentry);
}

// -----------------------------------------------------------
// Node Metadata API  (ai_metadata.h)
// -----------------------------------------------------------

void AF::AiMetaDataSetStr(AtNodeEntry *nentry,
                          const char* param,
                          const char* name,
                          const char* value) const
{
    ::AiMetaDataSetStr(nentry, param, name, value);
}

// -----------------------------------------------------------
// Custom Node Deleter
// -----------------------------------------------------------

bool NodeDeleter(typename ArnoldFacade::AtNodeT* node,
                 const ArnoldFacade& af)
{
    std::stringstream ss;
    ss << "Destroyed a node with type " <<
          ::AiNodeEntryGetTypeName(::AiNodeGetNodeEntry(node)) <<
          " and name \"" << ::AiNodeGetName(node) << "\".";
    bool result = af.AiNodeDestroy(node);
    MSG_DEBUG(af, ss.str().c_str());
    return result;
}


} // namespce MaterialXToArnold
