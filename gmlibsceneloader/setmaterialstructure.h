#ifndef SETMATERIALSTRUCTURE_H
#define SETMATERIALSTRUCTURE_H

#include "sceneobjectdatastructure.h"

class SetMaterialStructure : public SceneObjectDataStructure
{
public:

    using SceneObjectDataStructure::SceneObjectDataStructure;

    SetMaterialStructure();
    ~SetMaterialStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // SETMATERIALSTRUCTURE_H
