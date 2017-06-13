#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QLabel>
#include <QtWidgets>
#include <QtNetwork>
#include <QPushButton>


class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget();

    ~ChatWidget();

private slots:
    /// Pour se connecter au serveur
    void seConnecter_c();

    /// Appelé lors d'un click pour envoyer
    void envoyerMessage_c();

    /// Appelé lors de la saisie de "enter" par l'utilisateur pour envoyer
    void enterPressed_c();

    /// Appelé quand on recoit un paquet du serveur
    void donneesRecues_c();

    /// Appelé lorsqu'on s'est connecté au serveur
    void connexionFaite_c();

    /// Appelé lorsqu'on est déconnecté du serveur
    void deconnexionFaite_c();

    /// Appelé quand il y a une erreur sur le réseau
    void erreurSocket(QAbstractSocket::SocketError erreur);

private:
    /// Socket qui représente le serveur
    QTcpSocket *m_socket;

    /// Taille du message
    quint16 m_tailleMessage;

    /// Elements sur la page

    QLabel *m_chatTitre;
    QPushButton *m_buttonEnvoyerMessage;
    QPushButton *m_buttonConnection;
    QTextEdit *m_chatDisplay;
    QLineEdit *m_lineChat;



};

#endif // CHATWIDGET_H
