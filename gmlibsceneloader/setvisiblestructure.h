#ifndef SETVISIBLESTRUCTURE_H
#define SETVISIBLESTRUCTURE_H

#include "../openddl/openddl.h"

class SetVisibleStructure : public ODDL::Structure
{
public:
    SetVisibleStructure();
    ~SetVisibleStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescribtion, const Structure *structure ) const override;
};

#endif // SETVISIBLESTRUCTURE_H
