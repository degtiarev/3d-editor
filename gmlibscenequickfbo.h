#ifndef GMLIBSCENEQUICKFBO
#define GMLIBSCENEQUICKFBO

// qt
#include <QtQuick/QQuickFramebufferObject>

// stl
#include <chrono>

class GMlibSceneQuickFbo : public QQuickFramebufferObject {
  Q_OBJECT

public:
  GMlibSceneQuickFbo();

  Renderer*         createRenderer() const override;
  Q_PROPERTY(unsigned int fps READ fps NOTIFY signFPSUpdated)
private:

  using std_system_clock = std::chrono::system_clock;
  using std_time_point = std_system_clock::time_point;
  unsigned int fps() const;

  unsigned int _fps_avg {0};
  unsigned int _fps_counter{0};
  std_time_point _prev_time;


protected:
  void              keyPressEvent(QKeyEvent *event) override;
  void              keyReleaseEvent(QKeyEvent *event) override;
  void              mousePressEvent(QMouseEvent *event) override;
  void              mouseReleaseEvent(QMouseEvent *event) override;
  void              mouseDoubleClickEvent(QMouseEvent *event) override;
  void              mouseMoveEvent(QMouseEvent *event) override;
  void              wheelEvent(QWheelEvent *event) override;



private slots:
  void              onWindowChanged( QQuickWindow* window );
  void              updateFps();


signals:
  void              signFPSUpdated();
  void              signKeyPressed( QKeyEvent* event );
  void              signKeyReleased( QKeyEvent* event );
  void              signMouseDoubleClicked( QMouseEvent* event );
  void              signMouseMoved( QMouseEvent* event );
  void              signMousePressed( QMouseEvent* event );
  void              signMouseReleased( QMouseEvent* event );
  void              signWheelEventOccurred( QWheelEvent* event);
};

#endif
