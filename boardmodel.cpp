#include "boardmodel.h"
#include "boardinterface.h"
#include "boardfield.h"
#include "kingmodel.h"
#include "queenmodel.h"
#include "rookmodel.h"
#include "bishopmodel.h"
#include "knightmodel.h"
#include "pawnmodel.h"
#include "constants.h"
#include <math.h>

template<typename T>
QList<T*> concatenateLists(const QList<T*> &list1, const QList<T*> &list2) {
    QList<T*> concatenatedList = list1;
    concatenatedList.append(list2);
    return concatenatedList;
}


BoardModel::BoardModel() {
    activePawn = nullptr;
    winner = nullptr;
    activePlayer = Constants::startingPlayer;
    pawnInterface = PawnInterface();

    initializePawns();
}

QList<BasePawn*> BoardModel::getBlackPawns() {
    return blackPawns;
}

QList<BasePawn*> BoardModel::getWhitePawns() {
    return whitePawns;
}

BasePawn* BoardModel::getActivePawn() {
    return activePawn;
}

Player BoardModel::getActivePlayer() {
    return activePlayer;
}

Player* BoardModel::getWinner() {
    return winner;
}

void BoardModel::activatePawn(PawnField *pawnField) {
    BasePawn* pawn = getPawnOnBoardPosition(pawnField->getPosition());

    if (pawn && pawn->getPawnOwner() == this->activePlayer) {
        activePawn = pawn;
        pawnField->setZValue(1);
    }
}

void BoardModel::deactivatePawn() {
    this->activePawn = nullptr;
}

void BoardModel::setActivePawnPosition(BoardPosition targetPosition) {
    if (this->activePawn) {
        this->activePawn->firstMoveTaken = true;
        this->activePawn->setBoardPosition(targetPosition);
    }
}


BasePawn* BoardModel::getPawnOnBoardPosition(BoardPosition boardPosition) {

    QList<BasePawn*> allPawns = concatenateLists<BasePawn>(this->blackPawns, this->whitePawns);

    for (auto& pawn : allPawns) {
        BoardPosition pawnPosition = pawn->getBoardPosition();
        if (boardPosition.x == pawnPosition.x && boardPosition.y == pawnPosition.y) {
            return pawn;
        }
    }
    return nullptr;
}

bool BoardModel::isCursorInBoardBoundries(QPoint point) {
    int boardYBoundry = BoardInterface::boardYPosition + BoardField::defaultSize * BoardInterface::boardSize;
    int boardXBoundry = BoardInterface::boardXPosition + BoardField::defaultSize * BoardInterface::boardSize;
    return (point.x() > BoardInterface::boardXPosition &&
            point.y() > BoardInterface::boardYPosition &&
            point.x() < boardXBoundry &&
            point.y() < boardYBoundry
            );
}

bool BoardModel::validatePawnMove(BoardPosition targetPosition, BasePawn* pawn, BoardPosition* requestedActivePawnPosition) {
    // Determine the pawn to validate
    BasePawn* pawnToValidate = pawn ? pawn : activePawn;

    // Get the pawn on the target position
    BasePawn* pawnOnPositionToMove = getPawnOnBoardPosition(targetPosition);

    // Validate the move for the pawn
    bool isMoveValid = pawnToValidate->validateMove(targetPosition, pawnOnPositionToMove, requestedActivePawnPosition);

    // Check for intersection if the pawn type is not knight
    if (pawnToValidate->getPawnType() != PawnType::knight) {
        return isMoveValid && checkForIntersection(targetPosition, pawnToValidate, requestedActivePawnPosition);
    }

    return isMoveValid;
}

bool BoardModel::didRemoveEnemyOnBoardPosition(BoardPosition boardPosition) {
    BasePawn *pawn = getPawnOnBoardPosition(boardPosition);

    if (!pawn){
        return false;
    }

    if (pawn->getPawnOwner() == this->activePlayer) {
        return false;
    }

    switch (this->activePlayer) {
        case Player::black: {
            whitePawns.removeAt(whitePawns.indexOf(pawn));
        }
        break;
        case Player::white: {
            blackPawns.removeAt(blackPawns.indexOf(pawn));
        }
        break;
    }

    if (pawn->getPawnType() == PawnType::king) {
        this->winner = &this->activePlayer;
    }

    delete pawn;
    return true;
}


bool BoardModel::isKingInCheck(Player owner, bool isCheckingActivePlayer, BoardPosition positionToMoveActivePlayer) {

    BasePawn *kingPawn = nullptr;

    if (isCheckingActivePlayer && activePawn->getPawnType() == PawnType::king) {
        kingPawn = activePawn;
    } else {
        switch (owner) {
        case Player::black:
            for (auto& pawn : blackPawns) {
                if (pawn->getPawnType() == PawnType::king) {
                    kingPawn = pawn;
                }
            }
            break;
        case Player::white:
            for (auto& pawn : whitePawns) {
                if (pawn->getPawnType() == PawnType::king) {
                    kingPawn = pawn;
                }
            }
            break;
        }
    }

    if (kingPawn) {
        bool isInCheck = false;

        switch (owner) {
            case Player::black:
                isInCheck = checkForCheck(whitePawns, isCheckingActivePlayer, kingPawn, positionToMoveActivePlayer);
                break;
            case Player::white:
                isInCheck = checkForCheck(blackPawns, isCheckingActivePlayer, kingPawn, positionToMoveActivePlayer);
        }

        return isInCheck;
    }

    return false;
}


bool BoardModel::didPromoteActivePawn() {
    if (!activePawn || activePawn->getPawnType() != PawnType::pawn) {
        return false;
    }

    BoardPosition pawnPosition = activePawn->getBoardPosition();
    Player pawnOwner = activePawn->getPawnOwner();

    if ((pawnOwner == Player::black && pawnPosition.y == 7) ||
        (pawnOwner == Player::white && pawnPosition.y == 0)) {
        activePawn->setPawnType(PawnType::queen);
        return true;
    }

    return false;
}


void BoardModel::switchRound() {
    this->activePlayer = (this->activePlayer == Player::black) ? Player::white : Player::black;
}

BoardPosition BoardModel::getBoardPositionForMousePosition(QPoint point) {
    int xPosition = static_cast<int>(floor((point.x() - BoardInterface::boardXPosition) / BoardField::defaultSize));
    int yPosition = static_cast<int>(floor((point.y() - BoardInterface::boardYPosition) / BoardField::defaultSize));

    return BoardPosition { xPosition, yPosition };
}

void BoardModel::initializePawns() {
    for (int row : {0, 1, 6, 7}) {
        Player player = (row < 2) ? Player::black : Player::white;
        initializePawnsForRow(row, player);
    }
}

void BoardModel::initializePawnsForRow(int rowNumber, Player owner) {
    for (int i = 0; i < BoardInterface::boardSize; i++) {
        BoardPosition boardPosition = { i, rowNumber };
        PawnType type = pawnInterface.getPawnType(boardPosition);
        QString imagePath = pawnInterface.getImagePath(type, owner);
        BasePawn *pawn;

        switch (pawnInterface.getPawnType(boardPosition)) {
            case PawnType::king: pawn = new KingModel(owner, type, boardPosition, imagePath); break;
            case PawnType::queen: pawn = new QueenModel(owner, type, boardPosition, imagePath); break;
            case PawnType::rook: pawn = new RookModel(owner, type, boardPosition, imagePath); break;
            case PawnType::bishop: pawn = new BishopModel(owner, type, boardPosition, imagePath); break;
            case PawnType::knight: pawn = new KnightModel(owner, type, boardPosition, imagePath); break;
            case PawnType::pawn: pawn = new PawnModel(owner, type, boardPosition, imagePath); break;
         };

        if (owner == Player::white) {
            whitePawns.append(pawn);
        }
        else {
            blackPawns.append(pawn);
        }
    }
}

bool BoardModel::checkForIntersection(BoardPosition positionToMove,
                                                     BasePawn *pawnToValidate,
                                                     BoardPosition *requestedActivePawnPosition) {
    BoardPosition pawnPosition = pawnToValidate->getBoardPosition();
    int xDiference = positionToMove.x - pawnPosition.x;
    int yDiference = positionToMove.y - pawnPosition.y;
    int numbeOfFieldsToCheck = std::max(abs(xDiference), abs(yDiference));

    if (numbeOfFieldsToCheck == 1) {
        return true;
    }

    for (int i = 0; i < numbeOfFieldsToCheck; i++) {
        BoardPosition positionToCheck;

        if (xDiference < 0) {
            if (yDiference == 0) {
                positionToCheck = { pawnPosition.x + (xDiference + i), pawnPosition.y };
            } else if (yDiference < 0) {
                positionToCheck = { pawnPosition.x + (xDiference + i), pawnPosition.y + (yDiference + i) };
            } else {
                positionToCheck = { pawnPosition.x + (xDiference + i), pawnPosition.y + (yDiference - i) };
            }
        } else if (yDiference < 0) {
            if (xDiference == 0) {
                positionToCheck = { pawnPosition.x, pawnPosition.y + (yDiference + i) };
            } else {
                positionToCheck = { pawnPosition.x + (xDiference - i), pawnPosition.y + (yDiference + i) };
            }
        } else {
            if (xDiference == 0) {
                positionToCheck = { pawnPosition.x, pawnPosition.y + (yDiference - i) };
            } else if (yDiference == 0) {
                positionToCheck = { pawnPosition.x + (xDiference - i), pawnPosition.y };
            } else {
                positionToCheck = { pawnPosition.x + (xDiference - i), pawnPosition.y + (yDiference - i) };
            }
        }

        BasePawn *pawnToCheck = getPawnOnBoardPosition(positionToCheck);

        if (requestedActivePawnPosition &&
                positionToCheck.x != positionToMove.x &&
                positionToCheck.y != positionToMove.y &&
                positionToCheck.x == requestedActivePawnPosition->x &&
                positionToCheck.y == requestedActivePawnPosition->y) {
            return false;
        }

        if (pawnToCheck &&
                (pawnPosition.x != positionToMove.x ||pawnPosition.y != positionToMove.y)) {
            return false;
        }
    }

    return true;
}

bool BoardModel::checkForCheck(QList<BasePawn*> pawns,bool isCheckingActivePlayer, BasePawn *kingPawn, BoardPosition positionToMoveActivePlayer) {
    bool isInCheck = false;

    for (auto& pawn : pawns) {
        BoardPosition kingPosition = kingPawn->getBoardPosition();
        BoardPosition pawnPosition = pawn->getBoardPosition();

        if (isCheckingActivePlayer && activePawn->getPawnType() == PawnType::king) {
            if (validatePawnMove(positionToMoveActivePlayer, pawn, &positionToMoveActivePlayer)) {
                isInCheck = true;
            }
        } else if (isCheckingActivePlayer) {

            if ((positionToMoveActivePlayer.x != pawnPosition.x || positionToMoveActivePlayer.y != pawnPosition.y) &&
                validatePawnMove(kingPosition, pawn, &positionToMoveActivePlayer)) {
                isInCheck = true;
            }

        } else if (validatePawnMove(kingPosition, pawn)) {
            isInCheck = true;
        }
    }

    return isInCheck;
}
