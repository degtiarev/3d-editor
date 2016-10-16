#include "psurfstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include "iostream"

PSurfStructure::PSurfStructure()
    : SceneObjectStructure( int( GMStructTypes::PSurfObject ) )
{

}

bool
PSurfStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    auto sceneObjects = SceneObjectStructure::ValidateSubstructure( dataDescription, structure );

    auto objectData = structure->GetStructureType() == int( GMStructTypes::PSurfData );

    auto result = sceneObjects | objectData;
    return result;
}
