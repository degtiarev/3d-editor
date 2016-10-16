#include "colorstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include "iostream"

ColorStructure::ColorStructure()
    : ODDL::Structure( int( GMStructTypes::Color ) )
{
    std::cout << "Constructing a Color object" << std::endl;
}

bool
ColorStructure::ValidateSubstructure(const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    return ( structure->GetStructureType() == ODDL::kDataDouble );
}
