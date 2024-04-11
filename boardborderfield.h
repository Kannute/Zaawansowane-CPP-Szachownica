#ifndef BOARDBORDERFIELD_H
#define BOARDBORDERFIELD_H

#include <QGraphicsRectItem>

/**
 * @brief The BoardBorderField class represents a border field on the game board.
 */
class BoardBorderField: public QGraphicsRectItem  {
public:
    /**
     * @brief Constructs a BoardBorderField object with specified attributes.
     *
     * @param point The position of the field.
     * @param rect The bounding rectangle of the field.
     * @param text The text to be displayed on the field.
     * @param parent The parent graphics item, default is nullptr.
     */
    BoardBorderField(QPoint point, QRectF rect, QString text, QGraphicsItem *parent = nullptr);

private:
    QString text; /**< The text to be displayed on the field. */

    /**
     * @brief Writes the text on the field.
     */
    void writeText();

    /**
     * @brief Sets the background color of the field.
     *
     * @param backgroundColor The color to set as background.
     */
    void setBackground(QColor backgroundColor);
};

#endif // BOARDBORDERFIELD_H
