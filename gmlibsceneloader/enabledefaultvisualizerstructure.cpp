#include "enabledefaultvisualizerstructure.h"

#include "gmlibsceneloaderdatadescription.h"

// stl
#include "iostream"


EnableDefaultVisualizerStructure::EnableDefaultVisualizerStructure()
    : ODDL::Structure( int( GMStructTypes::EnableDefaultVisualizer))
{
    std::cout << "Constructing a EnableDefaultVisualizerStructure object" << std::endl;

}

bool
EnableDefaultVisualizerStructure::ValidateSubstructure(const ODDL::DataDescription *dataDescription, const ODDL::Structure *structure) const
{
    return (structure->GetStructureType() == ODDL::kDataBool);
}
