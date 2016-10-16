#include "setlightedstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "../openddl/openddl.h"

// stl
#include "iostream"


SetLightedStructure::SetLightedStructure()
    : ODDL::Structure (int ( GMStructTypes::SetLighted ) )
{
    std::cout << "Constructing a SetLightedStructure object" << std::endl;
}

bool
SetLightedStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    return (structure->GetStructureType() == ODDL::kDataBool);
}
