#ifndef PPLANESTRUCTURE_H
#define PPLANESTRUCTURE_H

#include "psurfstructure.h"

class PPlaneStructure : public PSurfStructure
{
public:
    PPlaneStructure();
    ~PPlaneStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PPLANESTRUCTURE_H
