#include "setcolorstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectdatastructure.h"

// stl
#include "iostream"

SetColorStructure::SetColorStructure()
    : SceneObjectDataStructure( int( GMStructTypes::SetColor ) )
{
    std::cout << "Constructing a setColor object" << std::endl;
}

bool
SetColorStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    auto result = ( structure->GetStructureType() == int( GMStructTypes::Color ) );
    return result;
}
