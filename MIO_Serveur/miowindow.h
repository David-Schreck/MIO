#ifndef MIOWINDOW_H
#define MIOWINDOW_H

#include <startwindow.h>
#include <settingswindow.h>
#include <gl_widget/glwidget.h>
#include <log_widget/logwidget.h>
#include <video_widget/videowidget.h>
#include <chat_widget/chatwidget.h>


#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

/**
 * @brief The MIOWindow class
 */
class MIOWindow : public QMainWindow // On hérite de QMainWindow
{
    //Est là pour géréer les SIGNALS et SLOTS personnalisés
    Q_OBJECT
public:
    //Default constructor
    MIOWindow();

    ~MIOWindow();

/// @remark Slots personnalisés (syntaxe finissant par _c)
public slots:

    /// @remark Signals personnalisés (syntaxe finissant par _s)
signals:
    void toLog_s(QString texte, int priority);

private:

    /// Boutons
    QPushButton *m_buttonPref;
    QPushButton *m_buttonQuit;

    /// Fenetres détachées
    SettingsWindow *m_settingsWindow;
    StartWindow *m_startWindow;

    /// Widgets principaux
    GLWidget *m_GLWidget;
    VideoWidget *m_videoWidget;
    ChatWidget *m_chatWidget;
    LogWidget *m_logWidget;

};


#endif // MIOWINDOW_H

