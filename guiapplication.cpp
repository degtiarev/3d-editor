#include "guiapplication.h"

// qt
#include <QOpenGLContext>
#include <QDebug>
#include <QInputEvent>

// stl
#include <iostream>
#include <cassert>



GuiApplication::GuiApplication(int& argc, char **argv) : QGuiApplication(argc, argv) {

    setApplicationDisplayName( "Hello GMlib ^^," );

    connect(this, &QGuiApplication::lastWindowClosed,this, &QGuiApplication::quit );
    connect(this, &GuiApplication::signOnSceneGraphInitializedDone, this, &GuiApplication::afterOnSceneGraphInitialized );
    connect(&_window, &Window::sceneGraphInitialized,this, &GuiApplication::onSceneGraphInitialized,Qt::DirectConnection );
    connect(&_window, &Window::sceneGraphInvalidated, this, &GuiApplication::onSceneGraphInvalidated, Qt::DirectConnection );
    connect(&_window,&Window::signKeyPressed, this,&GuiApplication::handleKeyPress);
    connect(&_window, &Window::beforeRendering, this, &GuiApplication::handleGLInputEvents, Qt::DirectConnection);

    // **************************************************************
    connect(&_window, &Window::signMousePressed, this, &GuiApplication::handleMouseButtonPressedEvents);
    connect(&_window, &Window::signMouseReleased, this, &GuiApplication::handleMouseButtonReleasedEvents);
    connect(&_window, &Window::signMouseMoved, this, &GuiApplication::handleMouseMovementEvents);
    connect(&_window, &Window::signWheelEventOccurred, this, &GuiApplication::handleMouseWheel);
    // **************************************************************

    _window.setSource(QUrl("qrc:///qml/main.qml"));
    _window.show();
}

GuiApplication::~GuiApplication() {

    _scenario.stopSimulation();

    _window.releasePersistence();
    _window.releaseResources();

    std::cout << "Bye bye ^^, ~~ \"emerge --oneshot life\"" << std::endl;
}

void
GuiApplication::onSceneGraphInitialized() {

    // Init the scene object and GMlibs OpenGL backend
    _scenario.initialize();

    // Pring surface format
    qDebug() << _window.format();

    // Init a scenario
    _scenario.initializeScenario();
    _scenario.prepare();

    emit signOnSceneGraphInitializedDone();
}

void
GuiApplication::afterOnSceneGraphInitialized() {

    // Start simulator
    _scenario.startSimulation();
}

void GuiApplication::onSceneGraphInvalidated() {

    _scenario.deinitialize();
}


// **************************************************************
//Graphic handle implimentation;
//Must call information from scenario;
void GuiApplication::handleGLInputEvents()
{
    while ( !_input_events.empty()) {
        const auto& e = _input_events.front();
        const auto& ke = std::dynamic_pointer_cast<const QKeyEvent>(e);
        const auto& me = std::dynamic_pointer_cast<const QMouseEvent>(e);
        const auto& we = std::dynamic_pointer_cast<const QWheelEvent>(e);


        //Wheel Event
        if(we){
            int delta = we->delta();
            _scenario.scaleObj(delta);
        }

        // Keys
        if (ke and ke->key()==Qt::Key_P){
            qDebug()<<"Handling the P button";
            _scenario.replotTesttorus();
        }

        if(ke and ke->key()==Qt::Key_A){
            _scenario.toggleSelectAll();
        }

        if(ke and ke->key()==Qt::Key_C){
            _scenario.changeColor(_scenario._selectedObjVar);
        }


        //Left button
        if(me and me->buttons()==Qt::LeftButton){
            if(me->modifiers()==Qt::AltModifier){
                _scenario.moveObj(_startpos,_endpos);
            }
            if(me->modifiers()==Qt::ControlModifier){
                _scenario.rotateObj(_startpos,_endpos);
            }

            if(me and me->type()==QEvent::MouseMove){
                if(me->modifiers()==Qt::AltModifier){
                    _scenario.moveObj(_startpos,_endpos);}

                if(me->modifiers()==Qt::ControlModifier){
                    _scenario.rotateObj(_startpos,_endpos);
                }
            }
        }

        //Right button
        if(me and me->buttons()== Qt::RightButton){
            if(!me->modifiers()){
                if (_scenario.findSceneObj(_endpos)){
                    _scenario.getObj(_scenario.findSceneObj(_endpos));}
            }
            if(me->modifiers()==Qt::ShiftModifier){
                if (_scenario.findSceneObj(_endpos)){
                    _scenario.deselectObj();}
            }
            if(me->modifiers()==Qt::ControlModifier){
                if (_scenario.findSceneObj(_endpos)){
                    _scenario.storeObj(_scenario.findSceneObj(_endpos));}}
        }

        _input_events.pop();
    }
}

void GuiApplication::handleKeyPress(QKeyEvent *e)
{

    //qDebug()<<e->text();

    if (e->key()==Qt::Key_Q) {_window.close(); }
    if (e->key()==Qt::Key_P) { _input_events.push(std::make_shared<QKeyEvent>(*e)); }
    if (e->key()==Qt::Key_R){_scenario.toggleSimulation();}

    if (e->key() == Qt::Key_Up){_scenario.camFlyUp();}
    if (e->key() == Qt::Key_Down){_scenario.camFlyDown();}
    if (e->key() == Qt::Key_Right){_scenario.camFlyRight();}
    if (e->key() == Qt::Key_Left){_scenario.camFlyLeft();}


    if(e->key()==Qt::Key_1){_scenario.switchCam(1);}
    if(e->key()==Qt::Key_2){_scenario.switchCam(2);}
    if(e->key()==Qt::Key_3){_scenario.switchCam(3);}
    if(e->key()==Qt::Key_4){_scenario.switchCam(4);}

    if(e->key()==Qt::Key_S) {_scenario.save();}
    if(e->key()==Qt::Key_L) {_scenario.load();}
    if(e->key()==Qt::Key_A){ _input_events.push(std::make_shared<QKeyEvent>(*e));}
    if(e->key()== Qt::Key_C){_input_events.push(std::make_shared<QKeyEvent>(*e));}
    if(e->key()==Qt::Key_U){_scenario.unlockObjs();}
}

//Mouse Click Handler
void GuiApplication::handleMouseButtonPressedEvents(QMouseEvent *m) {

    _startpos = _endpos;
    _endpos.setX(m->pos().x());
    _endpos.setY(m->pos().y());


    if( m->buttons() == Qt::LeftButton ) {

        _leftMousePressed = true;
        _input_events.push(std::make_shared<QMouseEvent>(*m));
    }

    if(m->buttons()==Qt::RightButton){

        _input_events.push(std::make_shared<QMouseEvent>(*m));
    }


}

//Mouse Move Handler
void GuiApplication::handleMouseMovementEvents(QMouseEvent *v) {

    if(v->type()==QEvent::MouseMove && _Mouse_pressed == true){
        //update position
        _startpos = _endpos;
        _endpos.setX(v->pos().x());
        _endpos.setY(v->pos().y());

        if(v->modifiers()==Qt::AltModifier || v->modifiers()==Qt::ShiftModifier){
            _input_events.push(std::make_shared<QMouseEvent>(*v));
        }
        if(v->modifiers()==Qt::ControlModifier){
            _input_events.push(std::make_shared<QMouseEvent>(*v));
        }
        if(!v->modifiers()){
            _scenario.NewMoveCamera(_startpos,_endpos);}
    }
}

//Mouse Release Handler
void GuiApplication::handleMouseButtonReleasedEvents(QMouseEvent *m) {
    if( m->type() == QEvent::MouseButtonRelease && m->button()==Qt::LeftButton ) {
        //  qDebug() << "Left Mouse Button Unpressed";
        _leftMousePressed = false;
    }
}

//MouseWheel Handler
void GuiApplication::handleMouseWheel(QWheelEvent *w){
    int delta = w->delta();

    if (!w->modifiers()){
        if (delta<0){_scenario.zoomCameraW(1.05);}
        if (delta>0) {_scenario.zoomCameraW(0.95);}
    }

    if (w->modifiers()==Qt::ShiftModifier){ _scenario.panVertical(delta);}
    if (w->modifiers()==Qt::ControlModifier){_scenario.panHorizontal(delta);}

    if (w->modifiers()==Qt::AltModifier){
        _input_events.push(std::make_shared<QWheelEvent>(*w));
    }
}

// **************************************************************

