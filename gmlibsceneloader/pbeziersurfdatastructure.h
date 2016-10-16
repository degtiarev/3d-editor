#ifndef PBEZIERSURFDATASTRUCTURE_H
#define PBEZIERSURFDATASTRUCTURE_H

#include "sceneobjectstructure.h"

class PBezierSurfDataStructure : public SceneObjectStructure
{
public:
    PBezierSurfDataStructure();
    ~PBezierSurfDataStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;

};

#endif // PBEZIERSURFDATASTRUCTURE_H
