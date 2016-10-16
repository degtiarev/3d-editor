#ifndef PTORUSSTRUCTURE_H
#define PTORUSSTRUCTURE_H

#include "psurfstructure.h"


class PTorusStructure : public PSurfStructure
{
public:

    using PSurfStructure::PSurfStructure;

    PTorusStructure();
    ~PTorusStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PTORUSSTRUCTURE_H
