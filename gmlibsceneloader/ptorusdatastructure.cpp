#include "ptorusdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "ptorusstructure.h"

// stl
#include "iostream"

PTorusDataStructure::PTorusDataStructure()
    : PTorusStructure( int( GMStructTypes::PTorusData ) )
{
    std::cout << "Constructing a PTorusData object" << std::endl;
}

bool
PTorusDataStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    auto result =   (structure->GetStructureType() == int( GMStructTypes::Set)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetColor)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetCollapsed)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetLighted)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetVisible)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetMaterial));

    return result;
}
