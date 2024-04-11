#ifndef QUEENMODEL_H
#define QUEENMODEL_H

#include "basepawn.h"

/**
 * @brief The QueenModel class represents a queen pawn on the game board.
 */
class QueenModel: public BasePawn {

public:
    /**
     * @brief Constructs a QueenModel object with specified attributes.
     *
     * @param pawnOwner The player who owns the queen pawn.
     * @param pawnType The type of the pawn.
     * @param position The position of the pawn on the board.
     * @param iconPath The file path to the image representing the pawn.
     */
    QueenModel(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath);

    /**
     * @brief Validates a move for the queen pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition Pawn on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    bool validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition);
};

#endif // QUEENMODEL_H
