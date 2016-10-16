#include "setcollapsedstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectdatastructure.h"

// stl
#include "iostream"

SetCollapsedStructure::SetCollapsedStructure()
    : SceneObjectDataStructure ( int( GMStructTypes::SetCollapsed ) )
{
    std::cout << "Constructing a SetCollapsedStructure object" << std::endl;
}

bool
SetCollapsedStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    return (structure->GetStructureType() == ODDL::kDataBool);
}
