#include "historique.h"

historique::historique()
{

}
void historique::save(QString id,QString nom, QString prenom, QString nom_boutique, QString chiffre_aff, QString email)
{    QFile file ("C:/Users/Imén/OneDrive/Bureau/Nouveau dossier (3)/achref/historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << id+"\n"+nom << "\n"+prenom << "\n"+nom_boutique << "\n"+chiffre_aff << "\n"+email << "\n" "-------------" "\n";
}
void historique::save1(QString,QString id)
{    QFile file ("C:/Users/Imén/OneDrive/Bureau/Nouveau dossier (3)/achref/historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out <<"\n" " Vous avez supprimee : " "\n";
     out << id+"\n" "\n" "---------" "\n";
}
void historique::save2(QString,QString id,QString nom, QString prenom, QString nom_boutique, QString chiffre_aff, QString email)
{    QFile file ("C:/Users/Imén/OneDrive/Bureau/Nouveau dossier (3)/achref/historique.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out <<"\n" " Vous avez modifiee : " "\n";
     out << id+"\n"+nom << "\n"+prenom << "\n"+nom_boutique<< "\n"+chiffre_aff<< "\n"+email << "\n" "-------------" "\n";


}
QString historique::load()
{   tmp="";
    QFile file("C:/Users/Imén/OneDrive/Bureau/Nouveau dossier (3)/achref/historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}
