#include "gestionmagasin.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include "mainwindow.h"
#include "ui_mainwindow.h"

gestionmagasin::gestionmagasin()
{

    id=0;
    nom=" ";
    categorie=" ";
    nom_boutique="";
    chiffre_aff;
    email="";
}
gestionmagasin ::gestionmagasin(int id,QString nom ,QString categorie ,QString nom_boutique ,int chiffre_aff ,QString email)
{
    this->id=id;
    this->nom=nom;
    this->categorie=categorie;
    this->nom_boutique=nom_boutique;
    this->chiffre_aff=chiffre_aff;
    this->email=email;
}

int gestionmagasin::getid(){return id;}
QString gestionmagasin::getnom(){return nom;}
QString gestionmagasin::getcategorie(){return categorie;}
QString gestionmagasin::getnom_boutique(){return nom_boutique;}
int gestionmagasin::getchiffre_aff(){return chiffre_aff;}
QString gestionmagasin::getemail(){return email;}


void gestionmagasin::setid(int id){this->id=id;}
void gestionmagasin::setnom(QString nom){this->nom=nom;}
void gestionmagasin::setcategorie(QString categorie){this->categorie=categorie;}
void gestionmagasin::setnom_boutique(QString nom_boutique){this->nom_boutique=nom_boutique;}
void gestionmagasin::setchiffre_aff(int chiffre_aff){this->chiffre_aff=chiffre_aff;}
void gestionmagasin::setemail(QString email){this->email=email;}


bool gestionmagasin::ajouter()
{
    QSqlQuery query;
        QString id_string= QString::number(id);
             query.prepare("insert into magasin (id,nom,categorie,nom_boutique,chiffre_aff,email)VALUES (:id,:nom,:categorie,:nom_boutique,:chiffre_aff,:email)");
             query.bindValue(":id", id_string);
             query.bindValue(":nom", nom);
             query.bindValue(":categorie", categorie);
             query.bindValue(":nom_boutique", nom_boutique);
             query.bindValue(":chiffre_aff", chiffre_aff);
             query.bindValue(":email", email);

        return query.exec();
}
QSqlQueryModel* gestionmagasin::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM magasin");

         model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("categorie"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("identifiant"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("chiffre_aff"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("boutique"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

    return model;
}
bool gestionmagasin::supprimer(int id)
{
    QSqlQuery query;

             query.prepare(" Delete from magasin where id=:id ");
             query.bindValue(":id", id);
        return query.exec();
}
bool gestionmagasin::modifier()
{
QSqlQuery query;
    query.prepare("update magasin set NOM=?, categorie=?, nom_boutique=?, email=?, chiffre_aff=? where id=?");
    query.addBindValue(nom);
    query.addBindValue(categorie);
    query.addBindValue(nom_boutique);
    query.addBindValue(chiffre_aff);
    query.addBindValue(email);
    query.addBindValue(id);
return    query.exec();
}
QSqlQueryModel * gestionmagasin::tri()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM magasin ORDER BY CAST (ID AS number) ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("categorie"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("chiffre_aff"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("boutique"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
    return model;
}
QSqlQueryModel * gestionmagasin::trin()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM magasin ORDER BY NOM ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("categorie"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("chiffre_aff"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("boutique"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

    return model;
}
QSqlQueryModel * gestionmagasin::trie()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM magasin ORDER BY email ASC ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("categorie"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("chiffre_aff"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("boutique"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));

    return model;
}
QSqlQueryModel *gestionmagasin::rechercherid(QString q)
{
     QString res= QString::number(id);
     QSqlQueryModel *model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM magasin  WHERE id like '%"+q+"%'" );
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("categorie"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("identifiant"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("chiffre_aff"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("boutique"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
      return model;
}
QSqlQueryModel *gestionmagasin::recherchernom(QString q)
{
     QString res= nom ;
     QSqlQueryModel *model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM magasin  WHERE nom like '%"+q+"%'" );
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("categorie"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("identifiant"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("chiffre_aff"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("boutique"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
      return model;
}
QSqlQueryModel *gestionmagasin::recherchermail(QString q)
{
     QString res= email ;
     QSqlQueryModel *model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM magasin  WHERE email like '%"+q+"%'" );
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("categorie"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("identifiant"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("chiffre_aff"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("boutique"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
      return model;
}


void gestionmagasin::statistique(QVector<double>* ticks,QVector<QString> *labels)

{

    QSqlQuery q;

    int i=0;

    q.exec("SELECT  chiffre_aff  FROM magasin");

    while (q.next())

    {

        QString chiffre_aff = q.value(0).toString();

        i++;

        *ticks<<i;

        *labels <<chiffre_aff;

    }

}
