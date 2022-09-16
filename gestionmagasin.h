#ifndef gestionmagasin_H
#define gestionmagasin_H
#include <QString>
#include <QSqlQueryModel>


class gestionmagasin
{
public:
    //constructeurs

    gestionmagasin();
    gestionmagasin(int , QString ,QString ,QString ,int ,QString);


    //getters

    int getid();
    QString getnom();
    QString getcategorie();
    QString getnom_boutique();
    int getchiffre_aff();
    QString getemail();

    //setters

    void setid(int);
    void setnom(QString);
    void setcategorie(QString);
    void setnom_boutique(QString);
    void setchiffre_aff(int);
    void setemail(QString);
    void statistique(QVector<double>* ticks,QVector<QString> *labels);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* tri();
    QSqlQueryModel* trin();
    QSqlQueryModel* trie();
    QSqlQueryModel* chercher(int);
    QSqlQueryModel *rechercherid(QString);
    QSqlQueryModel *recherchernom(QString);
    QSqlQueryModel *recherchermail(QString);



private:
    int id,chiffre_aff;
    QString nom , categorie , nom_boutique , email;
};

#endif // gestionmagasin_H
