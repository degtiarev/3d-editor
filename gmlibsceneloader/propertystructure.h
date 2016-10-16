#ifndef PROPERTYSTRUCTURE_H
#define PROPERTYSTRUCTURE_H

#include "../openddl/openddl.h"

class PropertyStructure : public ODDL::Structure
{
public:
    PropertyStructure();
    ~PropertyStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PROPERTYSTRUCTURE_H
