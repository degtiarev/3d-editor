#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include "scenario.h"
#include "window.h"

// qt
#include <QGuiApplication>


// stl
#include <memory>
#include <queue>




class GuiApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit GuiApplication(int& argc, char** argv);
    ~GuiApplication();

private:
    Window                                      _window;
    Scenario                                    _scenario;
    std::queue<std::shared_ptr<QInputEvent>> _input_events;

    // **************************************************************
    bool _leftMousePressed;
    QPoint _startpos;
    QPoint _endpos;
    // **************************************************************


private slots:

    void handleGLInputEvents();
    void handleKeyPress(QKeyEvent *e);


    virtual void                                onSceneGraphInitialized();
    virtual void                                afterOnSceneGraphInitialized();

    virtual void                                onSceneGraphInvalidated();


    // **************************************************************
    void  handleMouseButtonPressedEvents(QMouseEvent*);
    void  handleMouseMovementEvents(QMouseEvent*);
    void  handleMouseButtonReleasedEvents(QMouseEvent*);
    // **************************************************************


signals:
    void                                        signOnSceneGraphInitializedDone();
};




#endif // GUIAPPLICATION_H
