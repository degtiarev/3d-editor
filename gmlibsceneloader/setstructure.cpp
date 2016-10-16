#include "setstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectdatastructure.h"

// stl
#include "iostream"

SetStructure::SetStructure()
    : SceneObjectDataStructure( int( GMStructTypes::Set ) )
{
    std::cout << "Constructing a Set object" << std::endl;
}

bool
SetStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    //auto result =         ( structure->GetStructureType() == Point ) |
    //                      ( structure->GetStructureType() == Vector );
    return true;
}
