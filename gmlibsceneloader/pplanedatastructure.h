#ifndef PPLANEDATASTRUCTURE_H
#define PPLANEDATASTRUCTURE_H

#include "sceneobjectstructure.h"

class PPlaneDataStructure : public SceneObjectStructure
{
public:
    PPlaneDataStructure();
    ~PPlaneDataStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PPLANEDATASTRUCTURE_H
