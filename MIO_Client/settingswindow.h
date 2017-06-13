#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>
#include <QLineEdit>

/**
 * @brief The SettingsWindow class
 */
class SettingsWindow : public QWidget
{
    ///Est là pour géréer les SIGNALS et SLOTS personnalisés
    Q_OBJECT
public:
    /// Constructeur
    SettingsWindow();

    ///Getteurs
    QString getPseudo();



    /// Destructeur
    ~SettingsWindow();


    /// @remark Signals personnalisés (syntaxe finissant par _s)
signals:
    ///Mise à jour des preferences
    void refresh_s();

    /// @remark Slots personnalisés (syntaxe finissant par _c)
public slots:

    /// Mettre à jour le chemin d'accès
    void setPath_c();

    /// Appliquer les modifications
    void apply_c();

    /// Annuler les modifications
    void cancel_c();


private:


    QLabel *m_settingsTitle;
    QPushButton *m_ok;
    QPushButton *m_cancel;
    QPushButton *m_apply;

    QString m_IP;
    int m_port;
    QString m_pseudo;
    QString m_path;

    QLineEdit *m_lineEditIP;
    QLineEdit *m_lineEditPort;
    QLineEdit *m_lineEditPseudo;
    QLineEdit *m_lineEditPath;


};

#endif // SETTINGSWINDOW_H
