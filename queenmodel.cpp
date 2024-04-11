#include "queenmodel.h"

QueenModel::QueenModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath)
    : BasePawn(pawnOwner, pawnType, position, iconPath) {}

bool QueenModel::validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition) {
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }

    if (validateDiagonalMove(targetPosition, pawnOnTargetPosition)) {
        return true;
    }

    return validateLinearMove(targetPosition, pawnOnTargetPosition);
}
