#include "rookmodel.h"

RookModel::RookModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath)
    : BasePawn(pawnOwner, pawnType, position, iconPath) {}

bool RookModel::validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition) {
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }

    return validateLinearMove(targetPosition, pawnOnTargetPosition);
}
