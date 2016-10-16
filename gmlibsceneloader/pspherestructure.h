#ifndef PSPHERESTRUCTURE_H
#define PSPHERESTRUCTURE_H

#include "psurfstructure.h"

class PSphereStructure : public PSurfStructure
{
public:

    using PSurfStructure::PSurfStructure;

    PSphereStructure();
    ~PSphereStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PSPHERESTRUCTURE_H
