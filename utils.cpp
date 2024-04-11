#include "utils.h"
#include <QBrush>
#include <QLabel>
#include <QGraphicsProxyWidget>

QGraphicsTextItem* Utils::createTextItem(QString title, int fontSize, QColor textColor, QGraphicsItem *parent) {
    QGraphicsTextItem *textItem = new QGraphicsTextItem(title, parent);
    QFont titleFont("arial", fontSize);
    textItem->setDefaultTextColor(textColor);
    textItem->setFont(titleFont);

    return textItem;
}


void Utils::setBackgroundOnItem(QColor color, QAbstractGraphicsShapeItem *item) {
    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    brush.setColor(color);
    item->setBrush(brush);
}

void Utils::setProxyWidget(QString imagePath, QGraphicsRectItem *rectItem) {
    QPixmap pixelMap(imagePath);
    QLabel *image = new QLabel();
    QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget(rectItem);
    image->setPixmap(pixelMap);
    proxyWidget->setWidget(image);
}
