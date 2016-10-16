#include "pcylinderstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "psurfstructure.h"

// stl
#include "iostream"

PCylinderStructure::PCylinderStructure()
    : PSurfStructure( int( GMStructTypes::PCylinder))
{

    std::cout << "Constructing a PCylinder object" << std::endl;

}

bool
PCylinderStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    // Either a different scene object or a SceneObjectData object
    auto sceneObjects = PSurfStructure::ValidateSubstructure( dataDescription, structure );

    auto constructors = structure->GetStructureType() == int( GMStructTypes::PCylinderData );
    auto result = sceneObjects | constructors;

    return result;
}
