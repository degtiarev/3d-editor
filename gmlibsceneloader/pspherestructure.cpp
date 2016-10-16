#include "pspherestructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "psurfstructure.h"

// stl
#include "iostream"

PSphereStructure::PSphereStructure()
    : PSurfStructure( int( GMStructTypes::PSphere ) )
{
    std::cout << "Constructing a PSphere object" << std::endl;
}

bool
PSphereStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    // Either a different scene object or a SceneObjectData object
    auto sceneObjects = PSurfStructure::ValidateSubstructure( dataDescription, structure );

    auto constructors = structure->GetStructureType() == int( GMStructTypes::PSphereData );
    auto result = sceneObjects | constructors;

    return result;
}

