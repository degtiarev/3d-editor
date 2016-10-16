#include "psurfdatastructure.h"

#include "gmlibsceneloaderdatadescription.h"
#include "psurfstructure.h"

// stl
#include "iostream"

PSurfDataStructure::PSurfDataStructure()
    : PSurfStructure( int(GMStructTypes::PSurfData ) )
{
    std::cout << "Constructing a PSurfData object" << std::endl;
}

bool
PSurfDataStructure::ValidateSubstructure( const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    // Have to make replot - and enableDefaultVisualizer structure

    //auto enableDefaultVisualizer

    //auto result = replot | enableDefaultVisualizer
    //return result;

    auto result =   ( structure->GetStructureType() == int( GMStructTypes::Replot ) ) |
            ( structure->GetStructureType() == int( GMStructTypes::EnableDefaultVisualizer ) );

    return result;
}
