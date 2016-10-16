#ifndef GMLIBSCENELOADERDATADESCRIPTION_H
#define GMLIBSCENELOADERDATADESCRIPTION_H


#include "../openddl/openddl.h"

enum class GMStructTypes {
    SceneObject             =   ODDL::mc_cast('S', 'C', 'O', 'J'),
    SceneObjectData         =   ODDL::mc_cast('S', 'C', 'O', 'D'),
    GMlibVersion            =   ODDL::mc_cast('G', 'M', 'V', 'N'),
    PSurfObject             =   ODDL::mc_cast('P', 'S', 'F', 'O'),
    PSurfData               =   ODDL::mc_cast('P', 'S', 'D', 'A'),
    PTorus                  =   ODDL::mc_cast('P', 'T', 'R', 'S'),
    PTorusData              =   ODDL::mc_cast('P', 'T', 'D', 'T'),
    PCylinder               =   ODDL::mc_cast('P', 'C', 'L', 'D'),
    PCylinderData           =   ODDL::mc_cast('P', 'C', 'D', 'T'),
    PPlane                  =   ODDL::mc_cast('P', 'P', 'L', 'N'),
    PPlaneData              =   ODDL::mc_cast('P', 'P', 'D', 'T'),
    PSphere                 =   ODDL::mc_cast('P', 'S', 'P', 'H'),
    PSphereData             =   ODDL::mc_cast('P', 'S', 'D', 'T'),
    PBezierSurf             =   ODDL::mc_cast('P', 'B', 'Z', 'S'),
    PBezierSurfData         =   ODDL::mc_cast('P', 'B', 'D', 'T'),
    Set                     =   ODDL::mc_cast('S', 'E', 'T', 'X'),
    SetColor                =   ODDL::mc_cast('S', 'T', 'C', 'L'),
    Color                   =   ODDL::mc_cast('C', 'O', 'L', 'R'),
    SetMaterial             =   ODDL::mc_cast('S', 'T', 'M', 'T'),
    SetPosition             =   ODDL::mc_cast('S', 'T', 'P', 'S'),
    SetCollapsed            =   ODDL::mc_cast('S', 'T', 'C', 'S'),
    SetLighted              =   ODDL::mc_cast('S', 'T', 'L', 'G'),
    SetVisible              =   ODDL::mc_cast('S', 'T', 'V', 'B'),
    Material                =   ODDL::mc_cast('M', 'A', 'T', 'L'),
    Replot                  =   ODDL::mc_cast('R', 'E', 'P', 'T'),
    EnableDefaultVisualizer =   ODDL::mc_cast('E', 'D', 'V', 'I')
};




class GMlibSceneLoaderDataDescription : public ODDL::DataDescription
{
public:
    //GMlibSceneLoaderDataDescription() {}
    //~GMlibSceneLoaderDataDescription() {}

    using DataDescription::DataDescription;

    ODDL::Structure* CreateStructure(const ODDL::String &identifier) const override;
};

#endif // GMLIBSCENELOADERDATADESCRIPTION_H
