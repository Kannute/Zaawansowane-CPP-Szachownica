#include "winnerinterface.h"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include "button.h"
#include "constants.h"
#include "gameinterface.h"
#include "utils.h"

extern GameInterface *game;

WinnerInterface::WinnerInterface(Player winner) {
    double centeredXPosition = Constants::gameInterfaceWidth / 2;

    // Create and position the title item
    QGraphicsTextItem *titleItem = Utils::createTextItem("Match Over", Constants::fontSizeLarge, Constants::defaultTextColor, this);
    titleItem->setPos(centeredXPosition - titleItem->boundingRect().width() / 2, Constants::gameInterfaceHeight / 3);

    // Determine the winner name
    QString winnerName = (winner == Player::black) ? "Black player" : "White player";

    // Create and position the winner congrats text item
    QGraphicsTextItem *winnerCongrats = Utils::createTextItem(winnerName + " has won!", Constants::fontSizeMedium, Constants::defaultTextColor, this);
    winnerCongrats->setPos(centeredXPosition - winnerCongrats->boundingRect().width() / 2, Constants::gameInterfaceHeight / 2);

    // Create and position the main menu button
    Button *menuButton = new Button("Main Menu");
    menuButton->setPos(centeredXPosition - menuButton->boundingRect().width() / 2, Constants::gameInterfaceHeight / 2 - 1.2 * menuButton->boundingRect().height());

    // Connect the button signal to the mainMenu slot and add button to the scene
    connect(menuButton, SIGNAL(buttonPressed()), game, SLOT(mainMenu()));
    game->scene->addItem(menuButton);
    game->scene->addItem(this);
}
