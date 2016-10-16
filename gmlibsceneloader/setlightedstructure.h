#ifndef SETLIGHTEDSTRUCTURE_H
#define SETLIGHTEDSTRUCTURE_H

#include "../openddl/openddl.h"

class SetLightedStructure : public ODDL::Structure
{
public:
    SetLightedStructure();
    ~SetLightedStructure() = default;

    bool    ValidateSubstructure(const ODDL::DataDescription *dataDescribtion, const Structure *structure) const override;
};

#endif // SETLIGHTEDSTRUCTURE_H
