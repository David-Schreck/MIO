#include "miowindow.h"

MIOWindow::MIOWindow() : QMainWindow()
{
    /// Paramètres de base de la fenêtre
    setWindowTitle("MIO - Projet ISIS");
    showMaximized();

    /// Règle la couleur d'arrière plan de l'application
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, Qt::darkGray);
    qApp->setPalette(pal);

    /// Initialisation

    /// Bouttons
    m_buttonPref = new QPushButton("Préférences");
    m_buttonQuit = new QPushButton("Quitter");
    m_buttonPref->setFixedWidth(100);
    m_buttonQuit->setFixedWidth(100);

    /// Fenêtres
    m_settingsWindow = new SettingsWindow();
    m_startWindow = new StartWindow();

    /// Widgets
    m_glWidget = new GLWidget;
    m_logWidget = new LogWidget;
    m_videoWidget = new VideoWidget;
    m_chatWidget = new ChatWidget;

    /// Connections
    QObject::connect(m_buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_buttonPref, SIGNAL(clicked()), m_settingsWindow, SLOT(show()));


    /// Mise en place des elements

    QWidget *zoneCentrale = new QWidget;
    QVBoxLayout *VLayout = new QVBoxLayout;

    QHBoxLayout *HLayout1 = new QHBoxLayout;
    HLayout1->addWidget(m_videoWidget);
    HLayout1->addWidget(m_glWidget);

    QHBoxLayout *HLayoutBottom = new QHBoxLayout;
    HLayoutBottom->addWidget(m_buttonPref);
    HLayoutBottom->addStretch();
    HLayoutBottom->addWidget(m_buttonQuit);

    VLayout->addLayout(HLayout1);
    VLayout->addWidget(m_chatWidget);
    VLayout->addLayout(HLayoutBottom);

    zoneCentrale->setLayout(VLayout);
    setCentralWidget(zoneCentrale);


    /// Afficher la startWindow
    m_startWindow->show();

}


/// Getteurs
SettingsWindow* MIOWindow::getSettings()
{
    return m_settingsWindow;
}

/// Public slots

void MIOWindow::showSettings_c()
{
    m_settingsWindow->show();
}

void MIOWindow::quit_c()
{
    qApp->quit();
}


//Destructeur
MIOWindow::~MIOWindow()
{
    /// Boutons
    delete m_buttonPref;
    delete m_buttonQuit;

    /// Fenêtres séparées
    delete m_settingsWindow;
    delete m_startWindow;

    /// Widgets
    delete m_chatWidget;
    delete m_glWidget;
    delete m_videoWidget;
    delete m_logWidget;
}
