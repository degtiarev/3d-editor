#ifndef SCENEOBJECTSTRUCTURE_H
#define SCENEOBJECTSTRUCTURE_H

#include "../openddl/openddl.h"

class SceneObjectStructure : public ODDL::Structure
{
public:

    using Structure::Structure;

    SceneObjectStructure();
    ~SceneObjectStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *DataDescription, const Structure *structure ) const override;
};

#endif // SCENEOBJECTSTRUCTURE_H
