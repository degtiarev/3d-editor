#include "propertystructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "../openddl/openddl.h"

// stl
#include "iostream"

PropertyStructure::PropertyStructure()
    : ODDL::Structure( int( GMStructTypes::Property ) )
{
    std::cout << "Constructing a Property object" << std::endl;
}

bool
PropertyStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure ) const
{
    auto result =   (structure->GetStructureType() == ODDL::kDataInt32) |
                    (structure->GetStructureType() == ODDL::kDataBool) |
                    (structure->GetStructureType() == ODDL::kDataFloat) |
                    (structure->GetStructureType() == ODDL::kDataDouble);
    return result;
}
