#include "playerinterface.h"
#include <QObject>
#include <QFont>
#include "constants.h"
#include "gameinterface.h"
#include "utils.h"

int PlayerInterface::defaultHeight = 50;
int PlayerInterface::defaultWidth = 200;

extern GameInterface *game;

PlayerInterface::PlayerInterface(QGraphicsItem *parent): QGraphicsRectItem(parent) {
    QColor backgroundColor = Constants::white;
    Utils::setBackgroundOnItem(backgroundColor, this);
    setPen(Qt::NoPen);
}

void PlayerInterface::setPlayer(Player owner) {
    QString title = Player::black == owner ? "Black" : "White";
    QString imagePath = Player::black == owner ? ":Images/pawn_black.svg" : ":Images/pawn_white.svg";

    QGraphicsTextItem *titleItem = Utils::createTextItem(title, Constants::fontSizeMedium, Constants::defaultTextColor, this);

    double titleXPosition = this->boundingRect().x();
    double titleYPosition = this->boundingRect().y();
    titleItem->setPos(titleXPosition, titleYPosition);

    checkText = Utils::createTextItem("CHECK", Constants::fontSizeMedium, Constants::red, this);

    double checkXPosition = this->boundingRect().x() + this->boundingRect().width()/2;
    double checkYPosition = this->boundingRect().y();

    checkText->setPos(checkXPosition, checkYPosition);
    checkText->setOpacity(0);
}

void PlayerInterface::setActive(bool active) {
    QColor borderColor = active ? Constants::activePlayerBorder : Constants::defaultPlayerBorder;
    QPen pen(borderColor, 5);
    setPen(pen);
}

void PlayerInterface::setIsInCheck(bool isCheck) {
    checkText->setOpacity(isCheck ? 1 : 0);
}
