#include "scenario.h"
#include "testtorus.h"

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

void
Scenario::deinitialize() {

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

void
Scenario::initialize() {

    // Setup and initialized GMlib GL backend
    GMlib::GL::OpenGLManager::init();

    // Setup and init the GMlib GMWindow
    _scene = std::make_shared<GMlib::Scene>();
}

void
Scenario::initializeScenario() {

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
    _scene->insertCamera( _camera.get() );
    _renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

    // Surface
    _testtorus = std::make_shared<TestTorus>();
    _testtorus->toggleDefaultVisualizer();
    _testtorus->replot(200,200,1,1);
    _scene->insert(_testtorus.get());

    _testtorus->test01();

    auto cylinder=new GMlib::PCylinder<float>(1);
    cylinder->toggleDefaultVisualizer();
    cylinder->replot(200,200,1,1);
    _scene->insert(cylinder);

}

std::unique_ptr<Scenario> Scenario::_instance {nullptr};

Scenario&
Scenario::instance() { return *_instance; }

void
Scenario::prepare() { _scene->prepare(); }

void
Scenario::render( const QRect& viewport_in, GMlib::RenderTarget& target ) {

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

void
Scenario::startSimulation() {

    if( _timer_id || _scene->isRunning() )
        return;

    _timer_id = startTimer(16, Qt::PreciseTimer);
    _scene->start();
}

void
Scenario::stopSimulation() {

    if( !_timer_id || !_scene->isRunning() )
        return;

    _scene->stop();
    killTimer(_timer_id);
    _timer_id = 0;
}

void
Scenario::timerEvent(QTimerEvent* e) {

    e->accept();

    _scene->simulate();
    prepare();
}

void
Scenario::toggleSimulation() { _scene->toggleRun(); }

void
Scenario::replotTesttorus()
{
    _testtorus->replot(4,4,1,1);\
}

// **************************************************************

void Scenario::moveCamera(const QPoint& c, const QPoint& p) {

    auto previous = fromQtToGMlibViewPoint(*_camera.get(), p);
    auto current = fromQtToGMlibViewPoint(*_camera.get(), c);
    auto tmp = previous - current;

    GMlib::Vector<float,2> d (tmp(0),-tmp(1) );
    d = d * 0.02;
    _camera->move(d);
}
// Makes a point for camera movement
GMlib::Point<int, 2> Scenario::fromQtToGMlibViewPoint(const GMlib::Camera& cam, const QPoint& pos) {

    int h = cam.getViewportH(); // Height of the camera’s viewport
    // QPoint
    int q1 {pos.x()};
    int q2 {pos.y()};
    // GMlib Point
    int p1 = q1;
    int p2 = h - q2 - 1;

    return GMlib::Point<int, 2> {p1, p2};
}


//Camera Vertical rotation right
void Scenario::rotateVCamera(){
    _camera->lock(_testtorus.get());
    _camera->rotateGlobal(GMlib::Angle(0.05f), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ));
}

//Camera Horizontal rotation right
void Scenario::rotateHCamera(){
    _camera->lock(_testtorus.get());
    _camera->rotateGlobal(GMlib::Angle(0.05f),  GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));}

//Camera Vertical rotation left
void Scenario::rotateVCamera_L(){
    _camera->lock(_testtorus.get());
    _camera->rotateGlobal(GMlib::Angle(-0.05f), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ));
}

//Camera Horizontal rotation left
void Scenario::rotateHCamera_L(){
    _camera->lock(_testtorus.get());
    _camera->rotateGlobal(GMlib::Angle(-0.05f), GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ));
    //_camera->move(0.5);
}

//Converting a point for camera movement
//GMlib::Point<int,2> Scenario::fromQtToGMlibViewPoint(const GMlib::Camera& cam, const QPoint& pos) {

//    int h = cam.getViewportH(); // Height of the camera's viewport
//    return GMlib::Vector<int,2>(int(pos.x()),h-int(pos.y())-1);

//}

//Lock Object
void Scenario::lockObject(const bool &lock_var){
    if (lock_var==true){_camera->lock(_testtorus.get());}
}

//Zoom
void Scenario::zoomCameraW(const float &zoom_var){
    _camera->zoom(zoom_var);
}

//Camera Speed Scale
float Scenario::cameraSpeedScale(){
    return _scene->getSphere().getRadius();
}

//Move Camera
void Scenario::NewMoveCamera(const QPoint &begin_pos, const QPoint &end_pos) {

    //auto view_name = viewNameFromParams(params);
    auto pos       = fromQtToGMlibViewPoint(*_camera.get(), begin_pos);
    auto prev      = fromQtToGMlibViewPoint(*_camera.get(), end_pos);

    const float scale = cameraSpeedScale();
    //qDebug()<<scale << _camera->getViewportH() << " " <<_camera->getViewportW();
    GMlib::Vector<float,2> delta (
                -(pos(0) - prev(0))*scale / _camera->getViewportW(),
                (pos(1) - prev(1))*scale / _camera->getViewportH()
                );

    _camera->move( delta );

}

//Vertical pan
void Scenario::panVertical(const int &_delta)
{
    const float scale = cameraSpeedScale();
    auto delta = _delta;
    GMlib::Vector<float,2> delta_vec(0.0f,delta * scale / _camera->getViewportW());
    _camera->move(delta_vec);
}

//Horizontal pan
void Scenario::panHorizontal(const int &_delta)
{
    const float scale = cameraSpeedScale();
    auto delta = _delta;
    GMlib::Vector<float,2> delta_vec(delta * scale / _camera->getViewportH(),0.0f);
    _camera->move(delta_vec);
}

GMlib::Point<int, 2> Scenario::convertToGMlibPoint(const QPoint &pos)
{
    return GMlib::Vector<int,2>(int(pos.x()),int(pos.y()-1));
}

GMlib::SceneObject* Scenario::findSceneObj(QPoint &pos)
{
    GMlib::SceneObject *selected_obj = nullptr;

    _select_renderer->setCamera(_camera.get());
    const GMlib::Vector<int,2> size(_camera->getViewportW(),
                                    _camera->getViewportH());
    //_select_renderer->reshape(size);
    _select_renderer->reshape(size);
    _select_renderer->prepare();
    //select code
    GMlib::Point <int,2> qp = fromQtToGMlibViewPoint(*_camera.get(),pos);

    _select_renderer->select(GMlib::GM_SO_TYPE_SELECTOR);

    selected_obj=_select_renderer->findObject(qp(0),qp(1));
    if(!selected_obj) {

        _select_renderer->select(-GMlib::GM_SO_TYPE_SELECTOR );
        selected_obj = _select_renderer->findObject(qp(0),qp(1));
    }
    if(selected_obj){qDebug()<<"True";};
    _select_renderer->releaseCamera();

    return selected_obj;

}

//Select object
void Scenario::getObj(GMlib::SceneObject *selected_obj){
    //qDebug() <<selected_obj->getTypeId();
    selected_obj->setSelected(true);
    qDebug()<<selected_obj->isSelected();
    //
    //selected_obj->setColor();
}

void Scenario::deselectObj(GMlib::SceneObject *selected_obj)
{
    if (selected_obj->isSelected()){selected_obj->setSelected(false);}
    //selected_obj->setSelected(false);
}

void Scenario::switchCam(int n)
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

void Scenario::selectAll()
{


    //    QPoint point{30,40};

    //    if (fin dSceneObj(point)){
    //        qDebug()<<"True";


    //       // GMlib::SceneObject* obj = findSceneObj(point);
    //       // this->getObj(obj);
    //    }

    //    else
    //        qDebug()<<"False";



    //    for (int i=0; i<=_camera->getViewportH(); i+=50){
    //        for (int j=0; j<=_camera->getViewportW(); j+=50 ){

    //            // qDebug()<< i<<" "<<j;

    //            QPoint point{i,j};

    //            if (findSceneObj(point)){
    //                GMlib::SceneObject* obj = findSceneObj(point);
    //                this->getObj(obj);
    //            }

    //        }
    //    }
    // **************************************************************
}

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

    auto ptorus_obj = dynamic_cast<const GMlib::PTorus<float>*>(obj);
    if(ptorus_obj)
        savePT(os,ptorus_obj);

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

void Scenario::savePT(std::ofstream &os,
                      const GMlib::PTorus<float> *obj) {


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

