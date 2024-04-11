#ifndef PAWN_H
#define PAWN_H

#include <QGraphicsRectItem>
#include <QLabel>
#include "boardposition.h"

/**
 * @brief The PawnField class represents a pawn on the game board.
 */
class PawnField: public QGraphicsRectItem {

public:
    /**
     * @brief Constructs a PawnField object with specified attributes.
     *
     * @param position The position of the pawn on the board.
     * @param imagePath The file path to the image representing the pawn.
     * @param parent The parent graphics item.
     */
    PawnField(BoardPosition position, QString imagePath, QGraphicsItem *parent = nullptr);

    /**
     * @brief Gets the position of the pawn.
     *
     * @return The position of the pawn.
     */
    BoardPosition getPosition();

    /**
     * @brief Sets the position of the pawn.
     *
     * @param position The new position of the pawn.
     */
    void setPosition(BoardPosition position);

    /**
     * @brief Sets the image representing the pawn.
     *
     * @param imagePath The file path to the image representing the pawn.
     */
    void setImage(QString imagePath);

private:
    BoardPosition position; /**< The position of the pawn on the board. */
    QLabel *imageLabel; /**< The label displaying the image of the pawn. */
    QPixmap image; /**< The pixmap representing the image of the pawn. */
};

#endif // PAWN_H
