#include "boardinterface.h"
#include <QLabel>
#include "boardfield.h"
#include "boardposition.h"
#include "constants.h"
#include "boardborderfield.h"
#include "gameinterface.h"
#include "pawnfield.h"

extern GameInterface *game;

int BoardInterface::boardSize = Constants::defaultBoardSize;
int BoardInterface::boardXPosition = (Constants::gameInterfaceWidth - Constants::defaultBoardSize * Constants::defaultBoardFieldSize) / 2;
int BoardInterface::boardYPosition = 150;

BoardInterface::BoardInterface() {
    int size = boardSize * BoardField::defaultSize;
    setRect(boardXPosition, boardYPosition, size, size);
    game->scene->addItem(this);
}

QList<BoardField*> BoardInterface::getFields() {
    return fields;
}

void BoardInterface::drawBoard() {
    drawBoardFields();
    drawBoardFrame();
}

void BoardInterface::initializePawnFields(QList<BasePawn*> pawns) {
    for (BasePawn* pawnModel : pawns) {
        BoardPosition pawnPosition = pawnModel->getBoardPosition();

        int pawnXPosition = boardXPosition + pawnPosition.x * BoardField::defaultSize;
        int pawnYPosition = boardYPosition + pawnPosition.y * BoardField::defaultSize;

        PawnField* pawn = new PawnField(pawnPosition, pawnModel->getIconPath(), this);
        pawn->setRect(0, 0, BoardField::defaultSize, BoardField::defaultSize);
        pawn->setPos(pawnXPosition, pawnYPosition);

        this->pawns.append(pawn);
    }
}


void BoardInterface::moveActivePawnToMousePosition(QPoint point, BasePawn *pawn) {
    int xPosition = point.x() - BoardField::defaultSize/2;
    int yPosition = point.y() - BoardField::defaultSize/2;
    PawnField *pawnField = getPawnAtBoardPosition(pawn->getBoardPosition());

    if (pawnField) {
        pawnField->setPos(xPosition, yPosition);
    }
}

void BoardInterface::placeActivePawnAtBoardPosition(BasePawn *pawn, BoardPosition boardPosition) {
    PawnField *pawnField = getPawnAtBoardPosition(pawn->getBoardPosition());
    if (pawnField) {
        QPointF coordinates = getCoordinatesForBoardPosition(boardPosition);
        pawnField->setZValue(0);
        pawnField->setPos(coordinates);
        pawnField->setPosition(boardPosition);
    }
}

void BoardInterface::removePawnAtBoardPosition(BoardPosition boardPosition) {
    PawnField *pawnField = getPawnAtBoardPosition(boardPosition);

    game->scene->removeItem(pawnField);

    int index = pawns.indexOf(pawnField);
    pawns.removeAt(index);
    delete pawnField;
}


void BoardInterface::promotePawnAtBoardPosition(BoardPosition boardPosition) {
    PawnField* pawn = getPawnAtBoardPosition(boardPosition);
    QString imageFileName = (boardPosition.y == 7) ? ":Images/queen_black.svg" : ":Images/queen_white.svg";
    pawn->setImage(imageFileName);
}

PawnField* BoardInterface::getPawnAtMousePosition(QPoint point) {
    for (PawnField* pawn : pawns) {
        QRectF pawnRect = QRectF(pawn->pos(), pawn->rect().size());
        if (pawnRect.contains(point)) {
            return pawn;
        }
    }
    return nullptr;
}

PawnField* BoardInterface::getPawnAtBoardPosition(BoardPosition boardPosition) {
    for (PawnField* pawn : pawns) {
        BoardPosition pawnPosition = pawn->getPosition();
        if (pawnPosition.x == boardPosition.x && pawnPosition.y == boardPosition.y) {
            return pawn;
        }
    }
    return nullptr;
}

void BoardInterface::drawBoardFields() {
    for (int col = 0; col<this->boardSize; col++ ) {
        for (int row = 0; row<this->boardSize; row++) {
            QColor backgroundColor = (col+row)%2==0 ? Constants::boardFieldLightColor : Constants::boardFieldDarkColor;

            BoardPosition boardFieldPosition = {col, row};

            BoardField *boardField = new BoardField(backgroundColor, boardFieldPosition, this);

            int boardFieldXPosition = this->boardXPosition + col * BoardField::defaultSize;
            int boardFieldYPosition = this->boardYPosition + row * BoardField::defaultSize;

            boardField->setRect(boardFieldXPosition, boardFieldYPosition, BoardField::defaultSize, BoardField::defaultSize);

            this->fields.append(boardField);
        }
    }
}

void BoardInterface::drawBoardFrame() {

    QRectF horizontalFieldRect = QRectF(0, 0, BoardField::defaultSize, BoardField::defaultSize/2);
    QRectF verticalFieldRect = QRectF(0, 0, BoardField::defaultSize/2, BoardField::defaultSize);

    for (int i = 0; i < this->boardSize; i++) {

        // Horizontal Board Border Field
        // Upper bound
        int xPosition = boardXPosition + i * BoardField::defaultSize;
        QPoint point = QPoint(xPosition, boardYPosition - BoardField::defaultSize/2);
        new BoardBorderField(point, horizontalFieldRect, Constants::boardBorderItemsHorizontal[i], this);

        // Lower bound
        int yPosition = boardYPosition + this->boardSize * BoardField::defaultSize;
        point = QPoint(xPosition, yPosition);
        new BoardBorderField(point, horizontalFieldRect, Constants::boardBorderItemsHorizontal[i], this);

        // Vertical Board Border Field
        // Left hand bound
        yPosition = boardYPosition + i * BoardField::defaultSize;
        point = QPoint(this->boardXPosition - BoardField::defaultSize/2, yPosition);
        new BoardBorderField(point, verticalFieldRect, Constants::boardBorderItemsVertical[i], this);

        // Right hand bound
        xPosition = boardXPosition + this->boardSize * BoardField::defaultSize;
        yPosition = boardYPosition + i * BoardField::defaultSize;
        point = QPoint(xPosition, yPosition);
        new BoardBorderField(point, verticalFieldRect, Constants::boardBorderItemsVertical[i], this);
    }


    QRectF cornerFieldRect = QRectF(0, 0, BoardField::defaultSize/2, BoardField::defaultSize/2);

    // Corner Bard Border Fields
    int xPosition = boardXPosition - BoardField::defaultSize/2;
    int yPosition = boardYPosition - BoardField::defaultSize/2;
    QPoint point = QPoint(xPosition, yPosition);
    new BoardBorderField(point, cornerFieldRect, "\\", this);

    xPosition = boardXPosition + boardSize * BoardField::defaultSize;
    yPosition = boardYPosition - BoardField::defaultSize/2;
    point = QPoint(xPosition, yPosition);
    new BoardBorderField(point, cornerFieldRect, "/", this);


    // Corner Bard Border Fields
    xPosition = boardXPosition - BoardField::defaultSize/2;
    yPosition = boardYPosition + boardSize * BoardField::defaultSize;
    point = QPoint(xPosition, yPosition);
    new BoardBorderField(point, cornerFieldRect, "/", this);

    xPosition = boardXPosition + boardSize * BoardField::defaultSize;
    yPosition = boardYPosition + boardSize * BoardField::defaultSize;
    point = QPoint(xPosition, yPosition);
    new BoardBorderField(point, cornerFieldRect, "\\", this);
}

QPointF BoardInterface::getCoordinatesForBoardPosition(BoardPosition position) {
    int xPosition = boardXPosition + position.x*BoardField::defaultSize;
    int yPosition = boardYPosition + position.y*BoardField::defaultSize;
    // qDebug() << "Coordinates:" << xPosition << " | " << yPosition;
    return QPointF(xPosition, yPosition);
}
