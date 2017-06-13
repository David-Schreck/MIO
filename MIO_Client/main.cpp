#include "miowindow.h"

#include <QApplication>
#include <QObject>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /**
     * @brief Create the main Window
     */

    /// On définit le nom de l'entreprise et de l'aplication pour puvoir utiliser les constructeurs par defaut des preferences

    QCoreApplication::setOrganizationName("MIO");
    QCoreApplication::setApplicationName("MIO-Client");

    MIOWindow *MIOMainWindow = new MIOWindow;

    return app.exec();
}
