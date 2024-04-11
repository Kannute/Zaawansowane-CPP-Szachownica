#include "pawninterface.h"
#include <map>

PawnInterface::PawnInterface() {}

QString PawnInterface::getImagePath(PawnType type, Player owner) {
    static const std::map<PawnType, std::pair<QString, QString>> fileNames = {
        {PawnType::pawn, {"pawn_white.svg", "pawn_black.svg"}},
        {PawnType::rook, {"rook_white.svg", "rook_black.svg"}},
        {PawnType::bishop, {"bishop_white.svg", "bishop_black.svg"}},
        {PawnType::knight, {"knight_white.svg", "knight_black.svg"}},
        {PawnType::king, {"king_white.svg", "king_black.svg"}},
        {PawnType::queen, {"queen_white.svg", "queen_black.svg"}}
    };

    auto [whiteFile, blackFile] = fileNames.at(type);
    return ":Images/" + (owner == Player::white ? whiteFile : blackFile);
}

PawnType PawnInterface::getPawnType(BoardPosition position) {
    if (position.y == 1 || position.y == 6) {
        return PawnType::pawn;
    } else if (position.x == 0 || position.x == 7) {
        return PawnType::rook;
    } else if (position.x == 1 || position.x == 6) {
        return PawnType::knight;
    } else if (position.x == 2 || position.x == 5) {
        return PawnType::bishop;
    } else if (position.x == 3) {
        return PawnType::queen;
    } else {
        return PawnType::king;
    }
}
