#include "boardborderfield.h"
#include "constants.h"
#include "utils.h"
#include "gameinterface.h"
#include <QFont>

extern GameInterface *game;

BoardBorderField::BoardBorderField(QPoint point, QRectF rect, QString text, QGraphicsItem *parent) {
    this->setParentItem(parent);
    this->setPos(point);
    this->setRect(rect);
    this->text = text;
    this->setBackground(Constants::boardBorderFieldBackground);
    this->writeText();
}

void BoardBorderField::writeText() {
    QGraphicsTextItem *titleItem = Utils::createTextItem(this->text, Constants::fontSizeSmall, Constants::white);

    double textX = this->pos().x() + this->boundingRect().width()/2 - titleItem->boundingRect().width()/2;
    double textY = this->pos().y() + this->boundingRect().height()/2 - titleItem->boundingRect().height()/2;;

    titleItem->setPos(textX, textY);

    game->scene->addItem(titleItem);
}

void BoardBorderField::setBackground(QColor backgroundColor) {
    Utils::setBackgroundOnItem(backgroundColor, this);
    setPen(Qt::NoPen);
}
