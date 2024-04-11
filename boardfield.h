#ifndef BOARDFIELD_H
#define BOARDFIELD_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <boardposition.h>

/**
 * @brief The BoardField class represents a field on the game board.
 */
class BoardField: public QGraphicsRectItem {
public:
    /**
     * @brief Constructs a BoardField object with specified attributes.
     *
     * @param backgroundColor The background color of the field.
     * @param position The position of the field on the board.
     * @param parent The parent graphics item, default is nullptr.
     */
    BoardField(QColor backgroundColor,
               BoardPosition position,
               QGraphicsItem *parent = nullptr);

    static int defaultSize; /**< The default size of the field. */

    /**
     * @brief Gets the position of the field on the board.
     *
     * @return The position of the field.
     */
    BoardPosition getPosition();

private:
    BoardPosition position; /**< The position of the field on the board. */
};

#endif // BOARDFIELD_H
