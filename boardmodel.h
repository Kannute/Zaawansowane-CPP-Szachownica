#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QPoint>
#include "boardposition.h"
#include "pawnfield.h"
#include "basepawn.h"
#include "pawninterface.h"
#include "constants.h"

/**
 * @brief The BoardModel class represents the game board model.
 */
class BoardModel {

public:
    /**
     * @brief Constructs a BoardModel object.
     */
    BoardModel();

    /**
     * @brief Gets the list of black pawns.
     *
     * @return The list of black pawns.
     */
    QList<BasePawn*> getBlackPawns();

    /**
     * @brief Gets the list of white pawns.
     *
     * @return The list of white pawns.
     */
    QList<BasePawn*> getWhitePawns();

    /**
     * @brief Gets the active pawn.
     *
     * @return The active pawn.
     */
    BasePawn* getActivePawn();

    /**
     * @brief Gets the active player.
     *
     * @return The active player.
     */
    Player getActivePlayer();

    /**
     * @brief Gets the winner of the game.
     *
     * @return The winner of the game.
     */
    Player* getWinner();

    /**
     * @brief Activates the specified pawn.
     *
     * @param pawn The pawn to activate.
     */
    void activatePawn(PawnField *pawn);

    /**
     * @brief Deactivates the active pawn.
     */
    void deactivatePawn();

    /**
     * @brief Sets the position of the active pawn.
     *
     * @param position The position to set for the active pawn.
     */
    void setActivePawnPosition(BoardPosition position);

    /**
     * @brief Gets the board position for the specified mouse position.
     *
     * @param position The mouse position.
     * @return The board position corresponding to the mouse position.
     */
    BoardPosition getBoardPositionForMousePosition(QPoint position);

    /**
     * @brief Checks if the cursor is within the board boundaries.
     *
     * @param position The cursor position.
     * @return True if the cursor is within the board boundaries, false otherwise.
     */
    bool isCursorInBoardBoundries(QPoint position);

    /**
     * @brief Validates the move of the specified pawn to the target position.
     *
     * @param positionToMove The target position to move the pawn to.
     * @param pawnToValidate The pawn to validate the move for.
     * @param requestedActivePawnPosition The requested position for the active pawn.
     * @return True if the move is valid, false otherwise.
     */
    bool validatePawnMove(BoardPosition positionToMove, BasePawn *pawnToValidate = nullptr, BoardPosition *requestedActivePawnPosition = nullptr);

    /**
     * @brief Checks if an enemy pawn was removed from the specified board position.
     *
     * @param boardPosition The board position to check.
     * @return True if an enemy pawn was removed, false otherwise.
     */
    bool didRemoveEnemyOnBoardPosition(BoardPosition boardPosition);

    /**
     * @brief Checks if the king of the specified owner is in check.
     *
     * @param owner The owner of the king to check.
     * @param isCheckingActivePlayer Flag indicating if the active player is being checked.
     * @param positionToMoveActivePlayer The position to move the active player to.
     * @return True if the king is in check, false otherwise.
     */
    bool isKingInCheck(Player owner, bool isCheckingActivePlayer, BoardPosition positionToMoveActivePlayer);

    /**
     * @brief Checks if the active pawn has been promoted.
     *
     * @return True if the active pawn has been promoted, false otherwise.
     */
    bool didPromoteActivePawn();

    /**
     * @brief Switches the round to the next player.
     */
    void switchRound();

private:
    BasePawn *activePawn; /**< The active pawn. */
    Player activePlayer; /**< The active player. */
    Player *winner; /**< The winner of the game. */

    QList<BasePawn*> blackPawns; /**< The list of black pawns. */
    QList<BasePawn*> whitePawns; /**< The list of white pawns. */

    PawnInterface pawnInterface; /**< The pawn interface. */

    /**
     * @brief Initializes the pawns on the board.
     */
    void initializePawns();

    /**
     * @brief Initializes the pawns for the specified row and owner.
     *
     * @param rowNumber The row number.
     * @param owner The owner of the pawns.
     */
    void initializePawnsForRow(int rowNumber, Player owner);

    /**
     * @brief Gets the pawn on the specified board position.
     *
     * @param baordPosition The board position.
     * @return The pawn on the specified board position.
     */
    BasePawn* getPawnOnBoardPosition(BoardPosition baordPosition);

    /**
     * @brief Checks for intersection of pawns at the specified position.
     *
     * @param positionToMove The position to move.
     * @param pawnToValidate The pawn to validate the move for.
     * @param requestedActivePawnPosition The requested position for the active pawn.
     * @return True if there is an intersection, false otherwise.
     */
    bool checkForIntersection(BoardPosition positionToMove, BasePawn *pawnToValidate, BoardPosition *requestedActivePawnPosition = nullptr);

    /**
     * @brief Checks for check condition on the board.
     *
     * @param pawns The list of pawns.
     * @param isCheckingActivePlayer Flag indicating if the active player is being checked.
     * @param king The king pawn.
     * @param positionToMoveActivePlayer The position to move the active player to.
     * @return True if there is a check condition, false otherwise.
     */
    bool checkForCheck(QList<BasePawn*> pawns, bool isCheckingActivePlayer, BasePawn *king, BoardPosition positionToMoveActivePlayer);
};

#endif // BOARDMODEL_H
