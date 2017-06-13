#include "miowindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /**
     * @brief Create the MIO Main Window
     */

    QCoreApplication::setOrganizationName("MIO");
    QCoreApplication::setApplicationName("MIO-Serveur");

    MIOWindow *MIOMainWindow = new MIOWindow;

    return app.exec();
}
