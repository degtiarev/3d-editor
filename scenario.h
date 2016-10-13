#ifndef SCENARIO_H
#define SCENARIO_H


// local
class TestTorus;
class Vector;


// gmlib
namespace GMlib {

class Scene;
class Camera;
class PointLight;
class DefaultRenderer;
class DefaultSelectRenderer;
// **************************************************************
class RenderTarget;
class SceneObject;

template <typename T> class PTorus;
template <typename T> class PSphere;
template <typename T> class PCylinder;
template <typename T> class PPlane;
template <typename T, int n> class Point;
template <typename T, int n> class Vector;

class Angle;
// **************************************************************
}

//
// qt
#include <QObject>
#include <QRect>

//qgui
#include <QKeyEvent>

// stl
#include <iostream>
#include <memory>

class Scenario: public QObject {
    Q_OBJECT
public:
    explicit Scenario();
    virtual ~Scenario();

    void                                              initialize();
    void                                              deinitialize();
    virtual void                                      initializeScenario();

    void                                              startSimulation();
    void                                              stopSimulation();
    void                                              toggleSimulation();

    void                                              render( const QRect& viewport, GMlib::RenderTarget& target );
    void                                              prepare();
    void                                              replotTesttorus();


    // **************************************************************

    void                                              camFly(char direction);

    void                                              zoomCameraW(const float &zoom_var);
    void                                              switchCamera(int n);
    void                                              movePan(const int &_delta, char direction);
    void                                              moveCamera(const QPoint &begin_pos, const QPoint &end_pos);

    GMlib::SceneObject*                               findSceneObject(QPoint &pos);
    void                                              tryToSelectObject(QPoint &pos);
    void                                              tryToDeselectObject(QPoint &pos);
    void                                              tryToLockOnObject(QPoint &pos);


    void                                              selectChildrenObjects(GMlib::SceneObject* object);
    void                                              toggleSelectAll();
    void                                              moveObject(QPoint &pos,QPoint &prev);

    void                                              rotateObj(QPoint &pos,QPoint &prev);
    void                                              scaleObjects(int &delta);

    void                                              selectAll();
    void                                              unlockObjs();
    void                                              changeColor(GMlib::SceneObject* obj);
    GMlib::SceneObject*                               _selectedObjVar=nullptr;
    GMlib::SceneObject*                               _foundObjVar=nullptr;

    void                                               save();
    void                                               load();

    GMlib::Point<int, 2> fromQtToGMlibViewPoint     ( const QPoint& pos);

    // **************************************************************


protected:
    void                                              timerEvent(QTimerEvent *e) override;

private:
    std::shared_ptr<GMlib::Scene>                     _scene;
    int                                               _timer_id;


    bool                                              ifSelectedVar;

    //select_renderer
    std::shared_ptr<GMlib::DefaultSelectRenderer>     _select_renderer {nullptr};

    std::shared_ptr<GMlib::DefaultRenderer>           _renderer { nullptr };
    std::shared_ptr<GMlib::Camera>                    _camera   { nullptr };
    QRect                                             _viewport { QRect(0,0,1,1) };

    std::shared_ptr<GMlib::PointLight>                _light;
    std::shared_ptr<TestTorus>                        _testtorus;



private:
    static std::unique_ptr<Scenario>                  _instance;

    void         save( std::ofstream& os, const GMlib::SceneObject* obj);
    void         saveSO( std::ofstream& os, const GMlib::SceneObject* obj);
    void         savePT( std::ofstream& os, const GMlib::PTorus<float>* obj);
    void         savePS(std::ofstream &os, const GMlib::PSphere<float> *obj);
    void         savePC(std::ofstream &os, const GMlib::PCylinder<float> *obj);
    void         savePP(std::ofstream &os, const GMlib::PPlane<float> *obj);

public:
    static Scenario&                                  instance();
};

#endif
