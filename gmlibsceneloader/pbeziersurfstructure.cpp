#include "pbeziersurfstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "psurfstructure.h"

// stl
#include "iostream"

PBezierSurfStructure::PBezierSurfStructure()
    : PSurfStructure( int( GMStructTypes::PBezierSurf ) )
{
    std::cout << "Constructing a PBezierSurf object" << std::endl;
}

bool
PBezierSurfStructure::ValidateSubstructure(
        const ODDL::DataDescription *dataDescription,
        const ODDL::Structure *structure) const {

    // Either a different scene object or a SceneObjectData object
    auto sceneObjects = PSurfStructure::ValidateSubstructure( dataDescription, structure );

    auto constructors = structure->GetStructureType() == int( GMStructTypes::PBezierSurfData );
    auto result = sceneObjects | constructors;

    return result;

}
