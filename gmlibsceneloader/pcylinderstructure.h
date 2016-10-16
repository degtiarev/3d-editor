#ifndef PCYLINDERSTRUCTURE_H
#define PCYLINDERSTRUCTURE_H

#include "psurfstructure.h"

class PCylinderStructure : public PSurfStructure
{
public:

    using PSurfStructure::PSurfStructure;

    PCylinderStructure();
    ~PCylinderStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PCYLINDERSTRUCTURE_H
