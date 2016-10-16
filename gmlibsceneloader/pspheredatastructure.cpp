#include "pspheredatastructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "pspherestructure.h"

// stl
#include "iostream"

PSphereDataStructure::PSphereDataStructure()
    : PSphereStructure( int( GMStructTypes::PSphereData ) )
{
    std::cout << "Constructing a PSphereData object" << std::endl;
}

bool
PSphereDataStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    auto result =   (structure->GetStructureType() == int( GMStructTypes::Set)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetColor)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetCollapsed)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetLighted)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetVisible)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetMaterial));

    return result;
}
