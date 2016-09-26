#ifndef SCENARIO_H
#define SCENARIO_H


// local
class TestTorus;


// gmlib
namespace GMlib {

class Scene;
class Camera;
class PointLight;
class DefaultRenderer;
class DefaultSelectRenderer;
class RenderTarget;

// **************************************************************
template <typename T, int n> class Point;
// **************************************************************
}

//
// qt
#include <QObject>
#include <QRect>


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
    GMlib::Point<int, 2> fromQtToGMlibViewPoint(const GMlib::Camera& cam, const QPoint& pos);

    void moveCamera(const QPoint& p, const QPoint& c);
    // **************************************************************


protected:
    void                                              timerEvent(QTimerEvent *e) override;

private:
    std::shared_ptr<GMlib::Scene>                     _scene;
    int                                               _timer_id;

    std::shared_ptr<GMlib::DefaultRenderer>           _renderer { nullptr };
    std::shared_ptr<GMlib::Camera>                    _camera   { nullptr };
    QRect                                             _viewport { QRect(0,0,1,1) };

    std::shared_ptr<GMlib::PointLight>                _light;
    std::shared_ptr<TestTorus>                        _testtorus;


    std::shared_ptr<GMlib::DefaultSelectRenderer>     _dsr;

private:
    static std::unique_ptr<Scenario>                  _instance;
public:
    static Scenario&                                  instance();
};

#endif
