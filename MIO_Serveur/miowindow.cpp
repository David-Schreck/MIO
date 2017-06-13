#include "miowindow.h"

MIOWindow::MIOWindow() : QMainWindow()
{
    /// Paramètres de base de la fenêtre
    setMinimumSize(600, 400);
    setWindowTitle("MIO Serveur - Projet ISIS");
    showMaximized();

    ///@todo Gérer la configuration d'une icone logicielle
    QIcon Icon("MIO_Serveur.icns");
    setWindowIcon(Icon);

    /// Règle la couleur d'arrière plan de l'application
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, Qt::darkGray);
    qApp->setPalette(pal);

    /// Initialisation des attributs

    /// Boutons
    m_buttonPref = new QPushButton("Settings");
    m_buttonQuit = new QPushButton("Quit");

    /// Fenêtres détachées
    m_settingsWindow = new SettingsWindow();
    m_startWindow = new StartWindow();

    /// Widgets principaux
    m_GLWidget = new GLWidget;
    m_logWidget = new LogWidget;
    m_videoWidget = new VideoWidget;
    m_chatWidget = new ChatWidget;


    /// Mise en place des éléments

    QWidget *zoneCentrale = new QWidget;
    QHBoxLayout *HLayout = new QHBoxLayout;

    QVBoxLayout *VLayout1 = new QVBoxLayout;
    VLayout1->addWidget(m_videoWidget);
    VLayout1->addWidget(m_GLWidget);

    QHBoxLayout *HLayoutBottom = new QHBoxLayout;
    HLayoutBottom->addWidget(m_buttonPref);
    HLayoutBottom->addWidget(m_buttonQuit);

    QVBoxLayout *VLayout2 = new QVBoxLayout;
    VLayout2->addWidget(m_logWidget);
    VLayout2->addLayout(HLayoutBottom);

    HLayout->addLayout(VLayout1);
    HLayout->addWidget(m_chatWidget);
    HLayout->addLayout(VLayout2);

    zoneCentrale->setLayout(HLayout);
    setCentralWidget(zoneCentrale);

    /// Connections
    QObject::connect(m_buttonPref, SIGNAL(clicked()), m_settingsWindow, SLOT(show()));
    QObject::connect(m_buttonQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QObject::connect(m_logWidget, SIGNAL(toLog_s(QString, int)), m_logWidget, SLOT(writeInLog_c(QString, int)));
    QObject::connect(m_chatWidget, SIGNAL(toLog_s(QString, int)), m_logWidget, SLOT(writeInLog_c(QString, int)));
    QObject::connect(this, SIGNAL(toLog_s(QString, int)), m_logWidget, SLOT(writeInLog_c(QString, int)));


    /// On notifie dans le log le lancement de l'application
    /// On regarde quelle heure il est
    QString time = QDateTime::currentDateTime().toString(Qt::TextDate);

    emit toLog_s(time+"<br/>Lancement de MIO-Serveur avec succès", 1);




    /// Afficher la startWindow
    m_startWindow->show();

    /// Lancement du serveur
    m_chatWidget->lancementServeur();

}


//Destructeur
MIOWindow::~MIOWindow()
{
    delete m_buttonPref;
    delete m_buttonQuit;

    delete m_settingsWindow;
    delete m_startWindow;

    delete m_GLWidget;
    delete m_videoWidget;
    delete m_logWidget;
    delete m_chatWidget;
}
