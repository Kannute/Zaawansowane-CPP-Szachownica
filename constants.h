#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>
#include <QBrush>
#include <QString>

/**
 * @brief The Player enum represents the players in the game.
 */
enum class Player {
    black, /**< Black player. */
    white /**< White player. */
};

/**
 * @brief The PawnType enum represents the types of pawns in the game.
 */
enum class PawnType {
    king, /**< King pawn. */
    queen, /**< Queen pawn. */
    rook, /**< Rook pawn. */
    bishop, /**< Bishop pawn. */
    knight, /**< Knight pawn. */
    pawn /**< Regular pawn. */
};

/**
 * @brief The Constants class contains various constants used in the game.
 */
class Constants {

public:
    static int defaultMargin; /**< Default margin value. */
    static int defaultBoardFieldSize; /**< Default size of the board field. */
    static int defaultBoardSize; /**< Default size of the game board. */
    static int gameInterfaceHeight; /**< Height of the game interface. */
    static int gameInterfaceWidth; /**< Width of the game interface. */
    static int fontSizeSmall; /**< Font size for small text. */
    static int fontSizeMedium; /**< Font size for medium text. */
    static int fontSizeLarge; /**< Font size for large text. */
    static QColor red; /**< Red color. */
    static QColor white; /**< White color. */
    static QColor boardBorderFieldBackground; /**< Background color for board border fields. */
    static QColor activePlayerBorder; /**< Border color for the active player. */
    static QColor defaultPlayerBorder; /**< Default border color for players. */
    static QColor defaultTextColor; /**< Default text color. */
    static QColor defaultButtonColor; /**< Default button color. */
    static QColor defaultButtonColorHover; /**< Button color on hover. */
    static QColor defaultButtonTextColor; /**< Text color for buttons. */
    static QColor boardFieldLightColor; /**< Light color for board fields. */
    static QColor boardFieldDarkColor; /**< Dark color for board fields. */
    static Player startingPlayer; /**< Starting player of the game. */
    static QString gameInterfaceTitle; /**< Title of the game interface. */
    static QString gameInterfaceDetails; /**< Details of the game interface. */
    static QString boardBorderItemsVertical; /**< Vertical border items. */
    static QString boardBorderItemsHorizontal; /**< Horizontal border items. */

    /**
     * @brief Gets the background brush for the game interface.
     *
     * @return The background brush for the game interface.
     */
    static QBrush getGameInterfaceBackgroundBrush();

};

#endif // CONSTANTS_H
