#ifndef KNIGHTMODEL_H
#define KNIGHTMODEL_H

#include "basepawn.h"

/**
 * @brief The KnightModel class represents a knight pawn on the game board.
 */
class KnightModel: public BasePawn {

public:
    /**
     * @brief Constructs a KnightModel object with specified attributes.
     *
     * @param pawnOwner The player who owns the pawn.
     * @param pawnType The type of the pawn.
     * @param position The position of the pawn on the board.
     * @param iconPath The file path to the image representing the pawn.
     */
    KnightModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath);

    /**
     * @brief Validates a move for the knight pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    bool validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition);
};

#endif // KNIGHTMODEL_H
