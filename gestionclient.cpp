#include "gestionclient.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSystemTrayIcon>
#include <QTableView>
#include <QTableWidget>
#include <QPainter>
#include <QtGui>
#include <QTextDocument>
#include <QFileDialog>
#include "ui_mainwindow.h"
#include <QMainWindow>

gestionclient::gestionclient()

    {
    nom=" ";prenom=" ";IDD=0;mail=" ";categorie="";
    }
    gestionclient::gestionclient(QString nom, QString prenom ,int IDD,QString  mail,QString categorie)
    {
    this->nom=nom;this->prenom=prenom;this->IDD=IDD;this->mail=mail;this->categorie=categorie;}
    QString gestionclient::getnomIM(){return nom;}
    QString gestionclient::getprenomIM(){return prenom;}
    int gestionclient::getIDDIM(){return IDD;}
    QString gestionclient::getmailIM (){return mail;}
    QString gestionclient::getcatIM (){return categorie;}
    void gestionclient::setnomIM (QString nom){this->nom=nom;}
    void gestionclient::setprenomIM (QString prenom){this->prenom=prenom;}
    void gestionclient::setmailIM (QString mail){this->mail=mail;}

    void gestionclient::setIDDIM(int IDD){this->IDD=IDD;}
    void gestionclient::setcatIM(QString categorie){this->categorie=categorie;}




    bool gestionclient::ajouterIM()

    {
        QSqlQuery query;
        QString IDD_string=QString::number(IDD);

             query.prepare("INSERT INTO GESTIONCLIENT (nom,prenom,IDD,mail,categorie) "
                           "VALUES (:nom, :prenom,:IDD, :mail, :categorie)");

             query.bindValue(":nom", nom);
             query.bindValue(":prenom", prenom);
                query.bindValue(":IDD", IDD_string);

                query.bindValue(":mail", mail);
             query.bindValue(":categorie", categorie);


             return query.exec();
    }

    bool gestionclient::supprimerIM(int IDD )
    {   QSqlQuery query;


             query.prepare("delete from GESTIONCLIENT where IDD=:IDD");
             query.bindValue(":IDD", IDD);


             return query.exec();

    }


    QSqlQueryModel* gestionclient::afficherIM()
    {
        QSqlQueryModel* model=new QSqlQueryModel();
        model ->setQuery("SELECT * FROM GESTIONCLIENT");
        model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("nom"));
        model ->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
        model ->setHeaderData(2,Qt::Horizontal,QObject::tr("IDD"));
        model ->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
        model ->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));



        return model;
    }


     QSqlQueryModel* gestionclient::chercherIM(QString q)
    {
         QString IDD_string= QString::number(IDD);
        QSqlQueryModel* model=new QSqlQueryModel();
        model ->setQuery("SELECT * FROM GESTIONCLIENT WHERE IDD='"+IDD_string+"'");
        model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("nom"));
        model ->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
        model ->setHeaderData(2,Qt::Horizontal,QObject::tr("IDD"));
        model ->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
        model ->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));
         return model;
    }


    QSqlQueryModel* gestionclient::chercherIM_2(QString q)
    {
        QString res= nom ;
        QSqlQueryModel *model=new QSqlQueryModel();
         model->setQuery("SELECT * FROM GESTIONCLIENT  WHERE nom like '%"+q+"%'" );
         model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("nom"));
         model ->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
         model ->setHeaderData(2,Qt::Horizontal,QObject::tr("IDD"));
         model ->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
         model ->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));
         return model;

    }


    QSqlQueryModel* gestionclient::chercherIM_3(QString q)
    {
        QString res= mail ;
        QSqlQueryModel *model=new QSqlQueryModel();
         model->setQuery("SELECT * FROM GESTIONCLIENT  WHERE mail like '%"+q+"%'" );
         model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("nom"));
         model ->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
         model ->setHeaderData(2,Qt::Horizontal,QObject::tr("IDD"));
         model ->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
         model ->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));
         return model;
    }


    bool gestionclient::modifierIM(int IDD)
    {
    QSqlQuery query;
    QString IDD_string= QString::number(IDD);

    query.prepare("UPDATE GESTIONCLIENT set nom=:nom,prenom=:prenom,IDD=:IDD,mail=:mail,categorie =:categorie" " WHERE IDD=:IDD");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
     query.bindValue(":IDD", IDD_string);
    query.bindValue(":mail", mail);
    query.bindValue(":categorie", categorie);
    return    query.exec();
    }







    QSqlQueryModel * gestionclient::trieIM()
    {
        QSqlQueryModel * model= new QSqlQueryModel();

                model->setQuery("SELECT * FROM GESTIONCLIENT ORDER BY IDD ASC ");
                model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("nom"));
                model ->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
                model ->setHeaderData(2,Qt::Horizontal,QObject::tr("IDD"));
                model ->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
                model ->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));
        return model;
    }



    QSqlQueryModel * gestionclient::trieIM_2()
    {
        QSqlQueryModel * model= new QSqlQueryModel();

                model->setQuery("SELECT * FROM GESTIONCLIENT ORDER BY NOM ASC ");
                model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("nom"));
                model ->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
                model ->setHeaderData(2,Qt::Horizontal,QObject::tr("IDD"));
                model ->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
                model ->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));
        return model;
    }




    QSqlQueryModel * gestionclient::trieIM_3()
    {
        QSqlQueryModel * model= new QSqlQueryModel();

                model->setQuery("SELECT * FROM GESTIONCLIENT ORDER BY mail ASC ");
                model ->setHeaderData(0, Qt::Horizontal ,QObject::tr("nom"));
                model ->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));
                model ->setHeaderData(2,Qt::Horizontal,QObject::tr("IDD"));
                model ->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
                model ->setHeaderData(4,Qt::Horizontal,QObject::tr("categorie"));
        return model;
    }









    void gestionclient::notifications_ajoutergestionclientIM()
    {

        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

        notifyIcon->show();
        notifyIcon->showMessage("Gestion des clients ","client ajouté ",QSystemTrayIcon::Information,15000);
    }

    void gestionclient::notifications_supprimergestionclientIM()
    {
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;


        notifyIcon->show();
        notifyIcon->showMessage("Gestion des clients ","client Supprimé",QSystemTrayIcon::Information,15000);
    }


    void gestionclient::notifications_modifiergestionclientIM()
    {
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

        notifyIcon->show();
        notifyIcon->showMessage("Gestion des clients ","client est modifié",QSystemTrayIcon::Information,15000);

    }

    void gestionclient::notifications_trouvergestionclientIM()
    {
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

        notifyIcon->show();
        notifyIcon->showMessage("Gestion des clients ","Compte trouvé",QSystemTrayIcon::Information,15000);

    }


    void gestionclient::notifications_donetriIM()
    {
        QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

        notifyIcon->show();
        notifyIcon->showMessage("Gestion des clients ","Data trié",QSystemTrayIcon::Information,15000);

    }



