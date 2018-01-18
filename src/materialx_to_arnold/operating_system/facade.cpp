#include "operating_system/facade.h"

#include <stdlib.h>

namespace MaterialXToArnold
{

const char* OperatingSystem::getenv(const char* name) const
{
  return ::getenv(name);
}

}

