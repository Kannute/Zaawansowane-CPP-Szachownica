#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>

/**
 * @brief The Button class represents a clickable button in a QGraphicsScene.
 */
class Button: public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    /**
     * @brief Constructs a Button object with the specified title.
     *
     * @param title The title of the button.
     */
    Button(QString title);

    /**
     * @brief Handles the mouse press event for the button.
     *
     * @param event The QGraphicsSceneMouseEvent object representing the mouse press event.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Handles the hover enter event for the button.
     *
     * @param event The QGraphicsSceneHoverEvent object representing the hover enter event.
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    /**
     * @brief Handles the hover leave event for the button.
     *
     * @param event The QGraphicsSceneHoverEvent object representing the hover leave event.
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    /**
     * @brief Signal emitted when the button is pressed.
     */
    void buttonPressed();

};

#endif // BUTTON_H
