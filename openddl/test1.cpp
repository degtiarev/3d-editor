#include "openddl.h"


// stl
#include <fstream>
#include <iostream>
#include <vector>










using namespace ODDL;


/*
  This is the simplest example of what needs to be done in order to read an
  OpenDDL file that follows a specific format. In this example, a single type
  of structure is recognized, and its identifier in an OpenDDL file is "Example".
*/


enum
{
  kStructureExample  = ODDL::mc_cast('E','X','P','L')    // The 32-bit type of the "Example" structure.
};


/*
  The following class represents each "Example" structure in the file.
*/

class ExampleStructure : public Structure
{
  public:

    ExampleStructure();
    ~ExampleStructure();

    bool ValidateSubstructure(const DataDescription *dataDescription, const Structure *structure) const override;
};


/*
  The following class represents the entire OpenDDL file.
*/

class ExampleDataDescription : public DataDescription
{
  public:

    ExampleDataDescription();
    ~ExampleDataDescription();

    Structure *CreateStructure(const String& identifier) const override;
};













ExampleStructure::ExampleStructure() : Structure(kStructureExample)
{
  // An instance of the ExampleStructure class is constructed for each
  // occurrence of the "Example" structure in the OpenDDL file.
  std::cout << "Constructing an ExampleStructure!" << std::endl;
}

ExampleStructure::~ExampleStructure()
{
}

bool ExampleStructure::ValidateSubstructure(const DataDescription *dataDescription, const Structure *structure) const
{
  // In this example, we only allow the "float" data structure to be
  // contained inside an "Example" structure.

  return (structure->GetStructureType() == kDataFloat);
}


ExampleDataDescription::ExampleDataDescription()
{
}

ExampleDataDescription::~ExampleDataDescription()
{
}

Structure *ExampleDataDescription::CreateStructure(const String& identifier) const
{
  // This function is called for each structure identifier encountered
  // in an OpenDDL file. In this example, we only recognize the identifier
  // "Example", and if matched, we return a new instance of ExampleStructure.

  if (identifier == "Example")
  {
    return (new ExampleStructure);
  }

  return (nullptr);
}



























int main( int /*argc*/, char** /*argv*/ ) try {

  ExampleDataDescription edd;

  const auto& in_file = std::string("example.oddl");
  auto is = std::ifstream(in_file, std::ifstream::in);
  if(!is.is_open()) {
    std::cerr << "Error opening <" << in_file << ">!" << std::endl;
    return 1;
  }


  is.seekg( 0, std::ios_base::end );
  auto buff_length = is.tellg();
  is.seekg( 0, std::ios_base::beg );


  std::vector<char> buffer(buff_length);
  is.read(buffer.data(),buff_length);



  DataResult result = edd.ProcessText(buffer.data());
  if (result == kDataOkay) {

    auto structure = edd.GetRootStructure()->GetFirstSubnode();
    while (structure) {

      // This loops over all top-level structures in the file.

      // Do something with the data...

      structure = structure->Next();
    }
  }



  return 0;
}
catch(...) {
  std::cerr << "Something went horribly wrong -- exception caught!" << std::endl;
}
