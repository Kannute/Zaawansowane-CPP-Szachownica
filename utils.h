#ifndef UTILS_H
#define UTILS_H

#include <QAbstractGraphicsShapeItem>
#include <QColor>
#include <QGraphicsTextItem>

/**
 * @brief The Utils class provides utility functions for graphical items.
 */
class Utils {

public:
    /**
     * @brief Sets the background color of a graphical shape item.
     *
     * @param color The color to set as the background.
     * @param item The graphical shape item whose background color is to be set.
     */
    static void setBackgroundOnItem(QColor color, QAbstractGraphicsShapeItem *item);

    /**
     * @brief Sets the image for a graphical rectangle item.
     *
     * @param imagePath The file path to the image to be set.
     * @param item The graphical rectangle item to which the image is to be set.
     */
    static void setProxyWidget(QString imagePath, QGraphicsRectItem *item);

    /**
     * @brief Creates a QGraphicsTextItem with specified attributes.
     *
     * @param title The text content of the item.
     * @param fontSize The font size of the text.
     * @param textColor The color of the text.
     * @param parent The parent item of the created text item.
     * @return A pointer to the created QGraphicsTextItem.
     */
    static QGraphicsTextItem* createTextItem(QString title, int fontSize, QColor textColor, QGraphicsItem *parent = nullptr);
};

#endif // UTILS_H
