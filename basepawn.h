#ifndef BASEPAWN_H
#define BASEPAWN_H

#include <QString>
#include "boardposition.h"
#include "constants.h"

/**
 * @brief The BasePawn class represents a generic pawn on the game board.
 */
class BasePawn {
public:
    bool firstMoveTaken; /**< Represents whether the first move of the pawn has been taken. */

    /**
     * @brief Constructs a BasePawn object with specified attributes.
     *
     * @param pawnOwner The player who owns the pawn.
     * @param pawnType The type of the pawn.
     * @param position The position of the pawn on the board.
     * @param iconPath The file path to the image representing the pawn.
     */
    BasePawn(Player pawnOwner, PawnType pawnType, BoardPosition position, QString iconPath);

    /**
     * @brief Validates a move for the pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition Pawn on the target position.
     * @param requestedActivePawnPosition The position requested by the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    virtual bool validateMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition, BoardPosition *requestedActivePawnPosition) = 0;

    void setBoardPosition(BoardPosition targetPosition);
    void setPawnType(PawnType pawnType);

    BoardPosition getBoardPosition();
    Player getPawnOwner();
    PawnType getPawnType();
    QString getIconPath();

    /**
     * @brief Virtual destructor for BasePawn.
     */
    virtual ~BasePawn() = default;

protected:
    /**
     * @brief Checks if moving the pawn to the target position will cause it to collide with another pawn owned by the same player.
     *
     * @param pawnOnTargetPosition The pawn on the target position.
     * @return True if the move will collide with another pawn owned by the same player, false otherwise.
     */
    bool willMoveIntoOwnPawn(BasePawn *pawnOnTargetPosition);

    /**
     * @brief Validates a move where the pawn moves only one field.
     *
     * @param targetPosition The target position to move the pawn to.
     * @return True if the move is valid, false otherwise.
     */
    bool validateOneFieldMove(BoardPosition targetPosition);

    /**
     * @brief Validates a diagonal move for the pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @return True if the diagonal move is valid, false otherwise.
     */
    bool validateDiagonalMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition);

    /**
     * @brief Validates a linear move for the pawn.
     *
     * @param targetPosition The target position to move the pawn to.
     * @param pawnOnTargetPosition The pawn currently on the target position.
     * @return True if the linear move is valid, false otherwise.
     */
    bool validateLinearMove(BoardPosition targetPosition, BasePawn *pawnOnTargetPosition);


protected:
    BoardPosition position; /**< The position of the pawn on the board. */
    Player pawnOwner; /**< The player who owns the pawn. */
    PawnType pawnType; /**< The type of the pawn. */
    QString iconPath; /**< The file path to the image representing the pawn. */
};

#endif // BASEPAWN_H
