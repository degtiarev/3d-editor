#include "setmaterialstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectdatastructure.h"

// stl
#include "iostream"

SetMaterialStructure::SetMaterialStructure()
    : SceneObjectDataStructure( int( GMStructTypes::SetMaterial ) )
{
    std::cout << "Constructing a setMaterial object" << std::endl;
}

bool
SetMaterialStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    auto result = ( structure->GetStructureType() == int( GMStructTypes::Material ) );
    return result;
}
