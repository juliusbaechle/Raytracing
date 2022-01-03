#include <qapplication>
#include <qtimer.h>
#include "Simulator.h"

#include "Primitive.h"
#include "Fragment.h"
#include "Sphere.h"

#include "Scene.h"
#include "Camera.h"

#include <qdatetime.h>
#include <qdebug.h>

// https://www.hochschule-bochum.de/fileadmin/public/Die-BO_Einrichtungen/Hochschulkommunikation/Presse/FAWIS/Albers_facharbeitRaytracing.pdf

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);    
   
  Display& display = Simulator(800, 800); 

  Primitive* floor      = new Fragment({  5,  2, -2 }, { -10, 0, 0 }, { 0, -4, 0 }, false, { 142, 142, 142 });
  Primitive* ceiling    = new Fragment({  5,  2,  2 }, { -10, 0, 0 }, { 0, -4, 0 }, false, { 142, 142, 142 });  
  Primitive* leftWall   = new Fragment({  5, -2, -2 }, { -10, 0, 0 }, { 0,  0, 4 }, false, { 218, 121,   0 });
  Primitive* rightWall  = new Fragment({  5,  2, -2 }, { -10, 0, 0 }, { 0,  0, 4 }, false, {  53, 157, 187 });
  Primitive* frontWall  = new Fragment({ -5,  2, -2 }, {  0, -4, 0 }, { 0,  0, 4 }, false, { 174, 255, 174 });
  Primitive* backWall   = new Fragment({  5,  2, -2 }, {  0, -4, 0 }, { 0,  0, 4 }, false, { 174, 174, 174 });

  Primitive* backBall   = new Sphere({ -3, -1, -1.25 }, 0.75, { 208,208,208 });
  backBall->reflective = true;

  Primitive* frontBall  = new Sphere({ 0, 0.99, -0.99 }, 0.75, { 208,208,208 });
  frontBall->transparent = true;

  Scene scene;
  scene.addObject(floor);
  scene.addObject(ceiling);
  scene.addObject(leftWall);
  scene.addObject(rightWall);
  scene.addObject(frontWall);
  //scene.addObject(backWall); 
  scene.addObject(backBall);
  scene.addObject(frontBall);

  LightSource light{ new Sphere({ -2, 0, 2 }, 0.75, { 255, 255, 255 }), {-2, 0, 1.8} };
  scene.setLightSource(&light);

  PerspectiveCamera camera({ 5, 0, 0 }, { 800, 800 });

  qint64 ms = QDateTime::currentMSecsSinceEpoch();
  camera.render(scene);
  display.show(camera.picture());
  qDebug() << QString("Needed: %1 ms").arg(QDateTime::currentMSecsSinceEpoch() - ms);

  return a.exec();
}