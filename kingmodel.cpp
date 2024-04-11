#include "kingmodel.h"

KingModel::KingModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath)
    : BasePawn(pawnOwner, pawnType, position, iconPath) {}

bool KingModel::validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition) {
    /**
     * @brief Validates a move for the king pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }

    return validateOneFieldMove(targetPosition);
}
