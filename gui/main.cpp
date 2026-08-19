#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;

    window.setWindowTitle("Domino");

    window.resize(1000, 700);

    window.show();

    return app.exec();
}