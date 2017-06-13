#include "chatwidget.h"

#include <QMainWindow>
#include <QSettings>
#include <QBoxLayout>
#include <QLabel>

ChatWidget::ChatWidget()
{

    /// On initialise les objets
    m_chatTitre = new QLabel("Chat");
    m_buttonEnvoyerMessage = new QPushButton("Envoyer");
    m_buttonConnection = new QPushButton("Connexion");
    m_chatDisplay = new QTextEdit;
    m_chatDisplay->setReadOnly(true);
    m_chatDisplay->setWindowTitle("Chat");
    m_chatDisplay->setDocumentTitle("Hello");
    m_lineChat = new QLineEdit;


    /// On agence les éléments du chat

    QVBoxLayout *Vlayout = new QVBoxLayout;
    Vlayout->addWidget(m_chatTitre);
    Vlayout->addWidget(m_chatDisplay);

    QHBoxLayout *Hlayout = new QHBoxLayout;
    Hlayout->addWidget(m_buttonConnection);
    Hlayout->addWidget(m_lineChat);
    Hlayout->addWidget(m_buttonEnvoyerMessage);

    Vlayout->addLayout(Hlayout);
    setLayout(Vlayout);


    /// On créé les conections

    QObject::connect(m_buttonConnection, SIGNAL(clicked()), this, SLOT(seConnecter_c()));
    QObject::connect(m_buttonEnvoyerMessage, SIGNAL(clicked()), this, SLOT(envoyerMessage_c()));



    /// On créé un Socket qui représente la connection au serveur
    m_socket = new QTcpSocket(this);

    /// On créé les connections entre le socket et nos slots
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(donneesRecues_c()));
    connect(m_socket, SIGNAL(connected()), this, SLOT(connexionFaite_c()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(deconnexionFaite_c()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    /// On initialise la taille de message à 0
    m_tailleMessage = 0;
}

/**
 * @brief ChatWidget::seConnecter_c Slot pour une tentative de connexion au serveur
 */
void ChatWidget::seConnecter_c()
{
    /// On annonce sur la fenêtre qu'on est en train de se connexionFaite_cr
    m_chatDisplay->append("<em>Tentative de connexion en cours...</em>");

    /// On désactive les connexions précédentes s'il y en a
    m_socket->abort();

    /// On se connexionFaite_c sur le serveur
    QSettings settings;
    m_socket->connectToHost(settings.value("IP").toString(), settings.value("Port").toInt());

}


/**
 * @brief ChatWidget::envoyerMessage_c Slot pour envoyer le message
 */
void ChatWidget::envoyerMessage_c()
{

    if (m_lineChat->text()!="") // Si le champ d'envoi n'est pas vide
    {
    /// On créé un objet qui récupère les préférences
    QSettings settings;

    /// On créé un array d'octets
    QByteArray paquet;

    QDataStream out(&paquet, QIODevice::WriteOnly);

    /// On prépare le paquet à envoyer
    QString messageAEnvoyer = "<strong>" + settings.value("Pseudo").toString() +"</strong> : " + m_lineChat->text();

    /// On met temporairement 0 pour la taille du message
    out << (quint16) 0;
    /// On met le message à envoyer
    out << messageAEnvoyer;

    /// On revient en position 0 dans le data stream
    out.device()->seek(0);

    /// On y met la taille du paquet
    out << (quint16) (paquet.size() - sizeof(quint16));

    /// On envoie le paquet
    m_socket->write(paquet);

    /// On vide la zone d'écriture du message
    m_lineChat->clear();

    /// On met le curseur à l'intérieur
    m_lineChat->setFocus();
    }
}

/**
 * @brief ChatWidget::enterPressed_c Slot lorsequ'on appuise sur la touche entrée du chat
 */
void ChatWidget::enterPressed_c()
{
    envoyerMessage_c();
}

/**
 * @brief ChatWidget::donneesRecues_c Slot activé quand on recoit un paquet, pareil que sur serveur, mais avec affichage dans une fenêtre de texte
 */
void ChatWidget::donneesRecues_c()
{
    /// Socket du serveur
    QDataStream in(m_socket);

    /// On regarde si on connait la taille du message
    if (m_tailleMessage == 0)
    {
        /// Si l'entête n'est pas complet, on quitte
        if (m_socket->bytesAvailable() < (int)sizeof(quint16))
             return;
        /// On met dans m_tailleMessage la taille du message
        in >> m_tailleMessage;
    }

    /// On quitte si la taille du paquet ne corresponds pas à l'entête
    if (m_socket->bytesAvailable() < m_tailleMessage)
        return;


    /// On écrit dans messageRecu le contenu du message
    QString messageRecu;
    in >> messageRecu;

    /// On affiche le message sur la zone de Chat
    m_chatDisplay->append(messageRecu);

    /// On remet la taille de m_tailleMessage à 0 pour pouvoir recevoir de futurs messages
    m_tailleMessage = 0;
}

/**
 * @brief ChatWidget::connexionFaite_c Slot est appelé lorsque la connexion au serveur a réussi
 */
void ChatWidget::connexionFaite_c()
{
    m_chatDisplay->append("<em>Connexion réussie !</em>");
    m_buttonConnection->setDisabled(true);
}

/**
 * @brief ChatWidget::deconnexionFaite_c Slot appelé lorsqu'on est déconnecté du serveur
 */
void ChatWidget::deconnexionFaite_c()
{
    m_chatDisplay->append("<em>Déconnecté du serveur</em>");
    m_buttonConnection->setEnabled(true);
}

/**
 * @brief ChatWidget::erreurSocket Slot appelé lorsqu'il y a une erreur
 * @param erreur
 */
void ChatWidget::erreurSocket(QAbstractSocket::SocketError erreur)
{
    /// On affiche un message différent selon l'erreur qu'on nous indique
    switch(erreur)
    {
        case QAbstractSocket::HostNotFoundError:
            m_chatDisplay->append("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            m_chatDisplay->append("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>");
            break;
        case QAbstractSocket::RemoteHostClosedError:
            m_chatDisplay->append("<em>ERREUR : le serveur a coupé la connexion.</em>");
            break;
        default:
            m_chatDisplay->append("<em>ERREUR : " + m_socket->errorString() + "</em>");
    }

    m_buttonConnection->setEnabled(true);
}

ChatWidget::~ChatWidget()
{

}
