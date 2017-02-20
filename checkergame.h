#ifndef CCHECKERGAME_H
#define CCHECKERGAME_H

#include <QObject>

#include <Qt3DCore/QEntity>

#include "piece.h"

namespace Qt3DCore {
    class QTransform;
}

namespace Qt3DRender {
    class QPickEvent;
}

namespace Qt3DExtras {
    class QPlaneMesh;
}

class CCheckerGame : public QObject
{
    Q_OBJECT
public:
    explicit CCheckerGame(QObject *parent = 0);
    Qt3DCore::QEntity* sceneRoot();
signals:

public slots:
    void onPieceClicked(CPiece* clickedPiece);

private:
    void createBoard();
    void createCheckers();
    QVector3D getPositionOnBoard(int x, int y);
    QPoint getPiecePosition(CPiece* piece);

    CPiece* m_pieces[8][8];
    Qt3DCore::QEntity* m_board = nullptr;
    Qt3DCore::QEntity* m_sceneRoot = nullptr;

    Qt3DExtras::QPlaneMesh* m_boardMesh = nullptr;
    Qt3DCore::QTransform* m_boardTransform = nullptr;
    int m_boardHeight = 16;
    int m_boardWidth = 16;
};

#endif // CCHECKERGAME_H
