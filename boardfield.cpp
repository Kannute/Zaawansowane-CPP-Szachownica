#include "boardfield.h"
#include <utils.h>
#include "constants.h"
#include <gameinterface.h>

int BoardField::defaultSize = Constants::defaultBoardFieldSize;

extern GameInterface *game;

BoardField::BoardField(QColor backgroundColor,
                       BoardPosition position,
                       QGraphicsItem *parent): QGraphicsRectItem(parent) {
    this->position = position;

    Utils::setBackgroundOnItem(backgroundColor, this);
    setPen(Qt::NoPen);
    setAcceptHoverEvents(true);
}

BoardPosition BoardField::getPosition() {
    return position;
}
