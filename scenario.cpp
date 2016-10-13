#include "scenario.h"
#include "testtorus.h"

#include "gmlibsceneloader/gmlibsceneloaderdatadescription.h"


// openddl
#include "openddl/openddl.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QTimerEvent>
#include <QDebug>

// stl
#include <cassert>
#include <iostream>
#include <iomanip>


//class SimStateLock {
//public:
//  SimStateLock( Scenario& scenario ) : _scenario{scenario} {

//    _state = _scenario.isSimulationRunning();
//  }

//  ~SimStateLock() {

//    if(_state) _scenario.startSimulation();
//    else       _scenario.stopSimulation();
//  }

//  Scenario&   _scenario;
//  bool        _state;
//};



Scenario::Scenario() : QObject(), _timer_id{0}/*, _select_renderer{nullptr}*/ {

    if(_instance != nullptr) {

        std::cerr << "This version of the Scenario only supports a single instance of the GMlibWraper..." << std::endl;
        std::cerr << "Only one of me(0x" << this << ") please!! ^^" << std::endl;
        assert(!_instance);
        exit(666);
    }

    _instance = std::unique_ptr<Scenario>(this);
}

Scenario::~Scenario() {

    _instance.release();
}

void Scenario::deinitialize() {

    stopSimulation();

    _scene->remove(_testtorus.get());
    _testtorus.reset();

    _scene->removeLight(_light.get());
    _light.reset();

    _renderer->releaseCamera();
    _scene->removeCamera(_camera.get());

    _renderer.reset();
    _camera.reset();

    _scene->clear();
    _scene.reset();

    // Clean up GMlib GL backend
    GMlib::GL::OpenGLManager::cleanUp();
}

void Scenario::initialize() {

    // Setup and initialized GMlib GL backend
    GMlib::GL::OpenGLManager::init();

    // Setup and init the GMlib GMWindow
    _scene = std::make_shared<GMlib::Scene>();
}

void Scenario::initializeScenario() {

    // Insert a light
    auto init_light_pos = GMlib::Point<GLfloat,3>( 2.0, 4.0, 10 );
    _light = std::make_shared<GMlib::PointLight>( GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                  GMlib::GMcolor::White, init_light_pos );
    _light->setAttenuation(0.8, 0.002, 0.0008);
    _scene->insertLight( _light.get(), false );

    // Insert Sun
    _scene->insertSun();

    // Default camera parameters
    auto init_viewport_size = 600;
    auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, 0.0f, 0.0f );
    auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f );
    auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );

    // Projection cam
    _renderer = std::make_shared<GMlib::DefaultRenderer>();
    _camera = std::make_shared<GMlib::Camera>();
    _renderer->setCamera(_camera.get());

    // **************************************************************
    //select renderer test
    _select_renderer = std::make_shared<GMlib::DefaultSelectRenderer>();
    // **************************************************************

    _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    _camera->setCuttingPlanes( 1.0f, 8000.0f );
    _camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
    _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
    _camera->enableCulling(false);
    _scene->insertCamera( _camera.get() );
    _renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Surfaces
    _testtorus = std::make_shared<TestTorus>();
    _testtorus->toggleDefaultVisualizer();
    _testtorus->replot(200,200,1,1);
    _testtorus->setMaterial(GMlib::GMmaterial::Pewter);
    _scene->insert(_testtorus.get());

    _testtorus->test01();


    auto cylinder=new GMlib::PCylinder<float>(2,2,15);
    cylinder->toggleDefaultVisualizer();
    cylinder->replot(100,100,20,20);
    cylinder->set(GMlib::Point<float,3>(0,12,0), GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ),
                  GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));
    cylinder->setMaterial(GMlib::GMmaterial::Bronze);
    _scene->insert(cylinder);



    auto sphere=new GMlib::PSphere<float>(2);
    sphere->setMaterial(GMlib::GMmaterial::PolishedRed);
    sphere->setLighted(false);
    sphere->toggleDefaultVisualizer();
    sphere->replot(50,50,10,10);
    _scene->insert(sphere);


    auto plane=new GMlib::PPlane<float> (GMlib::Point<float,3>(-5,0,0),
                                         GMlib::Vector<float,3>(10,0,0), GMlib::Vector<float,3>(0,20,0));
    plane->setMaterial(GMlib::GMmaterial::Snow);
    plane->setLighted(false);
    plane->toggleDefaultVisualizer();
    plane->replot(50,50,1,1);
    _scene->insert(plane);

}

std::unique_ptr<Scenario> Scenario::_instance {nullptr};

Scenario& Scenario::instance() { return *_instance; }

void Scenario::prepare() { _scene->prepare(); }

void Scenario::render( const QRect& viewport_in, GMlib::RenderTarget& target ) {

    // Update viewport
    if(_viewport != viewport_in) {

        _viewport = viewport_in;

        const auto& size = _viewport.size();
        _renderer->reshape( GMlib::Vector<int,2>(size.width(),size.height()));
        _camera->reshape( 0, 0, size.width(), size.height() );
    }

    // Render and swap buffers
    _renderer->render(target);
}

void Scenario::startSimulation() {

    if( _timer_id || _scene->isRunning() )
        return;

    _timer_id = startTimer(16, Qt::PreciseTimer);
    _scene->start();
}

void Scenario::stopSimulation() {

    if( !_timer_id || !_scene->isRunning() )
        return;

    _scene->stop();
    killTimer(_timer_id);
    _timer_id = 0;
}

void Scenario::timerEvent(QTimerEvent* e) {

    e->accept();

    _scene->simulate();
    prepare();
}

void Scenario::toggleSimulation() { _scene->toggleRun(); }

void Scenario::replotTesttorus()
{
    _testtorus->replot(4,4,1,1);\
}

// **************************************************************


GMlib::Point<int, 2> Scenario::fromQtToGMlibViewPoint( const QPoint& pos) {

    int h =_camera->getViewportH();// cam.getViewportH(); // Height of the camera’s viewport

    // QPoint
    int q1 = pos.x();
    int q2 = pos.y();
    // GMlib Point
    int p1 = q1;
    int p2 = h - q2 - 1;

    return GMlib::Point<int, 2> (p1, p2);
}


void Scenario::camFly(char direction)
{
    GMlib::Vector<float,3> dS;

    if (direction=='U') dS = GMlib::Vector<float,3>(0,0,0.1);
    if (direction=='D') dS = GMlib::Vector<float,3>(0,0,-0.1);
    if (direction=='R') dS = GMlib::Vector<float,3>(0.1,0,0);
    if (direction=='L') dS = GMlib::Vector<float,3>(-0.1,0,0);

    auto dA = GMlib::Angle(0);
    auto axis = GMlib::Vector<float,3>(0,0,1);
    _camera->translateGlobal(dS);
    _camera->rotateGlobal(dA,axis);
}


//Zoom
void Scenario::zoomCameraW(const float &zoom_var){
    _camera->zoom(zoom_var);
}


//Move Camera
void Scenario::moveCamera(const QPoint &begin_pos, const QPoint &end_pos) {

    auto curentPos       = fromQtToGMlibViewPoint( begin_pos);
    auto previousPos     = fromQtToGMlibViewPoint( end_pos);

    const float scale = _scene->getSphere().getRadius();

    GMlib::Vector<float,2> delta (
                -(curentPos(0) - previousPos(0))*scale / _camera->getViewportW(),
                (curentPos(1) - previousPos(1))*scale / _camera->getViewportH()
                );

    _camera->move( delta );
}

//Move pan
void Scenario::movePan(const int &_delta, const char direction)
{
    const float scale = _scene->getSphere().getRadius();
    auto delta = _delta/5;
    GMlib::Vector<float,2> delta_vec;

    if (direction=='W')
        delta_vec = GMlib::Vector<float,2>(0.0f, delta * scale / _camera->getViewportW());
    else delta_vec = GMlib::Vector<float,2>(delta * scale / _camera->getViewportH(),0.0f);

    _camera->move(delta_vec);
}

GMlib::SceneObject* Scenario::findSceneObject(QPoint &pos)
{
    GMlib::SceneObject *selected_obj = nullptr;

    _select_renderer->setCamera(_camera.get());
    const GMlib::Vector<int,2> size(_camera->getViewportW(),
                                    _camera->getViewportH());

    _select_renderer->reshape(size);
    _select_renderer->prepare();
    //select code
    GMlib::Point <int,2> qp = fromQtToGMlibViewPoint(pos);

    _select_renderer->select(GMlib::GM_SO_TYPE_SELECTOR);

    selected_obj=_select_renderer->findObject(qp(0),qp(1));
    if(!selected_obj) {

        _select_renderer->select(-GMlib::GM_SO_TYPE_SELECTOR );
        selected_obj = _select_renderer->findObject(qp(0),qp(1));
    }

    _select_renderer->releaseCamera();

    return selected_obj;
}

//Select object
void Scenario::tryToSelectObject(QPoint &pos){

    GMlib::SceneObject *selected_obj = findSceneObject (pos);
    if( !selected_obj ) return;

    auto selected = selected_obj->isSelected(); //bool

    _scene->removeSelections(); //for selecting only 1 object at a time
    selected_obj->setSelected( !selected );

    _selectedObjVar = selected_obj;

    // qDebug()<<selected_obj->getPos()(0) << selected_obj->getPos()(1);
}

void Scenario::tryToDeselectObject(QPoint &pos)
{
    GMlib::SceneObject *selected_obj = findSceneObject (pos);

    if (selected_obj && selected_obj->isSelected()){
        _selectedObjVar->setSelected(false);}
}


void Scenario::tryToLockOnObject(QPoint &pos)
{
    GMlib::SceneObject *selected_obj = findSceneObject (pos);
    if(!selected_obj->isLocked()){_camera->lock(selected_obj);}
}



//unlock camera, return camera position to default
void Scenario::unlockObjs()
{    auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, 0.0f, 0.0f );
     auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f );
      auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );

       if(_camera->isLocked()){
           _camera->unLock();
           _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
           _camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
           _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
       }
}


void Scenario::scaleObjects(int &delta)
{
    const GMlib::Array<GMlib::SceneObject*> &sel_objs = _scene->getSelectedObjects();
    const float plus_val=1.02;
    const float minus_val=0.98;
    for( int i = 0; i < sel_objs.getSize(); i++ ) {
        GMlib::SceneObject* obj = sel_objs(i);
        if(delta>0){
            obj->scale( GMlib::Vector<float,3>( 0.1f + plus_val) );
        }
        else{obj->scale( GMlib::Vector<float,3>( 0.1f - minus_val) );}
    }
}

void Scenario::rotateObj(QPoint &pos, QPoint &prev)
{
    auto r_pos = fromQtToGMlibViewPoint(pos);
    auto r_prev = fromQtToGMlibViewPoint(prev);

    auto rot_X_pos_dif = float(r_pos(0)-r_prev(0));
    auto rot_Y_pos_dif = float(r_pos(1)-r_prev(1));

    GMlib::Vector<float,3> rot(rot_X_pos_dif,rot_Y_pos_dif,0.0f);
    rot=rot*0.001;

    GMlib::Angle ang(M_2PI * sqrt(
                         pow( double( rot_X_pos_dif) / _camera->getViewportW(), 2 ) +
                         pow( double( rot_Y_pos_dif) / _camera->getViewportH(), 2 ) )
                     );

    if (_selectedObjVar)
        _selectedObjVar->rotateGlobal(ang,rot);
}

void Scenario::switchCamera(int n)
{
    //auto init_viewport_size = 600;
    auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, 0.0f, 0.0f );
    auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f );
    auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );
    switch (n)
    {
    case 1:
        _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
        _camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
        _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
        qDebug() << "Projection cam";
        break;
    case 2:
        _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
        _camera->rotateGlobal( GMlib::Angle(0), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
        _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 0.0f ) );
        qDebug() << "Front cam";
        break;
    case 3:
        _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
        _camera->rotateGlobal( GMlib::Angle(90), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
        _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 0.0f ) );
        qDebug() << "Side cam";
        break;
    case 4:
        _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
        _camera->rotateGlobal( GMlib::Angle(-90), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
        _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, 0.0f, 20.0f ) );
        qDebug() << "Top cam";
        break;
    }
    // _renderer->render();


}

void Scenario::selectChildrenObjects(GMlib::SceneObject *object)
{
    GMlib::Camera *cam   = dynamic_cast<GMlib::Camera*>( object );
    GMlib::Light  *light = dynamic_cast<GMlib::Light*>( object );
    if( !cam && !light ) {
        object->setSelected(true);

        for( int i = 0; i < object->getChildren().getSize(); i++ )
        {
            selectChildrenObjects((object->getChildren())[i] );
        }
    }
}



void Scenario::toggleSelectAll()
{
    qDebug()<<"Toogle select"<<_scene->getSelectedObjects().getSize();

    if( _scene->getSelectedObjects().getSize() > 0 )
    {
        _scene->removeSelections();
    }
    else
    {
        _scene->removeSelections();

        GMlib::Scene *scene = _scene.get();
        for( int i = 0; i < scene->getSize(); ++i )
        {
            selectChildrenObjects((*scene)[i] );
        }
    }
}

void Scenario::moveObject(QPoint &pos, QPoint &prev)
{
    auto _pos = fromQtToGMlibViewPoint(pos);
    auto _prev = fromQtToGMlibViewPoint(prev);

    const float scale = _scene->getSphere().getRadius();
    auto tmp1 = -(_pos(0) - _prev(0))*scale / _camera->getViewportW();
    auto tmp2 = -(_pos(1) - _prev(1))*scale / _camera->getViewportH();
    GMlib::Vector<float,3> delta (tmp1,tmp2,0);

    const GMlib::Array<GMlib::SceneObject*> &sel_objs = _scene->getSelectedObjects();
    for( int i = 0; i < sel_objs.getSize(); i++ ) {

        GMlib::SceneObject* obj = sel_objs(i);

        // qDebug()<<delta(0) << delta(1);
        obj->translateGlobal(delta,true);
    }

}

//change Color
void Scenario::changeColor(GMlib::SceneObject* obj)
{
    std::vector<GMlib::Material> colors=
    {GMlib::GMmaterial::BlackPlastic,GMlib::GMmaterial::BlackRubber,
     GMlib::GMmaterial::Brass,GMlib::GMmaterial::Bronze,
     GMlib::GMmaterial::Chrome,GMlib::GMmaterial::Copper,
     GMlib::GMmaterial::Emerald,GMlib::GMmaterial::Gold,
     GMlib::GMmaterial::Jade,GMlib::GMmaterial::Obsidian,
     GMlib::GMmaterial::Pearl,GMlib::GMmaterial::Pewter,
     GMlib::GMmaterial::Plastic,GMlib::GMmaterial::PolishedBronze,
     GMlib::GMmaterial::PolishedCopper,GMlib::GMmaterial::PolishedGold,
     GMlib::GMmaterial::PolishedGreen,GMlib::GMmaterial::PolishedRed,
     GMlib::GMmaterial::PolishedSilver, GMlib::GMmaterial::Ruby,
     GMlib::GMmaterial::Sapphire, GMlib::GMmaterial::Silver,
     GMlib::GMmaterial::Snow, GMlib::GMmaterial::Turquoise};


    const auto cj = obj->getMaterial();
    unsigned int color_num=0;
    for (unsigned int i=0;i<colors.size(); i++){
        if (cj == colors[i]){color_num = i;
            break;}
    }

    color_num++;
    if(color_num<colors.size()-1){
        obj->setMaterial(colors[color_num]);
        qDebug()<<color_num;}

    else obj->setMaterial(colors[0]);
}

#define Saving {

void Scenario::save() {

    qDebug() << "Saving scene...";
    stopSimulation(); {


        auto filename = std::string("gmlib_save.openddl");

        auto os = std::ofstream(filename,std::ios_base::out);
        if(!os.is_open()) {
            std::cerr << "Unable to open " << filename << " for saving..."
                      << std::endl;
            return;
        }


        os << "GMlibVersion { int { 0x"
           << std::setw(6) << std::setfill('0')
           << std::hex << GM_VERSION
           << " } }"
           << std::endl<<std::endl;


        auto &scene = *_scene;
        for( auto i = 0; i < scene.getSize(); ++i ) {

            const auto obj = scene[i];
            save(os,obj);

        }



    } startSimulation();
    qDebug() << "The scene was success saved";

}

void Scenario::save(std::ofstream &os, const GMlib::SceneObject *obj) {


    auto cam_obj = dynamic_cast<const GMlib::Camera*>(obj);
    if(cam_obj) return;


    os << obj->getIdentity() << std::endl
       << "{" << std::endl<<std::endl;

    saveSO(os,obj);

    auto torus = dynamic_cast<const GMlib::PTorus<float>*>(obj);
    if(torus)
        savePT(os,torus);

    auto sphere = dynamic_cast<const GMlib::PSphere<float>*>(obj);
    if(sphere)
        savePS(os,sphere);

    auto  cylinder = dynamic_cast<const GMlib::PCylinder<float>*>(obj);
    if(cylinder)
        savePC(os,cylinder);

    auto  plane = dynamic_cast<const GMlib::PPlane<float>*>(obj);
    if(plane)
        savePP(os,plane);


    const auto& children = obj->getChildren();
    for(auto i = 0; i < children.getSize(); ++i )
        save(os,children(i));

    os << "}"
       << std::endl<<std::endl;

}

void Scenario::saveSO(std::ofstream &os, const GMlib::SceneObject *obj) {

    using namespace std;
    os << "SceneObjectData" << endl
       << "{" << endl<<endl;


    os << "set"<<endl<<"{"<<endl<<"Point {"
       << " float[3] { " << obj->getPos()(0)<<", "<<obj->getPos()(1)<<", "<<obj->getPos()(2)<<" }"
       << " }"<<endl;
    os <<"Vector {"
      << " float[3] { " << obj->getDir()(0)<<", "<<obj->getDir()(1)<<", "<<obj->getDir()(2)<<" }"
      << " }"<<endl;
    os <<"Vector {"
      << " float[3] { " << obj->getUp()(0)<<", "<<obj->getUp()(1)<<", "<<obj->getUp()(2)<<" }"
      << " }"<<endl<<"}"<<endl<<endl;


    os << "setCollapsed{ bool {"
       << ( obj->isCollapsed()?"true":"false")
       << "} }"<<endl<<endl;
    os << "setLighted{ bool {"
       << ( obj->isLighted()?"true":"false")
       << "} }"<<endl<<endl;
    os << "setVisible{ bool {"
       << ( obj->isVisible()?"true":"false")
       << "} }"<<endl<<endl;


    os << "setColor"<<endl<<"{"<<endl<<"Color {"
       << " double[3] { " << obj->getColor().getRedC()<<", "<<obj->getColor().getGreenC()<<", "<<obj->getColor().getBlueC()<<" }"
       << " }"<<endl<<"}"<<endl<<endl;


    os << "setMaterial"<<endl<<"{"<<endl<<"Material"<<endl<<"{"<<endl<<"Color {"
       << " double[3] { " << obj->getMaterial().getAmb().getRedC()<<", "<<obj->getMaterial().getAmb().getGreenC()<<", "<<obj->getMaterial().getAmb().getBlueC()<<" }"
       << " }"<<endl;
    os <<"Color {"
      << " double[3] { " << obj->getMaterial().getDif().getRedC()<<", "<<obj->getMaterial().getDif().getGreenC()<<", "<<obj->getMaterial().getDif().getBlueC()<<" }"
      << " }"<<endl;
    os <<"Color {"
      << " double[3] { " << obj->getMaterial().getSpc().getRedC()<<", "<<obj->getMaterial().getSpc().getGreenC()<<", "<<obj->getMaterial().getSpc().getBlueC()<<" }"
      << " }"<<endl;
    os<< "float {" <<obj->getMaterial().getShininess()  << "}"<<endl
      << "}"<<endl<<"}"<<endl;
    os << "}" << endl<<endl;

}

void Scenario::savePT(std::ofstream &os, const GMlib::PTorus<float> *obj) {

    using namespace std;

    os << "PSurfData"<<endl<<"{"<<endl
       <<"enableDefaultVisualize { bool {" << ( obj->getVisualizers()(0)?"true":"false")<<"} "
      << " }"<<endl<<endl;
    os <<"replot {"<<endl
      << "int {" <<obj->getSamplesU()<<"}"<<endl
      << "int {" <<obj->getSamplesV()<<"}"<<endl
      << "int {" <<obj->getDerivativesU()<<"}"<<endl
      << "int {" <<obj->getDerivativesV()<<"}"<<endl;
    os << "}" <<endl<<"}"<<endl<<endl;


    os << "PTorusData" << std::endl
       << "{" << endl;

    os << "setTubeRadius1{ float {"<<  obj->getTubeRadius1()<< "} }"<<endl;
    os << "setTubeRadius2{ float {"<<  obj->getTubeRadius2()<< "} }"<<endl;
    os << "setWheelRadius{ float {"<<  obj->getWheelRadius()<< "} }"<<endl;

    os << "}" <<endl<<endl;
}

void Scenario::savePS(std::ofstream &os, const GMlib::PSphere<float> *obj) {

    using namespace std;

    os << "PSurfData"<<endl<<"{"<<endl
       <<"enableDefaultVisualize { bool {" << ( obj->getVisualizers()(0)?"true":"false")<<"} "
      << " }"<<endl<<endl;
    os <<"replot {"<<endl
      << "int {" <<obj->getSamplesU()<<"}"<<endl
      << "int {" <<obj->getSamplesV()<<"}"<<endl
      << "int {" <<obj->getDerivativesU()<<"}"<<endl
      << "int {" <<obj->getDerivativesV()<<"}"<<endl;
    os << "}" <<endl<<"}"<<endl<<endl;


    os << "PSphereData" << std::endl
       << "{" << endl;

    os << "setRadius{ float {"<<  obj->getRadius()<< "} }"<<endl;

    os << "}" <<endl<<endl;
}

void Scenario::savePC(std::ofstream &os, const GMlib::PCylinder<float> *obj) {

    using namespace std;

    os << "PSurfData"<<endl<<"{"<<endl
       <<"enableDefaultVisualize { bool {" << ( obj->getVisualizers()(0)?"true":"false")<<"} "
      << " }"<<endl<<endl;
    os <<"replot {"<<endl
      << "int {" <<obj->getSamplesU()<<"}"<<endl
      << "int {" <<obj->getSamplesV()<<"}"<<endl
      << "int {" <<obj->getDerivativesU()<<"}"<<endl
      << "int {" <<obj->getDerivativesV()<<"}"<<endl;
    os << "}" <<endl<<"}"<<endl<<endl;



    os << "PCylinderData" << std::endl
       << "{" << endl;

    os <<"setConstants {"<<endl
      << "float {" <<obj->getRadiusX()<<"}"<<endl
      << "float {" <<obj->getRadiusY()<<"}"<<endl
      << "float {" <<obj->getHeight()<<"}"<<endl;
    os << "}" <<endl<<"}"<<endl<<endl;

    os << "}" <<endl<<endl;
}

void Scenario::savePP(std::ofstream &os, const GMlib::PPlane<float> *obj) {

    using namespace std;

    os << "PSurfData"<<endl<<"{"<<endl
       <<"enableDefaultVisualize { bool {" << ( obj->getVisualizers()(0)?"true":"false")<<"} "
      << " }"<<endl<<endl;
    os <<"replot {"<<endl
      << "int {" <<obj->getSamplesU()<<"}"<<endl
      << "int {" <<obj->getSamplesV()<<"}"<<endl
      << "int {" <<obj->getDerivativesU()<<"}"<<endl
      << "int {" <<obj->getDerivativesV()<<"}"<<endl;
    os << "}" <<endl<<"}"<<endl<<endl;


    os << "PPlaneData" << std::endl
       << "{" << endl;

    //os << "setRadius{ float {"<<  obj->getRadius()<< "} }"<<endl;

    os << "}" <<endl<<endl;
}

#define FOLDINGEND }

#define Loading {

void Scenario::load() {

    qDebug() << "Open scene...";
    //SimStateLock a(*this);
    stopSimulation();


    auto filename = std::string("gmlib_save.openddl");

    auto is = std::ifstream(filename,std::ios_base::in);
    if(!is.is_open()) {
        std::cerr << "Unable to open " << filename << " for reading..."
                  << std::endl;
        return;
    }

    is.seekg( 0, std::ios_base::end );
    auto buff_length = is.tellg();
    is.seekg( 0, std::ios_base::beg );

    std::vector<char> buffer(buff_length);
    is.read(buffer.data(),buff_length);


    std::cout << "Buffer length: " << buff_length << std::endl;

    GMlibSceneLoaderDataDescription gsdd;

    ODDL::DataResult result = gsdd.ProcessText(buffer.data());
    if(result != ODDL::kDataOkay) {

        auto res_to_char = [](auto nr, const ODDL::DataResult& result) {
            return char(((0xff << (8*nr)) & result ) >> (8*nr));
        };

        auto res_to_str = [&res_to_char](const ODDL::DataResult& result) {
            return std::string() + res_to_char(3,result) + res_to_char(2,result) + res_to_char(1,result) + res_to_char(0,result);
        };

        std::cerr << "Data result no A-OK: " << res_to_str(result) << " (" << result << ")" << std::endl;
        return;
    }



    std::cout << "Data result A-OK" << std::endl;
    auto structure = gsdd.GetRootStructure()->GetFirstSubnode();
    while(structure) {


        // Do something ^^,
        // Travers the ODDL structures and build your scene objects


        structure = structure->Next();
    }


    //Load GMlib::SceneObjects into the scene.

}

#define FOLDINGEND }

// **************************************************************

