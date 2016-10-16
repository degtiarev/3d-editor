#include "setpositionstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectdatastructure.h"

// stl
#include "iostream"

SetPositionStructure::SetPositionStructure()
    : SceneObjectDataStructure( int( GMStructTypes::SetPosition ) )
{
    std::cout << "Constructing a SetPosition object" << std::endl;
}

bool
SetPositionStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    auto result = ( structure->GetStructureType() == ODDL::kDataDouble );
    return result;
}
