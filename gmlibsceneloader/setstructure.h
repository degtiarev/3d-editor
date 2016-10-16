#ifndef SETSTRUCTURE_H
#define SETSTRUCTURE_H

#include "sceneobjectdatastructure.h"

class SetStructure : public SceneObjectDataStructure
{
public:

    using SceneObjectDataStructure::SceneObjectDataStructure;

    SetStructure();
    ~SetStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // SETSTRUCTURE_H
