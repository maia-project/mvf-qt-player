#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "playerwidget.h"
#include "playerwindow.h"

int main(int argc, char **argv) 
{
    QApplication app(argc, argv);
    PlayerWindow *mainWin = new PlayerWindow(argv[1]);
    mainWin->setWindowTitle("MVF player");
    mainWin->show();    
    int retval = app.exec();
    
    return retval;
}

