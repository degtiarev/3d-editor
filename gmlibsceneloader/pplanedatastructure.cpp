#include "pplanedatastructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectstructure.h"

// stl
#include "iostream"

PPlaneDataStructure::PPlaneDataStructure()
    : SceneObjectStructure( int( GMStructTypes::PPlaneData ) )
{
    std::cout << "Constructing a PPlaneData object" << std::endl;
}

bool
PPlaneDataStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    bool status = false;

    status |= ( structure->GetStructureType() == int(GMStructTypes::PPlaneData) ) ? true : false;

    status |= ODDL::Structure::ValidateSubstructure( dataDescription, structure) ? true : false;
    return status;
}
