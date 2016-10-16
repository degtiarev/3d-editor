#ifndef PCYLINDERDATASTRUCTURE_H
#define PCYLINDERDATASTRUCTURE_H

#include "pcylinderstructure.h"

class PCylinderDataStructure : public PCylinderStructure
{
public:

    PCylinderDataStructure();
    ~PCylinderDataStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;

};

#endif // PCYLINDERDATASTRUCTURE_H
