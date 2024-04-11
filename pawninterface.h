#ifndef PAWNINTERFACE_H
#define PAWNINTERFACE_H

#include <QString>
#include "constants.h"
#include "boardposition.h"

/**
 * @brief The PawnInterface class provides utility functions related to pawns.
 */
class PawnInterface {

public:
    /**
     * @brief Constructs a PawnInterface object.
     */
    PawnInterface();

    /**
     * @brief Gets the file path to the image representing a pawn.
     *
     * @param pawnType The type of the pawn.
     * @param pawnOwner The owner of the pawn.
     * @return The file path to the image representing the pawn.
     */
    QString getImagePath(PawnType pawnType, Player pawnOwner);

    /**
     * @brief Gets the pawn type at a specified board position.
     *
     * @param position The position on the board.
     * @return The type of pawn at the specified position.
     */
    PawnType getPawnType(BoardPosition position);
};

#endif // PAWNINTERFACE_H
