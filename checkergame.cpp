#include "checkergame.h"

#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QTextureImage>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QDiffuseMapMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickEvent>
#include <Qt3DCore/QTransform>

#include <QDebug>

CCheckerGame::CCheckerGame(QObject *parent) : QObject(parent)
{
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            m_pieces[i][j] = nullptr;
        }
    }

    m_sceneRoot = new Qt3DCore::QEntity;
    createBoard();
    createCheckers();
}

Qt3DCore::QEntity *CCheckerGame::sceneRoot()
{
    return m_sceneRoot;
}

void CCheckerGame::onPieceClicked(CPiece *clickedPiece)
{
    QPoint pos = getPiecePosition(clickedPiece);
    qDebug() << "X:" << pos.x() << " Y:" << pos.y();
}

void CCheckerGame::createBoard()
{
    m_board = new Qt3DCore::QEntity(m_sceneRoot);

    m_boardMesh = new Qt3DExtras::QPlaneMesh;
    m_boardMesh->setWidth(m_boardWidth);
    m_boardMesh->setHeight(m_boardHeight);

    m_boardTransform = new Qt3DCore::QTransform;
    m_boardTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    auto checkerBoardMaterial = new Qt3DExtras::QDiffuseMapMaterial;
    auto image = new Qt3DRender::QTextureImage();
    image->setSource(QUrl(QStringLiteral("qrc:/assets/chess4.jpg")));
    checkerBoardMaterial->diffuse()->addTextureImage(image);

    m_board->addComponent(checkerBoardMaterial);
    m_board->addComponent(m_boardMesh);
    m_board->addComponent(m_boardTransform);
}

void CCheckerGame::createCheckers()
{
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 4; ++j){
            m_pieces[j*2 + (i+1)%2][i] = new CPiece(getPositionOnBoard(j*2 + (i+1)%2,i),
                                                    QColor(100, 100, 100),
                                                    m_sceneRoot);

            m_pieces[j*2+(i+1)%2][6+i] = new CPiece(getPositionOnBoard(j*2 + (i+1)%2,6+i),
                                                    QColor(200, 200, 200),
                                                    m_sceneRoot);

            connect(m_pieces[j*2 + (i+1)%2][i], &CPiece::clicked, this, &CCheckerGame::onPieceClicked);
            connect(m_pieces[j*2+(i+1)%2][6+i], &CPiece::clicked, this, &CCheckerGame::onPieceClicked);
        }
    }
}

QVector3D CCheckerGame::getPositionOnBoard(int x, int y)
{
    QVector3D position = m_boardTransform->translation();
    position.setX(position.x() - m_boardMesh->width()/2);
    position.setZ(position.z() - m_boardMesh->height()/2);

    position.setX(position.x() + m_boardMesh->width()/16);
    position.setZ(position.z() + m_boardMesh->height()/16);

    position.setX(position.x() + x * m_boardMesh->width()/8);
    position.setZ(position.z() + y * m_boardMesh->height()/8);

    return position;
}

QPoint CCheckerGame::getPiecePosition(CPiece *piece)
{
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(m_pieces[i][j] == piece) {
                return QPoint(i, j);
            }
        }
    }
}
