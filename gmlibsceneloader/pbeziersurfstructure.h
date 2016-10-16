#ifndef PBEZIERSURFSTRUCTURE_H
#define PBEZIERSURFSTRUCTURE_H

#include "psurfstructure.h"

class PBezierSurfStructure : public PSurfStructure
{
public:
    PBezierSurfStructure();
    ~PBezierSurfStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *DataDescription, const Structure *structure ) const override;
};

#endif // PBEZIERSURFSTRUCTURE_H
