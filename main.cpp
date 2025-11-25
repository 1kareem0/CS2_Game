#include <QApplication>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Game SuperMario;
    SuperMario.show();
    return app.exec();
}
