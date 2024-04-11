#ifndef WINNERINTERFACE_H
#define WINNERINTERFACE_H

#include <QGraphicsRectItem>
#include "constants.h"

/**
 * @brief The WinnerInterface class represents the interface displayed when a player wins the game.
 */
class WinnerInterface: public QObject, public QGraphicsRectItem {
    Q_OBJECT

public:
    /**
     * @brief Constructs a WinnerInterface object with the specified winner and displays in the game interface.
     *
     * @param winner The player who won the game.
     */
    WinnerInterface(Player winner);
};

#endif // WINNERINTERFACE_H
