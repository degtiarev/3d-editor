#include "pbeziersurfdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "sceneobjectstructure.h"

// stl
#include "iostream"

PBezierSurfDataStructure::PBezierSurfDataStructure()
    : SceneObjectStructure( int( GMStructTypes::PBezierSurfData ) )
{
    std::cout << "Constructing a PBezierSurfData object" << std::endl;
}

bool
PBezierSurfDataStructure::ValidateSubstructure(
        const ODDL::DataDescription *dataDescription,
        const ODDL::Structure *structure) const {

    bool status = false;

    status |= ( structure->GetStructureType() == int(GMStructTypes::PBezierSurfData) ) ? true : false; //bit AND with assignment

    status |= ODDL::Structure::ValidateSubstructure( dataDescription, structure) ? true : false;
    return status;

}
