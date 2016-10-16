#ifndef REPLOTSTRUCTURE_H
#define REPLOTSTRUCTURE_H

#include "psurfdatastructure.h"

class ReplotStructure : public PSurfDataStructure
{
public:
    ReplotStructure();
    ~ReplotStructure() = default;

    bool    ValidateSubstructure( const ODDL::DataDescription *dataDescription, const Structure *structure ) const override;
};

#endif // REPLOTSTRUCTURE_H
