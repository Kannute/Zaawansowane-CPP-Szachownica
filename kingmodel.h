#ifndef KINGMODEL_H
#define KINGMODEL_H

#include "basepawn.h"

/**
 * @brief The KingModel class represents a king pawn on the game board.
 */
class KingModel: public BasePawn {

public:
    /**
     * @brief Constructs a KingModel object with specified attributes.
     *
     * @param pawnOwner The player who owns the pawn.
     * @param pawnType The type of the pawn.
     * @param position The position of the pawn on the board.
     * @param iconPath The file path to the image representing the pawn.
     */
    KingModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath);

    /**
     * @brief Validates a move for the king pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    bool validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition);
};

#endif // KINGMODEL_H
