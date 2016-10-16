#ifndef SCENEOBJECTDATASTRUCTURE_H
#define SCENEOBJECTDATASTRUCTURE_H

#include "sceneobjectstructure.h"

class SceneObjectDataStructure : public SceneObjectStructure
{
public:

    using SceneObjectStructure::SceneObjectStructure;

    SceneObjectDataStructure();
    ~SceneObjectDataStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // SCENEOBJECTDATASTRUCTURE_H
