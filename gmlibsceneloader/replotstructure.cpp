#include "replotstructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "psurfdatastructure.h"
#include "../openddl/openddl.h"

// stl
#include "iostream"

ReplotStructure::ReplotStructure()
    : PSurfDataStructure( int( GMStructTypes::Replot ) )
{
    std::cout << "Constructing a replot object" << std::endl;
}

bool
ReplotStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    auto result = ( structure->GetStructureType() == ODDL::kDataInt32 );
    return result;
}
