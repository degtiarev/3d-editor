#ifndef MATERIAL_H
#define MATERIAL_H

#include "setmaterialstructure.h"

class MaterialStructure : public SetMaterialStructure
{
public:
    MaterialStructure();
    ~MaterialStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // MATERIAL_H
