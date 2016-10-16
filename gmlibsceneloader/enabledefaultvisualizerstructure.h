#ifndef ENABLEDEFAULTVISUALIZERSTRUCTURE_H
#define ENABLEDEFAULTVISUALIZERSTRUCTURE_H

#include "../openddl/openddl.h"


class EnableDefaultVisualizerStructure : public ODDL::Structure
{
public:
    EnableDefaultVisualizerStructure();
    ~EnableDefaultVisualizerStructure() = default;

    bool ValidateSubstructure(const ODDL::DataDescription *dataDescribtion, const Structure *structure) const override;
};

#endif // ENABLEDEFAULTVISUALIZERSTRUCTURE_H
