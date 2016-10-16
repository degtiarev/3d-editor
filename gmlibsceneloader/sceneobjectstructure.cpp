#include "sceneobjectstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// Stl
#include "iostream"

SceneObjectStructure::SceneObjectStructure()
    : ODDL::Structure( int( GMStructTypes::SceneObject ) )
{


}

bool
SceneObjectStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    bool status = false;
    bool isStructure = ODDL::Structure::ValidateSubstructure( dataDescription, structure ) ? true : false;
    bool correctSubType = false;

    if( structure->GetStructureType() == int( GMStructTypes::PTorus ) ) {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::PSphere ) ) {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::PPlane ) ) {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::PBezierSurf ) ) {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::PCylinder ) ) {
        correctSubType = true;
    }
    else if( structure->GetStructureType() == int( GMStructTypes::SceneObjectData))
    {
        correctSubType = true;
    }
    else correctSubType = false;

    status = correctSubType & isStructure;
    return status;
}

