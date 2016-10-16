#ifndef PTORUSDATASTRUCTURE_H
#define PTORUSDATASTRUCTURE_H

#include "ptorusstructure.h"

class PTorusDataStructure : public PTorusStructure
{
public:

    using PTorusStructure::PTorusStructure;

    PTorusDataStructure();
    ~PTorusDataStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PTORUSDATASTRUCTURE_H
