#ifndef PSURFDATASTRUCTURE_H
#define PSURFDATASTRUCTURE_H

#include "psurfstructure.h"

class PSurfDataStructure : public PSurfStructure
{
public:

    using PSurfStructure::PSurfStructure;

    PSurfDataStructure();
    ~PSurfDataStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PSURFDATASTRUCTURE_H
