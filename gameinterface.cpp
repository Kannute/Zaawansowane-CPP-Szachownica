#include "GameInterface.h"
#include <QGraphicsTextItem>
#include <QColor>
#include <QBrush>
#include "button.h"
#include "winnerinterface.h"
#include "constants.h"
#include "utils.h"


GameInterface::GameInterface() {

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(Constants::gameInterfaceWidth, Constants::gameInterfaceHeight);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, Constants::gameInterfaceWidth, Constants::gameInterfaceHeight);
    setScene(scene);

    scene->setBackgroundBrush(Constants::getGameInterfaceBackgroundBrush());

    gameStarted = false;
}


void GameInterface::displayMainMenu() {
    // create title label
    double titleYPosition = 150;
    drawTitle(titleYPosition, 50);
    drawGameDetails();
    drawGameVersion();

    // create start button
    Button *startButton = new Button("Start Game");
    double buttonXPosition = this->width()/2 - startButton->boundingRect().width()/2;
    double buttonYPosition = 275;
    startButton->setPos(buttonXPosition, buttonYPosition);

    connect(startButton, SIGNAL(buttonPressed()), this, SLOT(startGame()));
    scene->addItem(startButton);

    // create quit button
    Button *quitButton = new Button("Quit");
    double quitXPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    double quitYPosition = 350;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitGame()));
    scene->addItem(quitButton);
}

void GameInterface::startGame() {

    scene->clear();

    boardModel = BoardModel();

    drawBoard();
    drawSettingsPanel();
    drawUserPanel();
    drawGameDetails();
    drawGameVersion();
    drawTitle(Constants::defaultMargin, Constants::fontSizeLarge);
    gameStarted = true;
}

void GameInterface::quitGame() {
    close();
}

void GameInterface::resetGame() {
    gameStarted = false;
    scene->clear();
    startGame();
}

void GameInterface::mainMenu() {
    gameStarted = false;
    scene->clear();
    displayMainMenu();
}

void GameInterface::drawBoard() {
    board = new BoardInterface();
    board->drawBoard();
    board->initializePawnFields(boardModel.getBlackPawns());
    board->initializePawnFields(boardModel.getWhitePawns());
}

void GameInterface::drawSettingsPanel() {
    // create quit button
    Button *resetButton = new Button("Reset game");
    double resetXPosition = 0.33 * Constants::gameInterfaceWidth - resetButton->boundingRect().width();
    double resetYPosition = Constants::gameInterfaceHeight - resetButton->boundingRect().height()*2;
    resetButton->setPos(resetXPosition, resetYPosition);

    connect(resetButton, SIGNAL(buttonPressed()), this, SLOT(resetGame()));
    scene->addItem(resetButton);

    // create quit button
    Button *quitButton = new Button("Quit game");
    double quitXPosition = 0.5 * Constants::gameInterfaceWidth - resetButton->boundingRect().width()/2;
    double quitYPosition = Constants::gameInterfaceHeight - quitButton->boundingRect().height()*2;
    quitButton->setPos(quitXPosition, quitYPosition);

    connect(quitButton, SIGNAL(buttonPressed()), this, SLOT(quitGame()));
    scene->addItem(quitButton);

    // create quit button
    Button *mainMenuButton = new Button("Main Menu");
    double mainMenuXPosition = 0.66 * Constants::gameInterfaceWidth;
    double mainMenuYPosition = Constants::gameInterfaceHeight - mainMenuButton->boundingRect().height()*2;;
    mainMenuButton->setPos(mainMenuXPosition, mainMenuYPosition);

    connect(mainMenuButton, SIGNAL(buttonPressed()), this, SLOT(mainMenu()));
    scene->addItem(mainMenuButton);
}

void GameInterface::drawUserPanel() {
    blackPlayerInterface = drawUserInterface(Player::black);
    whitePlayerInterface = drawUserInterface(Player::white);
    whitePlayerInterface->setActive(true);
}

PlayerInterface* GameInterface::drawUserInterface(Player player) {
    PlayerInterface *playerInterface = new PlayerInterface();

    int xPosition = BoardInterface::boardXPosition - 1.2 * PlayerInterface::defaultWidth;
    int yPosition = BoardInterface::boardYPosition;

    switch (player) {
        case Player::white:
            yPosition += 1.2*PlayerInterface::defaultHeight;
            break;
        case Player::black:
            yPosition += 1.2*PlayerInterface::defaultHeight*2;
            break;
    }

    scene->addItem(playerInterface);
    playerInterface->setRect(xPosition, yPosition, PlayerInterface::defaultWidth, PlayerInterface::defaultHeight);
    playerInterface->setPlayer(player);

    return playerInterface;
}

void GameInterface::drawTitle(double yPosition, int fontSize) {
    QGraphicsTextItem *title = Utils::createTextItem(Constants::gameInterfaceTitle, fontSize, Qt::white);
    double xPosition = this->width()/2 - title->boundingRect().width()/2;
    title->setPos(xPosition, yPosition);
    scene->addItem(title);
}

void GameInterface::drawGameDetails() {
    QGraphicsTextItem *title = Utils::createTextItem(Constants::gameInterfaceDetails, 10, Qt::white);
    double xPosition = this->width() - title->boundingRect().width();
    title->setPos(xPosition, Constants::gameInterfaceHeight-60);
    scene->addItem(title);
}

void GameInterface::drawGameVersion() {
    QGraphicsTextItem *title = Utils::createTextItem("Game Version: 1.0", 10, Qt::white);
    title->setPos(0, Constants::gameInterfaceHeight-30);
    scene->addItem(title);
}

void GameInterface::mousePressEvent(QMouseEvent *event) {
    if (!gameStarted) {
        QGraphicsView::mousePressEvent(event);
        return;
    } else if (event->button() == Qt::RightButton) {
        releaseActivePawn();
    } else if (boardModel.getActivePawn()) {
        handleSelectingPointForActivePawnByMouse(event->pos());
    } else {
        PawnField *pawn = board->getPawnAtMousePosition(event->pos());
        selectPawn(pawn);
    }

    QGraphicsView::mousePressEvent(event);
}

void GameInterface::mouseMoveEvent(QMouseEvent *event) {
    if (gameStarted && boardModel.getActivePawn()) {
        board->moveActivePawnToMousePosition(event->pos(), boardModel.getActivePawn());
    }

    QGraphicsView::mouseMoveEvent(event);
}


void GameInterface::selectPawn(PawnField *pawn) {
    if (!pawn) {
        return;
    }
    boardModel.activatePawn(pawn);
}

void GameInterface::handleSelectingPointForActivePawnByMouse(QPoint point) {
    if (!boardModel.getActivePawn()) {
        return;
    }

    if (!boardModel.isCursorInBoardBoundries(point)) {
        return;
    }

    BoardPosition boardPosition = boardModel.getBoardPositionForMousePosition(point);

    if (!boardModel.validatePawnMove(boardPosition)) {
        return;
    }

    bool isKingInCheck = boardModel.isKingInCheck(boardModel.getActivePawn()->getPawnOwner(), true, boardPosition);

    if (boardModel.didRemoveEnemyOnBoardPosition(boardPosition)) {
        board->removePawnAtBoardPosition(boardPosition);
    }

    moveActivePawnToSelectedPoint(point);

    if (boardModel.didPromoteActivePawn()) {
        board->promotePawnAtBoardPosition(boardPosition);
    }

    switch (boardModel.getActivePawn()->getPawnOwner()) {
        case Player::black:
            setCheckStateOnPlayerInterface(Player::white, boardModel.isKingInCheck(Player::white, false, boardPosition));
            break;
        case Player::white:
            setCheckStateOnPlayerInterface(Player::black, boardModel.isKingInCheck(Player::black, false, boardPosition));
            break;
    }

    setCheckStateOnPlayerInterface(boardModel.getActivePawn()->getPawnOwner(), isKingInCheck);

    if (boardModel.getWinner()) {
        showWinnerInterface(*boardModel.getWinner());
        return;
    }

    boardModel.deactivatePawn();
    boardModel.switchRound();
    blackPlayerInterface->setActive(boardModel.getActivePlayer() == Player::black);
    whitePlayerInterface->setActive(boardModel.getActivePlayer() == Player::white);
}

void GameInterface::setCheckStateOnPlayerInterface(Player player, bool isInCheck) {
    switch (player) {
    case Player::black:
        blackPlayerInterface->setIsInCheck(isInCheck);
        break;
    case Player::white:
        whitePlayerInterface->setIsInCheck(isInCheck);
        break;
    }
}

// update pawn field position and pawn model position
void GameInterface::moveActivePawnToSelectedPoint(QPoint point) {
    BoardPosition boardPosition = boardModel.getBoardPositionForMousePosition(point);
    board->placeActivePawnAtBoardPosition(boardModel.getActivePawn(), boardPosition);
    boardModel.setActivePawnPosition(boardPosition);
}

void GameInterface::releaseActivePawn() {
    if (boardModel.getActivePawn() == nullptr) {
        return;
    }

    BasePawn *activePawn = boardModel.getActivePawn();
    board->placeActivePawnAtBoardPosition(activePawn, activePawn->getBoardPosition());
    qInfo() << activePawn->getBoardPosition().x << " " << activePawn->getBoardPosition().y;
    boardModel.deactivatePawn();
}

void GameInterface::showWinnerInterface(Player winner) {
    gameStarted = false;

    scene->clear();

    WinnerInterface *winnerInterface = new WinnerInterface(winner);
    winnerInterface->setRect(0, 0, Constants::gameInterfaceWidth, Constants::gameInterfaceHeight);
}
