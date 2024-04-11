#include "button.h"
#include "constants.h"
#include "utils.h"

#include <QBrush>
#include <QGraphicsRectItem>
#include <QFont>

/**
 * @brief Constructs an ActionButton with the specified title.
 *
 * @param title The title to be displayed on the button.
 */
Button::Button(QString title) {
    // Set the initial size of the button
    setRect(0, 0, 200, 50);

    // Set the background color of the button
    QColor backgroundColor = Constants::defaultButtonColor;
    Utils::setBackgroundOnItem(backgroundColor, this);

    // Set the text color of the button
    QColor textColor = Constants::defaultButtonTextColor;

    // Create text item to display the title
    QGraphicsTextItem *text = Utils::createTextItem(title, 20, textColor, this);

    // Calculate the position to center the text item within the button
    double xPosition = rect().width()/2 - text->boundingRect().width()/2;
    double yPosition = rect().height()/2 - text->boundingRect().height()/2;

    // Set the position of the text item
    text->setPos(xPosition, yPosition);

    // Allow the button to respond to hover events
    setAcceptHoverEvents(true);
}

/**
 * @brief Handles the mouse press event for the button. Emits buttonPressed() signal.
 *
 * @param event The mouse press event.
 */
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit buttonPressed();
}

/**
 * @brief Handles the hover enter event for the button. Dims the background color
 *
 * @param event The hover enter event.
 */
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    QColor backgroundColor = Constants::defaultButtonColorHover;
    Utils::setBackgroundOnItem(backgroundColor, this);
}

/**
 * @brief Handles the hover leave event for the button. Restores the background color back to the default one
 *
 * @param event The hover leave event.
 */
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    QColor backgroundColor = Constants::defaultButtonColor;
    Utils::setBackgroundOnItem(backgroundColor, this);
}
