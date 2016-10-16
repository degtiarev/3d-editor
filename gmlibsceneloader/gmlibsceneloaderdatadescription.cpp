#include "gmlibsceneloaderdatadescription.h"

#include "gmlibversionstructure.h"

#include "sceneobjectstructure.h"
#include "sceneobjectdatastructure.h"

#include "psurfstructure.h"
#include "psurfdatastructure.h"

#include "ptorusstructure.h"
#include "ptorusdatastructure.h"

#include "pspherestructure.h"
#include "pspheredatastructure.h"

#include "pplanestructure.h"
#include "pplanedatastructure.h"

#include "pcylinderstructure.h"
#include "pcylinderdatastructure.h"

#include "pbeziersurfstructure.h"
#include "pbeziersurfdatastructure.h"


#include "colorstructure.h"
#include "setcolorstructure.h"

#include "materialstructure.h"
#include "setmaterialstructure.h"

#include "enabledefaultvisualizerstructure.h"
#include "replotstructure.h"
#include "setstructure.h"
#include "setpositionstructure.h"
#include "setlightedstructure.h"
#include "setvisiblestructure.h"
#include "setcollapsedstructure.h"

//#include "propertystructure.h"


ODDL::Structure *GMlibSceneLoaderDataDescription::CreateStructure(
        const ODDL::String &identifier) const {

    if(identifier == "GMlibVersion")
    {
        return new GMlibVersionStructure;
    }

    else if( identifier == "PTorus" )
    {
        return new PTorusStructure;
    }
    else if( identifier == "PTorusData" )
    {
        return new PTorusDataStructure;
    }
    else if( identifier == "PCylinder" )
    {
        return new PCylinderStructure;
    }
    else if( identifier == "PCylinderData" )
    {
        return new PCylinderDataStructure;
    }
    else if( identifier == "PPlane" )
    {
        return new PPlaneStructure;
    }
    else if( identifier == "PPlaneData" )
    {
        return new PPlaneDataStructure;
    }
    else if( identifier == "PSphere" )
    {
        return new PSphereStructure;
    }
    else if( identifier == "PSphereData" )
    {
        return new PSphereDataStructure;
    }
    else if( identifier == "PBezierSurf" )
    {
        return new PBezierSurfStructure;
    }
    else if( identifier == "PBezierSurfData" )
    {
        return new PBezierSurfDataStructure;
    }
    else if( identifier == "SceneObjectData" )
    {
        return new SceneObjectDataStructure;
    }
    else if( identifier == "set" )
    {
        return new SetStructure;
    }
    else if( identifier == "setColor" )
    {
        return new SetColorStructure;
    }
    else if( identifier == "setMaterial" )
    {
        return new SetMaterialStructure;
    }
    else if( identifier == "Material" )
    {
        return new MaterialStructure;
    }
    else if( identifier == "PSurfData" )
    {
        return new PSurfDataStructure;
    }
    else if( identifier == "replot" )
    {
        return new ReplotStructure;
    }
    else if( identifier == "SetCollapsed" )
    {
        return new SetCollapsedStructure;
    }
    else if( identifier == "Color" )
    {
        return new ColorStructure;
    }
    else if( identifier == "replot" )
    {
        return new ReplotStructure;
    }
    else if( identifier == "enableDefaultVisualizer" )
    {
        return new EnableDefaultVisualizerStructure;
    }
    else if( identifier == "setLighted" )
    {
        return new SetLightedStructure;
    }
    else if( identifier == "setVisible" )
    {
        return new SetVisibleStructure;
    }
    else if( identifier == "setPosition" )
    {
        return new SetPositionStructure;
    }

    return nullptr;
}
