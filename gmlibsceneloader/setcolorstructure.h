#ifndef SETCOLORSTRUCTURE_H
#define SETCOLORSTRUCTURE_H

#include "sceneobjectdatastructure.h"

class SetColorStructure : public SceneObjectDataStructure
{
public:
    SetColorStructure();
    ~SetColorStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;

};

#endif // SETCOLORSTRUCTURE_H
