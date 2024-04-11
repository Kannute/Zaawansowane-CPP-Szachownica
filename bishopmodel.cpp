#include "bishopmodel.h"

BishopModel::BishopModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath): BasePawn (pawnOwner, pawnType, position, iconPath) {}

bool BishopModel::validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition) {
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }
    return validateDiagonalMove(targetPosition, pawnOnTargetPosition);
}
