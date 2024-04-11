#include "knightmodel.h"

KnightModel::KnightModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath)
    : BasePawn(pawnOwner, pawnType, position, iconPath) {}

bool KnightModel::validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition) {
    /**
     * @brief Validates a move for the knight pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }

    int xDifference = abs(targetPosition.x - this->position.x);
    int yDifference = abs(targetPosition.y - this->position.y);

    // Check if the move is L-shaped (either 2 squares in one direction and 1 in the other, or vice versa)
    if ((xDifference == 2 && yDifference == 1) || (xDifference == 1 && yDifference == 2)) {
        return true;
    }

    return false;
}
