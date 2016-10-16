#ifndef COLOR_H
#define COLOR_H

#include "../openddl/openddl.h"

class ColorStructure : public ODDL::Structure
{
public:
    ColorStructure();
    ~ColorStructure() = default;

    bool ValidateSubstructure(const ODDL::DataDescription *dataDescribtion, const Structure *structure) const override;
};

#endif // COLOR_H
