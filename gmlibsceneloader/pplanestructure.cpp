#include "pplanestructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "psurfstructure.h"

// stl
#include "iostream"

PPlaneStructure::PPlaneStructure()
    : PSurfStructure( int( GMStructTypes::PPlane ) )
{
    std::cout << "Constructing a PPlane object" << std::endl;
}

bool
PPlaneStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    // Either a different scene object or a SceneObjectData object
    auto sceneObjects = PSurfStructure::ValidateSubstructure( dataDescription, structure );

    auto constructors = structure->GetStructureType() == int( GMStructTypes::PPlaneData );
    auto result = sceneObjects | constructors;

    return result;
}
