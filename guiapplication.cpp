#include "guiapplication.h"

// qt
#include <QOpenGLContext>
#include <QDebug>
#include <QInputEvent>

// stl
#include <iostream>
#include <cassert>



GuiApplication::GuiApplication(int& argc, char **argv) : QGuiApplication(argc, argv) {

    setApplicationDisplayName( "Aleksei Degtiarev" );

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

    _window.setTitle("3D Editor");
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
            _scenario.scaleObjects(delta);}

        // Keys
        if (ke and ke->key()==Qt::Key_P){
            _scenario.replotTesttorus();}

        if(ke and ke->key()==Qt::Key_A){
            _scenario.toggleSelectAll();}

        if(ke and ke->key()==Qt::Key_C){
            qDebug()<<"change color";
            _scenario.changeColor();}

        if(ke and ke->key() == Qt::Key_N){
            qDebug()<<"insert sphere";
            _scenario.insertObject(_endpos, 's');}

        if(ke and ke->key() == Qt::Key_D)
        {
            qDebug() << "Deleting selected objects";
            _scenario.deleteObject();
        }


        //Left button
        if(me and me->buttons()==Qt::LeftButton){
            if(me->modifiers()==Qt::AltModifier){
                _scenario.moveObject(_startpos,_endpos);}

            if(me->modifiers()==Qt::ControlModifier){
                _scenario.rotateObj(_startpos,_endpos);}

            if(me->modifiers()==Qt::ShiftModifier){
                _scenario.tryToLockOnObject(_endpos);}
        }

        //Right button
        if(me and me->buttons()== Qt::RightButton){
            if(!me->modifiers()) {
                _scenario.tryToSelectObject(_endpos,'1');}

            if(me->modifiers()==Qt::ControlModifier){
                _scenario.tryToSelectObject(_endpos,'a');}
        }

        _input_events.pop();
    }
}

void GuiApplication::handleKeyPress(QKeyEvent *e)
{
    //qDebug()<<e->text();

    if (e->key()==Qt::Key_Q) {_window.close(); }
    else  if (e->key()==Qt::Key_R){_scenario.toggleSimulation();}

    else if (e->key() == Qt::Key_Up){_scenario.camFly('U');}
    else  if (e->key() == Qt::Key_Down){_scenario.camFly('D');}
    else  if (e->key() == Qt::Key_Right){_scenario.camFly('R');}
    else  if (e->key() == Qt::Key_Left){_scenario.camFly('L');}

    else   if (e->key()==Qt::Key_1){_scenario.switchCamera(1);}
    else  if (e->key()==Qt::Key_2){_scenario.switchCamera(2);}
    else  if (e->key()==Qt::Key_3){_scenario.switchCamera(3);}
    else  if (e->key()==Qt::Key_4){_scenario.switchCamera(4);}

    else  if (e->key()==Qt::Key_S) {_scenario.save();}
    else  if (e->key()==Qt::Key_L) {_scenario.load();}
    else  if (e->key()==Qt::Key_U){_scenario.unlockObjs();}

    else _input_events.push(std::make_shared<QKeyEvent>(*e));
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

        if(!v->modifiers()){
            _scenario.moveCamera(_startpos,_endpos);}

        else
        { _input_events.push(std::make_shared<QMouseEvent>(*v));}
    }
}

//Mouse Release Handler
void GuiApplication::handleMouseButtonReleasedEvents(QMouseEvent *m) {
    if( m->type() == QEvent::MouseButtonRelease && m->button()==Qt::LeftButton ) {
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

    if (w->modifiers()==Qt::ShiftModifier){ _scenario.movePan(delta,'W');}
    if (w->modifiers()==Qt::ControlModifier){_scenario.movePan(delta,'H');}
    if (w->modifiers()==Qt::AltModifier){_input_events.push(std::make_shared<QWheelEvent>(*w));
    }
}

// **************************************************************

