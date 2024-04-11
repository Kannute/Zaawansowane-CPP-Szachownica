#include "pawnmodel.h"

PawnModel::PawnModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath)
    : BasePawn(pawnOwner, pawnType, position, iconPath) {
    this->pawnMoved = false;
}

bool PawnModel::didPawnMove() {
    /**
     * @brief Checks if the pawn has moved.
     *
     * @return True if the pawn has moved, false otherwise.
     */
    return this->pawnMoved;
}

bool PawnModel::validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition) {
    /**
     * @brief Validates a move for the pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }

    int xDifference = targetPosition.x - this->position.x;
    int yDifference = targetPosition.y - this->position.y;

    bool wantsToMoveByOneField = std::max(abs(xDifference), abs(yDifference)) == 1;
    // BoardPosition *temp_position = this->getBoardPosition();

    if (abs(xDifference) > 1 || abs(yDifference) > 2) {
        return false;
    }

    if (!wantsToMoveByOneField && this->didPawnMove()) {
        return false;
    }

    bool wantsToMoveInGoodDirection;

    switch (this->getPawnOwner()) {
        case Player::black:
            wantsToMoveInGoodDirection = yDifference > 0;
            break;
        case Player::white:
            wantsToMoveInGoodDirection = yDifference < 0;
            break;
    }

    if (wantsToMoveByOneField) {
        if (requestedActivePawnPosition && xDifference == 0)  {
            return (wantsToMoveInGoodDirection &&
                    requestedActivePawnPosition->x != targetPosition.x &&
                    requestedActivePawnPosition->y != targetPosition.y);
        } else if (xDifference == 0) {
            return (wantsToMoveInGoodDirection && !pawnOnTargetPosition);
        } else if (requestedActivePawnPosition) {
            return (wantsToMoveInGoodDirection &&
                    requestedActivePawnPosition->x == targetPosition.x &&
                    requestedActivePawnPosition->y == targetPosition.y) || (wantsToMoveInGoodDirection && pawnOnTargetPosition);
        } else {
            return (wantsToMoveInGoodDirection && pawnOnTargetPosition);
        }
    }

    return (wantsToMoveInGoodDirection &&
            !this->didPawnMove() &&
            xDifference == 0);
}
