#include "materialstructure.h"

#include "setcolorstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "setmaterialstructure.h"
#include "../openddl/openddl.h"

// stl
#include "iostream"

MaterialStructure::MaterialStructure()
    : SetMaterialStructure( int( GMStructTypes::Material ) )
{
    std::cout << "Constructing a Material object" << std::endl;
}

bool
MaterialStructure::ValidateSubstructure(const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    auto result = ( structure->GetStructureType() == int( GMStructTypes::Color ) ) |
                  ( structure->GetStructureType() == ODDL::kDataDouble );
    return result;
}
