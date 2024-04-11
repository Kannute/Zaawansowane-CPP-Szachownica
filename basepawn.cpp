#include "basepawn.h"

BasePawn::BasePawn(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath) {
    this->position = position;
    this->pawnOwner = pawnOwner;
    this->pawnType = pawnType;
    this->iconPath = iconPath;
    this->firstMoveTaken = false;
}

Player BasePawn::getPawnOwner() {
    return this->pawnOwner;
}

BoardPosition BasePawn::getBoardPosition(){
    return this->position;
}

QString BasePawn::getIconPath(){
    return this->iconPath;
}

PawnType BasePawn::getPawnType(){
    return this->pawnType;
}

void BasePawn::setPawnType(PawnType pawnType) {
    this->pawnType = pawnType;
}

void BasePawn::setBoardPosition(BoardPosition targetPosition) {
    this->position = targetPosition;
}

bool BasePawn::willMoveIntoOwnPawn(BasePawn *pawnOnTargetPosition) {
    if (pawnOnTargetPosition)
        return pawnOnTargetPosition->pawnOwner == this->pawnOwner;
    return false;

}

bool BasePawn::validateOneFieldMove(BoardPosition positionToMove) {
    /**
     * @brief Validates if the pawn can move to the specified position within one field.
     *
     * @param positionToMove The position to move the pawn to.
     * @return True if the move is valid within one field, false otherwise.
     */
    int xDifference = positionToMove.x - this->position.x;
    int yDifference = positionToMove.y - this->position.y;
    return (std::max(abs(xDifference), abs(yDifference)) == 1);
}

bool BasePawn::validateDiagonalMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition) {
    /**
     * @brief Validates a diagonal move for the pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @return True if the diagonal move is valid, false otherwise.
     */
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }

    int xDifference = targetPosition.x - this->position.x;
    int yDifference = targetPosition.y - this->position.y;

    if (abs(xDifference) != abs(yDifference)) {
        return false;
    }

    return true;
}

bool BasePawn::validateLinearMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition) {
    /**
     * @brief Validates a linear move for the pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @return True if the linear move is valid, false otherwise.
     */
    if (this->willMoveIntoOwnPawn(pawnOnTargetPosition)) {
        return false;
    }

    if ((targetPosition.x != this->position.x && targetPosition.y != this->position.y)) {
        return false;
    }

    return true;
}
