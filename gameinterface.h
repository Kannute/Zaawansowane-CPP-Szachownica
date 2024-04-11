#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "boardinterface.h"
#include "boardmodel.h"
#include "pawnfield.h"
#include "playerinterface.h"

/**
 * @brief The GameInterface class represents the main game interface.
 */
class GameInterface : public QGraphicsView {
    Q_OBJECT

public:
    /**
     * @brief Constructs a GameInterface object.
     */
    GameInterface();

    QGraphicsScene *scene; /**< The graphics scene associated with the game interface. */

    /**
     * @brief Displays the main menu of the game.
     */
    void displayMainMenu();

public slots:
    /**
     * @brief Starts the game by drawing the game board and initializing Player interfaces and navigation buttons.
     */
    void startGame();

    /**
     * @brief Quits the game.
     */
    void quitGame();

    /**
     * @brief Resets the game.
     */
    void resetGame();

    /**
     * @brief Returns to the main menu.
     */
    void mainMenu();

private:
    BoardModel boardModel; /**< The model representing the game board. */
    bool gameStarted; /**< Flag indicating whether the game has started. */
    BoardInterface *board; /**< The graphical representation of the game board. */
    PlayerInterface *blackPlayerInterface; /**< Interface for the black player. */
    PlayerInterface *whitePlayerInterface; /**< Interface for the white player. */

    /**
     * @brief Draws the game board.
     */
    void drawBoard();

    /**
     * @brief Draws the settings panel.
     */
    void drawSettingsPanel();

    /**
     * @brief Draws the user panel.
     */
    void drawUserPanel();

    /**
     * @brief Draws the user interface for the specified player.
     *
     * @param player The player for whom to draw the interface.
     * @return The player interface object.
     */
    PlayerInterface* drawUserInterface(Player player);

    /**
     * @brief Draws the title of the game.
     *
     * @param yPosition The y-coordinate position of the title.
     * @param fontSize The font size of the title.
     */
    void drawTitle(double yPosition, int fontSize);

    /**
     * @brief Draws the game details.
     */
    void drawGameDetails();

    /**
     * @brief Draws the game version.
     */
    void drawGameVersion();

    /**
     * @brief Handles the mouse press event.
     *
     * @param event The mouse press event.
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Handles the mouse move event.
     *
     * @param event The mouse move event.
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief Selects a pawn on the game board.
     *
     * @param pawn The pawn to select.
     */
    void selectPawn(PawnField *pawn);

    /**
     * @brief Handles selecting a point for the active pawn by mouse.
     *
     * @param point The point selected by the mouse.
     */
    void handleSelectingPointForActivePawnByMouse(QPoint point);

    /**
     * @brief Sets the check state on the player interface.
     *
     * @param player The player for whom to set the check state.
     * @param isInCheck Indicates whether the player is in check.
     */
    void setCheckStateOnPlayerInterface(Player player, bool isInCheck);

    /**
     * @brief Moves the active pawn to the selected point.
     *
     * @param point The selected point.
     */
    void moveActivePawnToSelectedPoint(QPoint point);

    /**
     * @brief Releases the active pawn.
     */
    void releaseActivePawn();

    /**
     * @brief Shows the winner interface.
     *
     * @param winner The winning player.
     */
    void showWinnerInterface(Player winner);
};

#endif // GAME_H
