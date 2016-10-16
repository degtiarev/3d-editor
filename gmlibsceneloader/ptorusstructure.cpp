#include "ptorusstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "psurfstructure.h"

// stl
#include "iostream"

PTorusStructure::PTorusStructure()
    : PSurfStructure( int( GMStructTypes::PTorus ) )
{
    std::cout << "Constructing a PTorus object" << std::endl;
}

bool
PTorusStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    // Either a different scene object or a SceneObjectData object
    auto sceneObjects = PSurfStructure::ValidateSubstructure( dataDescription, structure );

    auto constructors = structure->GetStructureType() == int( GMStructTypes::PTorusData );
    auto result = sceneObjects | constructors;

    return result;
}

