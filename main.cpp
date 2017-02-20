#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QTextureImage>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QEntity>

#include "checkergame.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Qt3DExtras::Qt3DWindow window;
    CCheckerGame game;
    window.setRootEntity(game.sceneRoot());

    Qt3DRender::QCamera *camera = window.camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 20.0f, 10.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    window.show();

    return a.exec();
}
