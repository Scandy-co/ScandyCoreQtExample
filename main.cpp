#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(application);

    QCoreApplication::setOrganizationName("ScandyCore Qt");
    QCoreApplication::setApplicationName("Qt Example");
    QCoreApplication::setApplicationVersion("1.0.0");

    // QCommandLineParser parser;
    // parser.setApplicationDescription(QCoreApplication::applicationName());
    // parser.addHelpOption();
    // parser.addVersionOption();
    // parser.addPositionalArgument("file", "The file to open.");
    // parser.process(app);

    QApplication a(argc, argv);
    MainWindow w;
    // if (!parser.positionalArguments().isEmpty())
    //   mainWin.loadFile(parser.positionalArguments().first());
    w.show();
    return a.exec();
}
