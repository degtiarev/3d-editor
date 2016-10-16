#include "setvisiblestructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "../openddl/openddl.h"

// stl
#include "iostream"

SetVisibleStructure::SetVisibleStructure()
    : ODDL::Structure (int ( GMStructTypes::SetVisible ) )
{
    std::cout << "Constructing a SetVisibleStructure object" << std::endl;
}

bool
SetVisibleStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    return (structure->GetStructureType() == ODDL::kDataBool);
}
