#include "sceneobjectdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectstructure.h"

// stl
#include "iostream"

SceneObjectDataStructure::SceneObjectDataStructure()
    : SceneObjectStructure( int( GMStructTypes::SceneObjectData ) )
{
    std::cout << "Constructing a SceneObjectData object" << std::endl;
}

bool
SceneObjectDataStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    bool status = false;
    bool isStructure = ODDL::Structure::ValidateSubstructure( dataDescription, structure ) ? true : false;

    bool correctSubType = false;
    if( structure->GetStructureType() == int( GMStructTypes::Set ) )
    {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::SetCollapsed ) )
    {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::SetColor ) )
    {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::SetLighted ) )    // Make Struct
    {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::SetVisible ) )    // Make Struct
    {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::SetMaterial ) )
    {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::SetPosition ) ) {
        correctSubType = true;
    }
    else correctSubType = false;


    status = correctSubType & isStructure;

    return status;
}
