#include "constants.h"

int Constants::defaultMargin = 30;
int Constants::defaultBoardFieldSize = 60;
int Constants::defaultBoardSize = 8;
int Constants::gameInterfaceHeight = 800;
int Constants::gameInterfaceWidth = 1200;
int Constants::fontSizeSmall = 10;
int Constants::fontSizeMedium = 20;
int Constants::fontSizeLarge = 30;
QColor Constants::white = QColor( 255, 255, 255 );
QColor Constants::red = QColor( 255, 0, 0 );
QColor Constants::boardBorderFieldBackground = QColor(  163, 193, 159 );
QColor Constants::defaultTextColor = QColor(157, 128, 101);
QColor Constants::defaultButtonColor =  QColor(247, 237, 188);
QColor Constants::defaultButtonColorHover = QColor(230, 253, 251);
QColor Constants::defaultButtonTextColor = QColor(44, 41, 51);
QColor Constants::activePlayerBorder = QColor(154, 255, 146);
QColor Constants::defaultPlayerBorder = QColor(183, 183, 183);
QColor Constants::boardFieldLightColor = QColor( 235, 216, 211 );
QColor Constants::boardFieldDarkColor = QColor(149, 149, 149);
Player Constants::startingPlayer = Player::white;
QString Constants::gameInterfaceTitle = "Szachownica - Chess";
QString Constants::gameInterfaceDetails = "Politechnika Warszawska\nKacper Łuka\nZaawansowane C++";

QString Constants::boardBorderItemsHorizontal = "ABCDEFGH";
QString Constants::boardBorderItemsVertical = "12345678";


QBrush Constants::getGameInterfaceBackgroundBrush() {
    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    QColor color = QColor( 165, 203, 219 );
    brush.setColor(color);

    return brush;
}
