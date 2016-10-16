#include "pcylinderdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "pcylinderstructure.h"

// stl
#include "iostream"

PCylinderDataStructure::PCylinderDataStructure()
    : PCylinderStructure( int( GMStructTypes::PCylinderData ) )
{
    std::cout << "Constructing a PCylinderData object" << std::endl;
}

bool
PCylinderDataStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    auto result =   (structure->GetStructureType() == int( GMStructTypes::Set)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetColor)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetCollapsed)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetLighted)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetVisible)) |
                    (structure->GetStructureType() == int( GMStructTypes::SetMaterial));

    return result;
}
