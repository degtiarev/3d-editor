#ifndef PSPHEREDATASTRUCTURE_H
#define PSPHEREDATASTRUCTURE_H

#include "pspherestructure.h"

class PSphereDataStructure : public PSphereStructure
{
public:

    PSphereDataStructure();
    ~PSphereDataStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PSPHEREDATASTRUCTURE_H
