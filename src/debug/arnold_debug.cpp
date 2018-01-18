#include <sstream>
#include <regex>

#include <ai.h>

namespace ArnoldDebug
{

void Filename(std::ostringstream& os, const AtNodeEntry* nentry)
{
    const char* filename = AiNodeEntryGetFilename(nentry);
    if (filename == nullptr) os << "<built-in>";
    else os << filename;
}

void OutputTypeName(std::ostringstream& os, const AtNodeEntry* nentry)
{
    const int outputType = AiNodeEntryGetOutputType(nentry);
    if (outputType >= AI_TYPE_BYTE && outputType <= AI_TYPE_CLOSURE)
        os << AiParamGetTypeName(static_cast<uint8_t>(outputType));
    else if (outputType == AI_TYPE_USHORT)
        os << "UShort";
    else if (outputType == AI_TYPE_HALF)
        os << "Half";
    else
        os << "None";
}

void RGB(std::ostringstream& os, const AtRGB& c)
{
    os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
}

void RGBA(std::ostringstream& os, const AtRGBA& c)
{
    os << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
}

void Vector(std::ostringstream& os, const AtVector& v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

void Vector2(std::ostringstream& os, const AtVector2& v)
{
    os << "(" << v.x << ", " << v.y << ")";
}

void String(std::ostringstream& os, const AtString& s)
{
    const char* cstr = s.c_str();
    if(strlen(cstr) == 0) os << "\"\"";
    else os << s.c_str();
}

void Pointer(std::ostringstream& os, const void* p)
{
    os << p;
}

void NodeName(std::ostringstream& os, const void* n)
{
    if(n == nullptr)
    {
        os << "";
    }
    else
    {
        const AtNode* node = static_cast<const AtNode*>(n);
        os << AiNodeGetName(node);
    }
}

void ArrayElement(std::ostringstream& os, const AtArray* a, uint32_t i);

void Array(std::ostringstream& os, const AtArray* a)
{
    os << "[";
    const uint32_t n = AiArrayGetNumElements(a);
    const uint32_t n_minus_one = n-1;
    for(uint32_t i = 0; i < n; i++)
    {
        ArrayElement(os, a, i);
        if(i < n_minus_one) os << ", ";
    }
    os << "]";
}

void Matrix(std::ostringstream& os, const AtMatrix* m)
{
    os << "[";
    for(int i = 0; i < 16; i++)
    {
        os << &(m[i]);
        if(i < 15) os << ", ";
    }
    os << "]";
}

void Enum(std::ostringstream& os, const AtEnum e, const int i)
{
    os << AiEnumGetString(e, i);
}

void ArrayElement(std::ostringstream& os, const AtArray* a, uint32_t i)
{
    const uint8_t etype = AiArrayGetType(a);
    switch(etype)
    {
        case AI_TYPE_BYTE:
        {
            os << AiArrayGetByte(a, i);
            break;
        }
        case AI_TYPE_INT:
        {
            os << AiArrayGetInt(a, i);
            break;
        }
        case AI_TYPE_UINT:
        {
            os << AiArrayGetUInt(a, i);
            break;
        }
        case AI_TYPE_BOOLEAN:
        {
            os << AiArrayGetBool(a, i);
            break;
        }
        case AI_TYPE_FLOAT:
        {
            os << AiArrayGetFlt(a, i);
            break;
        }
        case AI_TYPE_RGB:
        {
            const AtRGB e = AiArrayGetRGB(a, i);
            RGB(os, e);
            break;
        }
        case AI_TYPE_RGBA:
        {
            const AtRGBA e = AiArrayGetRGBA(a, i);
            RGBA(os, e);
            break;
        }
        case AI_TYPE_VECTOR:
        {
            const AtVector e = AiArrayGetVec(a, i);
            Vector(os, e);
            break;
        }
        case AI_TYPE_VECTOR2:
        {
            const AtVector2 e = AiArrayGetVec2(a, i);
            Vector2(os, e);
            break;
        }
        case AI_TYPE_STRING:
        {
            const AtString e = AiArrayGetStr(a, i);
            String(os, e);
            break;
        }
        case AI_TYPE_POINTER:
        {
            void* e = AiArrayGetPtr(a, i);
            Pointer(os, e);
            break;
        }
        case AI_TYPE_NODE:
        {
            void* e = AiArrayGetPtr(a, i);
            NodeName(os, e);
            break;
        }
        case AI_TYPE_ARRAY:
        {
            const AtArray* e = AiArrayGetArray(a, i);
            Array(os, e);
            break;
        }
        case AI_TYPE_MATRIX:
        {
            const AtMatrix e = AiArrayGetMtx(a, i);
            Matrix(os, &e);
            break;
        }
        default:
            AiMsgFatal("A value of %d is not a valid AiArray element type",
                       etype);
            break;
    }

}

void Value(std::ostringstream& os,
           const AtNode* node,
           const AtString pname,
           const uint8_t ptype)
{
    switch(ptype)
    {
        case AI_TYPE_BYTE:
        {
            os << static_cast<unsigned int>(AiNodeGetByte(node, pname));
            break;
        }
        case AI_TYPE_INT:
        {
            os << AiNodeGetInt(node, pname);
            break;
        }
        case AI_TYPE_UINT:
        {
            os << AiNodeGetUInt(node, pname);
            break;
        }
        case AI_TYPE_BOOLEAN:
        {
            os << AiNodeGetBool(node, pname);
            break;
        }
        case AI_TYPE_FLOAT:
        {
            os << AiNodeGetFlt(node, pname);
            break;
        }
        case AI_TYPE_RGB:
        {
            RGB(os, AiNodeGetRGB(node, pname));
            break;
        }
        case AI_TYPE_RGBA:
        {
            RGBA(os, AiNodeGetRGB(node, pname));
            break;
        }
        case AI_TYPE_VECTOR:
        {
            Vector(os, AiNodeGetVec(node, pname));
            break;
        }
        case AI_TYPE_VECTOR2:
        {
            Vector2(os, AiNodeGetVec2(node, pname));
            break;
        }
        case AI_TYPE_STRING:
        {
            String(os, AiNodeGetStr(node, pname));
            break;
        }
        case AI_TYPE_POINTER:
        {
            Pointer(os, AiNodeGetPtr(node, pname));
            break;
        }
        case AI_TYPE_NODE:
        {
            NodeName(os, AiNodeGetPtr(node, pname));
            break;
        }
        case AI_TYPE_ARRAY:
        {
            Array(os, AiNodeGetArray(node, pname));
            break;
        }
        case AI_TYPE_MATRIX:
        {
            const AtMatrix m = AiNodeGetMatrix(node, pname);
            Matrix(os, &m);
            break;
        }
        case AI_TYPE_ENUM:
        {
            const AtNodeEntry* nentry = AiNodeGetNodeEntry(node);
            const AtParamEntry* pentry = AiNodeEntryLookUpParameter(nentry,
                                                                  pname);
            Enum(os, AiParamGetEnum(pentry), AiNodeGetInt(node, pname));
            break;
        }
        default:
            AiMsgFatal("A value of %d is not a valid parameter value type",
                       ptype);
            break;
    }
}

void Default(std::ostringstream& os,
             const AtParamEntry* pentry,
             const uint8_t ptype)
{
    const AtParamValue* pdefault = AiParamGetDefault(pentry);
    switch(ptype)
    {
        case AI_TYPE_BYTE:
        {
            os << static_cast<unsigned int>(pdefault->BYTE());
            break;
        }
        case AI_TYPE_INT:
        {
            os << pdefault->INT();
            break;
        }
        case AI_TYPE_UINT:
        {
            os << pdefault->UINT();
            break;
        }
        case AI_TYPE_BOOLEAN:
        {
            os << pdefault->BOOL();
            break;
        }
        case AI_TYPE_FLOAT:
        {
            os << pdefault->FLT();
            break;
        }
        case AI_TYPE_RGB:
        {
            RGB(os, pdefault->RGB());
            break;
        }
        case AI_TYPE_RGBA:
        {
            RGBA(os, pdefault->RGBA());
            break;
        }
        case AI_TYPE_VECTOR:
        {
            Vector(os, pdefault->VEC());
            break;
        }
        case AI_TYPE_VECTOR2:
        {
            Vector2(os, pdefault->VEC2());
            break;
        }
        case AI_TYPE_STRING:
        {

            String(os, pdefault->STR());
            break;
        }
        case AI_TYPE_POINTER:
        {
            Pointer(os, pdefault->PTR());
            break;
        }
        case AI_TYPE_NODE:
        {
            NodeName(os, pdefault->PTR());
            break;
        }
        case AI_TYPE_ARRAY:
        {
            Array(os, pdefault->ARRAY());
            break;
        }
        case AI_TYPE_MATRIX:
        {
            Matrix(os, pdefault->pMTX());
            break;
        }
        case AI_TYPE_ENUM:
        {
            Enum(os, AiParamGetEnum(pentry), pdefault->INT());
            break;
        }
        default:
            AiMsgFatal("A value of %d is not a valid default value type",
                       ptype);
            break;
    }
}

void Category(std::ostringstream& os, const AtUserParamEntry* upentry)
{
    uint8_t category = AiUserParamGetCategory(upentry);
    switch(category)
    {
        case AI_USERDEF_CONSTANT:
        {
            os << "CONSTANT";
            break;
        }
        case AI_USERDEF_UNIFORM:
        {
            os << "UNIFORM";
            break;
        }
        case AI_USERDEF_VARYING:
        {
            os << "VARYING";
            break;
        }
        case AI_USERDEF_INDEXED:
        {
            os << "INDEXED";
            break;
        }
        default:
            AiMsgFatal("A value of %d is not a valid category type", category);
            break;
    }
}

void UserParameter(std::ostringstream& os,
                   const AtNode* node,
                   const char* name,
                   const AtUserParamEntry* upentry,
                   const unsigned int indent,
                   const unsigned int index)
{
    uint8_t uptype = AiUserParamGetType(upentry);
    const AtString upname{AiUserParamGetName(upentry)};

    os << std::string(indent, ' ');
    os << "user_param: " << name << "[" << index << "]" << std::endl;

    os << std::string(indent, ' ');
    os << "name: " <<  AiUserParamGetName(upentry) << std::endl;

    os << std::string(indent, ' ');
    os << "category: ";
    Category(os, upentry);
    os << std::endl;

    os << std::string(indent, ' ');
    os << "type: " <<  AiParamGetTypeName(uptype) << std::endl;

    os << std::string(indent, ' ');
    os << "value: ";
    Value(os, node, upname, uptype);
    os << "\n" << std::endl;
}

void UserParameters(std::ostringstream& os,
                    const AtNode* node,
                    const char* name,
                    const unsigned int indent,
                    unsigned int& n)
{
    n = 0;
    AtUserParamIterator* it = AiNodeGetUserParamIterator(node);
    while(const AtUserParamEntry* upentry = AiUserParamIteratorGetNext(it))
    {
        UserParameter(os, node, name, upentry, indent, n);
        n++;
    }
    AiUserParamIteratorDestroy( it );
}

void Parameter(std::ostringstream& os,
               const AtNode* node,
               const char* name,
               const AtNodeEntry* nentry,
               const int index,
               const unsigned int indent)
{
        const AtParamEntry* pentry = AiNodeEntryGetParameter(nentry, index);
        const AtString pname = AiParamGetName(pentry);
        uint8_t ptype = AiParamGetType(pentry);

        os << std::string(indent, ' ');
        os << "param: " << name << "[" << index << "]" << std::endl;

        os << std::string(indent, ' ');
        os << "name: " << pname.c_str() << std::endl;

        os << std::string(indent, ' ');
        os << "type: " << AiParamGetTypeName(ptype) << std::endl;

        os << std::string(indent, ' ');
        os << "default: ";
        Default(os, pentry, ptype);
        os << std::endl;

        os << std::string(indent, ' ');
        os << "value: ";
        Value(os, node, pname, ptype);
        os << "\n" << std::endl;

}

void Parameters(std::ostringstream& os,
                const AtNode* node,
                const char* name,
                const AtNodeEntry* nentry,
                const int num_params,
                const unsigned int indent)
{
    for(int i = 0; i < num_params; i++)
    {
        Parameter(os, node, name, nentry, i, indent);
    }
}

void Parameters(std::ostringstream& os,
                const AtNode* node,
                const char* name,
                const AtNodeEntry* nentry,
                const unsigned int indent)
{
    const int num_params = AiNodeEntryGetNumParams(nentry);
    Parameters(os, node, name, nentry, num_params, indent);
}

void Node(std::ostringstream& os,
          const AtNode* node,
          const unsigned int indent)
{
    const char* name = AiNodeGetName(node);
    const AtNodeEntry* nentry = AiNodeGetNodeEntry(node);

    const int num_params = AiNodeEntryGetNumParams(nentry);

    std::ostringstream upos;
    unsigned int num_user_params = 0;
    UserParameters(upos, node, name, indent, num_user_params);

    os << "" << std::endl;
    os << "name: " << name << std::endl;
    os << "entry_name: " << AiNodeEntryGetName(nentry) << std::endl;
    os << "type: " << AiNodeEntryGetTypeName(nentry) << std::endl;
    os << "output_type: ";
    OutputTypeName(os, nentry);
    os << std::endl;
    os << "num_params: " << num_params << std::endl;
    os << "num_user_params: " << num_user_params << std::endl;
    os << "filename: ";
    Filename(os, nentry);
    os << std::endl;
    os << "version: " << AiNodeEntryGetVersion(nentry) << std::endl;
    os << "params: " << std::endl;
    Parameters(os, node, name, nentry, num_params, indent);
    os << "user_params: " << std::endl;
    os << upos.str();
    os << "" << std::endl;
}

void NodesRegEx(std::ostringstream& os,
                unsigned int node_mask = AI_NODE_ALL,
                const char* node_name_regex = nullptr,
                const unsigned int indent = 4)
{
    std::regex e{node_name_regex};
    AtNodeIterator* iter = AiUniverseGetNodeIterator(node_mask);
    while(const AtNode* node = AiNodeIteratorGetNext(iter))
    {
        const char* name = AiNodeGetName(node);
        if (std::regex_match(std::string(name), e)) {
            Node(os, node, indent);
        }
    }
    AiNodeIteratorDestroy(iter);
}

void NodesNoRegEx(std::ostringstream& os,
                  unsigned int node_mask = AI_NODE_ALL,
                  const unsigned int indent = 4)
{
    AtNodeIterator* iter = AiUniverseGetNodeIterator(node_mask);
    while(const AtNode* node = AiNodeIteratorGetNext(iter))
    {
        Node(os, node, indent);
    }
    AiNodeIteratorDestroy(iter);
}

void Nodes(std::ostringstream& os,
           unsigned int node_mask = AI_NODE_ALL,
           const char* node_name_regex = nullptr,
           const unsigned int indent = 4)
{
    if(node_name_regex == nullptr) NodesNoRegEx(os, node_mask, indent);
    else NodesRegEx(os, node_mask, node_name_regex, indent);
}

} // namespace ArnoldDebug
