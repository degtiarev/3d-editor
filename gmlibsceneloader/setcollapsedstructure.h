#ifndef SETCOLLAPSEDSTRUCTURE_H
#define SETCOLLAPSEDSTRUCTURE_H

#include "sceneobjectdatastructure.h"

class SetCollapsedStructure : public SceneObjectDataStructure
{
public:
    SetCollapsedStructure();
    ~SetCollapsedStructure() = default;

    bool    ValidateSubstructure(const ODDL::DataDescription *dataDescribtion, const Structure *structure) const override;
};

#endif // SETCOLLAPSEDSTRUCTURE_H
