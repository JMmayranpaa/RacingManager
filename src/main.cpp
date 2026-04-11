#include <iostream>
#include <QApplication>
#include <overlay/OverlayWindow.h>


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    OverlayWindow overlay;
    overlay.show();

    return app.exec();


}