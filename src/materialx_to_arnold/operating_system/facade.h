#ifndef MTLX_TO_A_OPERATING_SYSTEM_H
#define MTLX_TO_A_OPERATING_SYSTEM_H

namespace MaterialXToArnold
{

class OperatingSystem
{
public:
    const char* getenv(const char * name) const;
};

}

#endif // MTLX_TO_A_OPERATING_SYSTEM_H
