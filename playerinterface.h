#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include "constants.h"

/**
 * @brief The PlayerInterface class represents the interface for a player in the game.
 */
class PlayerInterface: public QGraphicsRectItem  {

public:
    /**
     * @brief Constructs a PlayerInterface object.
     *
     * @param parent The parent graphics item.
     */
    PlayerInterface(QGraphicsItem *parent = nullptr);

    static int defaultHeight; /**< The default height of the player interface. */
    static int defaultWidth; /**< The default width of the player interface. */

    /**
     * @brief Sets the owner of the player interface.
     *
     * @param owner The owner of the player interface.
     */
    void setPlayer(Player owner);

    /**
     * @brief Sets whether the player interface is active.
     *
     * @param active True if the player interface is active, false otherwise.
     */
    void setActive(bool active);

    /**
     * @brief Sets whether the player is in check.
     *
     * @param isCheck True if the player is in check, false otherwise.
     */
    void setIsInCheck(bool isCheck);

private:
    QGraphicsTextItem *checkText; /**< The text indicating if the player is in check. */
};

#endif // PLAYERINTERFACE_H
