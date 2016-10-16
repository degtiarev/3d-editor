#ifndef PSURFSTRUCTURE_H
#define PSURFSTRUCTURE_H

#include "sceneobjectstructure.h"

class PSurfStructure : public SceneObjectStructure
{
public:
    
    using SceneObjectStructure::SceneObjectStructure;
    
    PSurfStructure();
    ~PSurfStructure() = default;
    
    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // PSURFSTRUCTURE_H
