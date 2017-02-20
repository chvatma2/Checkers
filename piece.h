#ifndef PIECE_H
#define PIECE_H

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QPickEvent>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <QPoint>

class CPiece : public Qt3DCore::QEntity
{
    Q_OBJECT
public:
    CPiece(QVector3D position, QColor color, QNode *parent = nullptr);
    void changePosition(QVector3D position);
public slots:
    void onClicked(Qt3DRender::QPickEvent *pick);
signals:
    void clicked(CPiece* piece);
private:
    Qt3DCore::QTransform* m_transform;
    Qt3DExtras::QCylinderMesh* m_mesh;
    QVector3D m_position;
};

#endif // PIECE_H
