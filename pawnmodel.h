#ifndef PAWNMODEL_H
#define PAWNMODEL_H

#include "basepawn.h"

/**
 * @brief The PawnModel class represents a pawn on the game board.
 */
class PawnModel: public BasePawn {

private:
    bool pawnMoved; ///< Flag to track whether the pawn has moved.

public:
    /**
     * @brief Constructs a PawnModel object with specified attributes.
     *
     * @param pawnOwner The player who owns the pawn.
     * @param pawnType The type of the pawn.
     * @param position The position of the pawn on the board.
     * @param iconPath The file path to the image representing the pawn.
     */
    PawnModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath);

    /**
     * @brief Checks if the pawn has moved.
     *
     * @return True if the pawn has moved, false otherwise.
     */
    bool didPawnMove();

    /**
     * @brief Validates a move for the pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    bool validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition);
};

#endif // PAWNMODEL_H
