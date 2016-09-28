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
template <typename T, int n> class Point;
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
    void                                              rotateVCamera();
    void                                              rotateHCamera();
    void                                              rotateVCamera_L();
    void                                              rotateHCamera_L();

    void                                              zoomCameraW(const float &zoom_var);
    void                                              moveCamera_M(const QPoint &f, const QPoint &e);
    void                                              switchCam(int n);
    float                                             cameraSpeedScale();
    void                                              panHorizontal(const int &_delta);
    void                                              panVertical(const int &_delta);
    void                                              NewMoveCamera(const QPoint &begin_pos, const QPoint &end_pos);

    void                                              lockObject(const bool &lock_var);
    GMlib::SceneObject*                               findSceneObj(QPoint &pos);
    GMlib::Point<int, 2>                              convertToGMlibPoint(const QPoint& pos);
    void                                              getObj(GMlib::SceneObject *selected_obj);
    void                                              deselectObj(GMlib::SceneObject *selected_obj);
    void                                              selectAll();


    void         save();

    GMlib::Point<int, 2> fromQtToGMlibViewPoint(const GMlib::Camera& cam, const QPoint& pos);

    void moveCamera(const QPoint& p, const QPoint& c);
    // **************************************************************


protected:
    void                                              timerEvent(QTimerEvent *e) override;

private:
    std::shared_ptr<GMlib::Scene>                     _scene;
    int                                               _timer_id;

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

public:
    static Scenario&                                  instance();
};

#endif
