#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H

#include <QGraphicsRectItem>
#include <QList>
#include <QPoint>
#include "boardfield.h"
#include "pawnfield.h"
#include "basepawn.h"

/**
 * @brief The BoardInterface class represents the graphical interface of the game board.
 */
class BoardInterface: public QGraphicsRectItem {
public:
    /**
     * @brief Constructs a BoardInterface object.
     */
    BoardInterface();

    static int boardSize; /**< The size of the game board. */
    static int boardXPosition; /**< The x-coordinate position of the game board. */
    static int boardYPosition; /**< The y-coordinate position of the game board. */

    /**
     * @brief Gets the list of board fields.
     *
     * @return The list of board fields.
     */
    QList<BoardField*> getFields();

    /**
     * @brief Draws the game board.
     */
    void drawBoard();

    /**
     * @brief Initializes pawn fields on the board.
     *
     * @param pawns The list of pawns to initialize on the board.
     */
    void initializePawnFields(QList<BasePawn*> pawns);

    /**
     * @brief Gets the pawn at the specified board position.
     *
     * @param boardPosition The position on the board to check for a pawn.
     * @return The pawn field at the specified position, or nullptr if no pawn is found.
     */
    PawnField* getPawnAtBoardPosition(BoardPosition boardPosition);

    /**
     * @brief Gets the pawn at the specified mouse position.
     *
     * @param point The mouse position to check for a pawn.
     * @return The pawn field at the specified mouse position, or nullptr if no pawn is found.
     */
    PawnField* getPawnAtMousePosition(QPoint point);

    /**
     * @brief Moves the active pawn to the specified mouse position.
     *
     * @param point The mouse position where the active pawn is moved.
     * @param pawn The active pawn to move.
     */
    void moveActivePawnToMousePosition(QPoint point, BasePawn *pawn);

    /**
     * @brief Places the specified pawn at the specified board position.
     *
     * @param pawn The pawn to place.
     * @param boardPosition The board position where the pawn is placed.
     */
    void placeActivePawnAtBoardPosition(BasePawn *pawn, BoardPosition boardPosition);

    /**
     * @brief Removes the pawn at the specified board position.
     *
     * @param boardPosition The board position where the pawn is removed.
     */
    void removePawnAtBoardPosition(BoardPosition boardPosition);

    /**
     * @brief Promotes the pawn at the specified board position.
     *
     * @param boardPosition The board position of the pawn to promote.
     */
    void promotePawnAtBoardPosition(BoardPosition boardPosition);

private:
    QList<BoardField*> fields; /**< The list of board fields. */
    QList<PawnField*> pawns; /**< The list of pawn fields. */
    QGraphicsTextItem *checkWarningTitleTextItem; /**< The title text item for pawn move check warning. */
    QGraphicsTextItem *checkWarningDescriptionTextItem; /**< The description text item for pawn move check warning. */

    /**
     * @brief Creates a column of board fields at the specified position.
     *
     * @param xPosition The x-coordinate position of the column.
     * @param columnNumber The number of the column.
     */
    void createFieldsColumn(int xPosition, int columnNumber);

    /**
     * @brief Draws the board fields.
     */
    void drawBoardFields();

    /**
     * @brief Draws the frame of the game board.
     */
    void drawBoardFrame();

    /**
     * @brief Draws the frame of the game board at the specified position with a title.
     *
     * @param point The position to draw the frame.
     * @param rect The bounding rectangle of the frame.
     * @param title The title of the frame.
     */
    void drawBoardFrameAtPosition(QPoint point, QRectF rect, QString title);


    /**
     * @brief Gets the coordinates for the specified board position.
     *
     * @param position The board position to get coordinates for.
     * @return The coordinates for the specified board position.
     */
    QPointF getCoordinatesForBoardPosition(BoardPosition position);
};

#endif // BOARDINTERFACE_H
