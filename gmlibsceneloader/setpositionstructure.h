#ifndef SETPOSITIONSTRUCTURE_H
#define SETPOSITIONSTRUCTURE_H

#include "sceneobjectdatastructure.h"


class SetPositionStructure : public SceneObjectDataStructure
{
public:

    using SceneObjectDataStructure::SceneObjectDataStructure;

    SetPositionStructure();
    ~SetPositionStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // SETPOSITIONSTRUCTURE_H
