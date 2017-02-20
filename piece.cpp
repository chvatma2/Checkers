#include "piece.h"

#include <Qt3DRender/QObjectPicker>

CPiece::CPiece(QVector3D position, QColor color, QNode *parent) : Qt3DCore::QEntity(parent), m_position(position)
{
    m_transform = new Qt3DCore::QTransform;
    m_transform->setScale(1.0f);
    m_transform->setTranslation(position);

    m_mesh = new Qt3DExtras::QCylinderMesh;
    m_mesh->setRadius(0.7);
    m_mesh->setLength(0.5);
    m_mesh->setRings(100);
    m_mesh->setSlices(20);

    auto material = new Qt3DExtras::QPhongMaterial;
    material->setDiffuse(color);

    auto objectPicker = new Qt3DRender::QObjectPicker;
    QObject::connect(objectPicker, &Qt3DRender::QObjectPicker::clicked,
            this, &CPiece::onClicked);

    addComponent(m_mesh);
    addComponent(m_transform);
    addComponent(material);
    addComponent(objectPicker);
}

void CPiece::changePosition(QVector3D position)
{
    m_transform->setTranslation(position);
}

void CPiece::onClicked(Qt3DRender::QPickEvent *pick)
{
    Q_UNUSED(pick);
    emit clicked(this);
}
