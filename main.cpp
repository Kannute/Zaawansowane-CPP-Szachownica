#include <QApplication>
#include <gameinterface.h>

GameInterface *game;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    game = new GameInterface();
    game->show();
    game->displayMainMenu();

    return a.exec();
}
