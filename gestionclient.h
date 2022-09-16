#ifndef gestionclient_H
#define gestionclient_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QTableWidget>
class gestionclient
{
public:
    gestionclient();
    gestionclient(QString,QString,int,QString,QString);

    QString getnomIM();
    QString getprenomIM();
    int getIDDIM ();

    QString getmailIM();
    QString getcatIM();


    void setnomIM (QString);
    void setprenomIM (QString);
    void setIDDIM(int);

    void setmailIM(QString);
    void setcatIM(QString);
    bool ajouterIM();
    QSqlQueryModel* afficherIM();

    bool supprimerIM (int);
     bool modifierIM(int);
    QSqlQueryModel * chercherIM(QString );
    QSqlQueryModel *chercherIM_2(QString );
    QSqlQueryModel * chercherIM_3(QString );
     void notifications_ajoutergestionclientIM();
     void notifications_supprimergestionclientIM();
     void notifications_modifiergestionclientIM();
     void notifications_trouvergestionclientIM();
     void notifications_donetriIM();
     QSqlQueryModel * trieIM();
      QSqlQueryModel * trieIM_2();
      QSqlQueryModel * trieIM_3();


private:
    QString nom , prenom , mail, categorie;
 int IDD  ;

};



#endif // gestionclient_H
