#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gestionmagasin.h"
#include <QMessageBox>
#include <QApplication>
#include <QIntValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QSqlQuery>
#include <QTextStream>
#include <QRegularExpression>
#include <QPdfWriter>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QDate>
#include "qcustomplot.h"

//------ACHREF-----------

#include <QMessageBox>
#include "gestionclient.h"
#include <QString>
#include <QTableView>
#include <QSystemTrayIcon>
#include <QMainWindow>
#include "exportexcelobject.h"
#include <QFileDialog>
#include <QtWidgets/qdialog.h>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QErrorMessage>
#include <QFile>
#include <QDataStream>

//--------------------------




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    ui->id->setValidator(new QIntValidator(0, 9999999, this));
    ui->id_mod->setValidator(new QIntValidator(0, 9999999, this));
    ui->id_rechercher->setValidator(new QIntValidator(0, 9999999, this));
    ui->tab_compte->setModel(G.afficher());

    ui->tab_compte_recherche->setModel(G.afficher());
    ui->menuu->setCurrentIndex(0);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_label()
{

}
void MainWindow::on_pb_ajouterm_clicked()
{
    ui->menuu->setCurrentIndex(2);
}
void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->id->text().toInt();
   QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString nomsoc=ui->nomsoc->text();
    int chiffre_aff=ui->categorie->text().toInt();
    QString email=ui->email->text();//<----------------------checking email

        int at=0;
        int point=0;
        int nbC=0;
        int nbI=0;
        int nbDash=0;
        bool okay=true;
        if (email.isEmpty()&&okay)
        {
            QMessageBox::warning(nullptr,QObject::tr("INVALID INPUT"),QObject ::tr("invalid E-MAIL (e-mail cannot be empty)\n"
                                                                        "Click Cancel And Try again"),QMessageBox::Cancel);

        }
        else if(!email.isEmpty()&&okay)
        {


            for(int i=0;i<email.length()&&okay;i++)
            {

                if(email[i]=="." || email[i]=="_" || email[i]=="-" || email[i]=="@")
                    if( email[i]==email[i+1] && i<email.length()-1)
                    {
                        okay=false;
                        break;
                    }
                if((email[i]>="a" && email[i]<="z") || (nom[i]>="A" && nom[i]<="Z")){nbC++;}

                else if(email[i]>="0" && email[i]<="9"){nbI++;}
                else if(email[i]=="-"  || email[i]=="_" || email[i]==".")
                {
                    nbDash++;
                }
                else if ( email[i]=="@")
                {
                    at++;
                    if(i==0)
                    {okay=false;

                        break;
                    }
                    else
                        for(int j=i+1;j<email.length();j++)
                        {

                           if((email[j]>="a" && email[j]<="z") || email[j]==".")
                            {
                               i=j;
                               if(email[j]=="."){point++;}
                               else{nbC++;}
                           }
                           else{okay=false;break;}

                        }
                }

                else
                    okay=false;

            }
            if(at!=1 || point!=1 || nbC==0 || nbDash>1)
            {
                okay=false;


                QMessageBox::warning(nullptr,QObject::tr("INVALID INPUT"),QObject ::tr("invalid E-MAIL (e-mail consists of only characters,numbers,@,-,_,.)\n "
                                                                                        "E-Mail EXAMPLE : example@mail.com\n"
                                                                                       "Click Cancel And Try again"),QMessageBox::Cancel);
            }
        }
    gestionmagasin G (id,nom,prenom,nomsoc,chiffre_aff,email);
    {gestionmagasin G (id,nom,prenom,nomsoc,chiffre_aff,email);
            bool test=G.ajouter();

            if(test)
            {  QMessageBox::information(nullptr, QObject::tr("Ajouter un compte"),
                                        QObject::tr("compte ajoute\n"
                                                    "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
                ui->tab_compte->setModel(G.afficher());
                ui->tab_compte_recherche->setModel(G.afficher());
                histo.save("id :"+ui->id->text(),"nom :"+ui->nom->text(),"prenom :"+ui->prenom->text(),"nom_boutique :"+ui->nomsoc->text(),"chiffre_aff :"+ui->categorie->text(),"email :"+ui->email->text());

            }
            else
            {  QMessageBox::warning(nullptr, QObject::tr("erreur"),
                                    QObject::tr("Echec de l'ajout.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
            }

        }

}
void MainWindow::on_pb_retour_ajouter_clicked()
{
    ui->menuu->setCurrentIndex(1);
}
void MainWindow::on_pb_afficherm_clicked()
{
    ui->menuu->setCurrentIndex(3);
}
void MainWindow::on_pb_retour_afficher_clicked()
{
    ui->menuu->setCurrentIndex(1);
}
void MainWindow::on_pb_supprimerm_clicked()
{
    ui->menuu->setCurrentIndex(4);
}
void MainWindow::on_pb_supprimer_clicked()
{

    gestionmagasin G1;

    G1.setid(ui->idsupp->text().toInt());
    bool test=G1.supprimer(G1.getid());
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Suppression avec succes.");
        ui->tab_compte->setModel(G.afficher());
        ui->tab_compte_recherche->setModel(G.afficher());
        histo1.save1("SUPPRIMER","id :"+ui->idsupp->text());

    }
    else
        msgBox.setText("Echec de suppression.");
    msgBox.exec();
}
void MainWindow::on_id_2_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT id FROM magasin");
    ui->comboBox->setModel(model);
}
void MainWindow::on_pb_retour_supp_clicked()
{
    ui->menuu->setCurrentIndex(1);
}
void MainWindow::on_pb_modifierm_clicked()
{
    ui->menuu->setCurrentIndex(5);
}
void MainWindow::on_pb_modifier_clicked()
{
        QString nom=ui->nom_mod->text();
        QString prenom=ui->prenom_mod->text();
        QString nomsoc=ui->nomsoc_mod->text();
        int chiffre_aff=ui->categorie_mod->text().toInt();
        QString email=ui->email_mod->text();
        int id=ui->id_mod->text().toInt();
        gestionmagasin G(0,nom,prenom,nomsoc,chiffre_aff,email);
        G.setid(id);
        bool test=G.modifier();
        QMessageBox msgBox;
        if(test)
        {
            msgBox.setText("modification avec succes.");
            ui->tab_compte->setModel(G.afficher());
            ui->tab_compte_recherche->setModel(G.afficher());
            histo.save2("SUPPRIMER","id :"+ui->id_mod->text(),"nom :"+ui->nom_mod->text(),"prenom :"+ui->prenom_mod->text(),"nom_boutique :"+ui->nomsoc_mod->text(),"chiffre_aff :"+ui->categorie_mod->text(),"email :"+ui->email_mod->text());
        }
        else
            msgBox.setText("Echec de modification.");
        msgBox.exec();
}
void MainWindow::on_pb_retour_modifier_clicked()
{
    ui->menuu->setCurrentIndex(1);
}
void MainWindow::on_pb_trier_clicked()
{
    ui->tab_compte->setModel(G.tri());
}
void MainWindow::on_pb_trier_nom_clicked()
{
    ui->tab_compte->setModel(G.trin());
}
void MainWindow::on_pb_trier_email_clicked()
{
    ui->tab_compte->setModel(G.trie());
}
void MainWindow::on_pb_rechercherm_clicked()
{
    ui->menuu->setCurrentIndex(6);
}
void MainWindow::on_pb_retour_rechercher_clicked()
{
    ui->menuu->setCurrentIndex(1);
}
void MainWindow::on_pushButton_2_clicked()
{
    QDesktopServices::openUrl(QUrl("https://site-8663562-393-8117.mystrikingly.com"));
}
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{

    QString val=ui->comboBox->currentText();

    QSqlQuery qry;
    qry.prepare("select * from magasin where id = '"+val+"' ");

    if(qry.exec( ))
    {
        while(qry.next())
        {
            ui->idsupp->setText(qry.value(0).toString());
        }
    }

}
void MainWindow::on_comboBox_m_currentTextChanged(const QString &arg1)
{
    QString val=ui->comboBox_m->currentText();

    QSqlQuery qry;
    qry.prepare("select * from magasin where id = '"+val+"' ");

    if(qry.exec( ))
    {
        while(qry.next())
        {
            ui->id_mod->setText(qry.value(0).toString());
            ui->nom_mod->setText(qry.value(1).toString());
            ui->prenom_mod->setText(qry.value(2).toString());
            ui->nomsoc_mod->setText(qry.value(3).toString());
            ui->categorie_mod->setText(qry.value(4).toString());
            ui->email_mod->setText(qry.value(5).toString());
        }
    }
}
void MainWindow::on_id_m_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT id FROM magasin");
    ui->comboBox_m->setModel(model);
}
void MainWindow::on_pb_ficher_excel_clicked()
{
    QTableView *table;
                   table = ui->tab_compte;

                   QString filters("CSV files (.csv);;All files (.*)");
                   QString defaultFilter("CSV files (*.csv)");
                   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                      filters, &defaultFilter);
                   QFile file(fileName);

                   QAbstractItemModel *model =  table->model();
                   if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                       QTextStream data(&file);
                       QStringList strList;
                       for (int i = 0; i < model->columnCount(); i++) {
                           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") << "\n";
                       for (int i = 0; i < model->rowCount(); i++) {
                           strList.clear();
                           for (int j = 0; j < model->columnCount(); j++) {

                               if (model->data(model->index(i, j)).toString().length() > 0)
                                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                               else
                                   strList.append("");
                           }
                           data << strList.join(";") + "\n";
                       }
                       file.close();
                       QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                                 QObject::tr("Export avec succes .\n"
                                                             "Click OK to exit."), QMessageBox::Ok);
                   }
}
void MainWindow::on_id_rechercher_textChanged(const QString &arg1)
{
    QString ch = arg1;

                     if (ch=="")
                     {
                         ui->tab_compte_recherche->setModel(G.afficher());
                     }
                     else
                     {
                       ui->tab_compte_recherche->setModel(G.rechercherid(ch)) ;
                     }
}
void MainWindow::on_nom_rechercher_textChanged(const QString &arg1)
{
    QString ch = arg1;

                     if (ch=="")
                     {
                         ui->tab_compte_recherche->setModel(G.afficher());
                     }
                     else
                     {
                       ui->tab_compte_recherche->setModel(G.recherchernom(ch)) ;
                     }
}
void MainWindow::on_email_rechercher_textChanged(const QString &arg)
{
    QString ch = arg;

                     if (ch=="")
                     {
                         ui->tab_compte_recherche->setModel(G.afficher());
                     }
                     else
                     {
                       ui->tab_compte_recherche->setModel(G.recherchermail(ch)) ;
                     }
}
void MainWindow::on_pb_retour_historique_clicked()
{
    ui->menuu->setCurrentIndex(1);
}
void MainWindow::on_pb_historique_clicked()
{
    ui->menuu->setCurrentIndex(7);
}
void MainWindow::on_pb_afficher_historique_clicked()
{
    QFile file("C:/Users/user/Downloads/gestion compte offre/historique.txt");
        if (!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file.errorString());
        QTextStream in(&file);
        ui->textBrowser->setText(in.readAll());
}

void MainWindow::on_pb_compte_offre_clicked()
{
    ui->menuu->setCurrentIndex(1);
}

void MainWindow::on_pb_offre_retour_clicked()
{
    ui->menuu->setCurrentIndex(0);
}



void MainWindow::on_pb_stat_clicked()
{
    gestionmagasin e;
    QLinearGradient gradient(0, 0, 0, 400);
                          gradient.setColorAt(0, QColor(90, 90, 90));
                          gradient.setColorAt(0.38, QColor(105, 105, 105));
                          gradient.setColorAt(1, QColor(70, 70, 70));
                          ui->plot->setBackground(QBrush(gradient));

                          QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                          amande->setAntialiased(false);
                          amande->setStackingGap(1);
                           //couleurs
                          amande->setName("TND");
                          amande->setPen(QPen(QColor(0, 18, 110).lighter(130)));
                          amande->setBrush(QColor(0, 18, 110));

                           //axe des abscisses
                          QVector<double> ticks;
                          QVector<QString> labels;
                          e.statistique(&ticks,&labels);

                          QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                          textTicker->addTicks(ticks, labels);
                          ui->plot->xAxis->setTicker(textTicker);
                          ui->plot->xAxis->setTickLabelRotation(60);
                          ui->plot->xAxis->setSubTicks(false);
                          ui->plot->xAxis->setTickLength(0, 4);
                          ui->plot->xAxis->setRange(0, 8);
                          ui->plot->xAxis->setBasePen(QPen(Qt::white));
                          ui->plot->xAxis->setTickPen(QPen(Qt::white));
                          ui->plot->xAxis->grid()->setVisible(true);
                          ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                          ui->plot->xAxis->setTickLabelColor(Qt::white);
                          ui->plot->xAxis->setLabelColor(Qt::white);

                          // axe des ordonnées
                          ui->plot->yAxis->setRange(0,10);
                          ui->plot->yAxis->setPadding(5);
                          ui->plot->yAxis->setLabel("Statistiques des chiffres d'affaire");
                          ui->plot->yAxis->setBasePen(QPen(Qt::white));
                          ui->plot->yAxis->setTickPen(QPen(Qt::white));
                          ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                          ui->plot->yAxis->grid()->setSubGridVisible(true);
                          ui->plot->yAxis->setTickLabelColor(Qt::white);
                          ui->plot->yAxis->setLabelColor(Qt::white);
                          ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                          ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                          // ajout des données  (statistiques de la quantité)//

                          QVector<double> PlaceData;
                          QSqlQuery q1("select chiffre_aff from MAGASIN");
                          while (q1.next()) {
                                        int  nbr_fautee = q1.value(0).toInt();
                                        PlaceData<< nbr_fautee;
                                          }
                          amande->setData(ticks, PlaceData);

                          ui->plot->legend->setVisible(true);
                          ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                          ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                          ui->plot->legend->setBorderPen(Qt::NoPen);
                          QFont legendFont = font();
                          legendFont.setPointSize(5);
                          ui->plot->legend->setFont(legendFont);
                          ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}







//-----------------IMEN---------------------






void MainWindow::on_pb_ajouterIM_clicked()
{

    QString nom=ui->nomA->text();
    QString prenom=ui->prenomA->text();
       int IDD=ui->IDDA->text().toInt();
        QString mail=ui->mailA->text();
    QString categorie=ui->categorieA->text();

   gestionclient d (nom,prenom,IDD,mail,categorie);

    {
            bool test=d.ajouterIM();
            ui->affichage->setModel(d.afficherIM());
            ui->affichage_2->setModel(d.afficherIM());
            ui->affichage_3->setModel(d.afficherIM());
            if(test)
            {  QMessageBox::information(nullptr, QObject::tr("Ajouter un compte"),
                                        QObject::tr("compte ajoute\n"
                                                    "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
            ui->statusBar->showMessage("comptes ajouté");
            d.notifications_ajoutergestionclientIM();}
            else
            {  QMessageBox::warning(nullptr, QObject::tr("erreur"),
                                    QObject::tr("Echec de l'ajout.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}

        }
}



void MainWindow::on_pb_modifierIM_clicked()
{
    int IDD=ui->IDDM->text().toInt();
    QString nom=ui->nomM->text();
    QString prenom=ui->prenomM->text();
       IDD=ui->IDDM->text().toInt();
      QString mail=ui->mailM->text();
    QString categorie=ui->categorieM->text();

 gestionclient d (nom,prenom,IDD,mail,categorie);


     {
     bool test=d.modifierIM(IDD);
      if(test)
     {

          ui->affichage->setModel(d.afficherIM());
          ui->affichage_2->setModel(d.afficherIM());
          ui->affichage_3->setModel(d.afficherIM());
     QMessageBox::information(nullptr, QObject::tr("modifier "),
                       QObject::tr("Modification effectuée.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
     ui->statusBar->showMessage("compte modifié");
     d.notifications_modifiergestionclientIM();
     }
       else
         {  QMessageBox::critical(nullptr, QObject::tr("modifier "),
                       QObject::tr("Echec de la modification  \n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
      ui->statusBar->showMessage("compte non modifié");
}
}
}



void MainWindow::on_pb_supprimerIM_clicked()
{

    int IDD=ui->id_suppIM_3->text().toInt();
    QString supp=ui->id_suppIM_3->text();
   gestionclient d ;
    bool test=d.supprimerIM(IDD);

    ui->affichage_2->setModel(d.afficherIM());

    if((test)&& (supp!=""))
    {
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject ::tr("suppression effectuée\n"
                                                                        "Click Cancel to exit"),QMessageBox::Cancel);
    ui->statusBar->showMessage("suppression effectuée");
    d.notifications_supprimergestionclientIM();}
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject ::tr("suppression non effectue\n"
                                                                        "Click Cancel to exit"),QMessageBox::Cancel);

    ui->statusBar->showMessage("suppression non effectuée");
    }


}



void MainWindow::on_pb_rechercherIM_clicked()
{
   gestionclient d ;

        QString IDD=ui->id_suppIM_3->text();


                        if (IDD=="")
                        {

                            ui->affichage_2->setModel(d.afficherIM());

                            QMessageBox::warning(nullptr, QObject::tr("erreur"),
                                                               QObject::tr("Echec de la recherche.\n"
                                                                           "Click Cancel to exit."), QMessageBox::Cancel);
                        }
                        else
                        {

                           ui->affichage_2->setModel(d.chercherIM(IDD)) ;

                          QMessageBox::information(nullptr, QObject::tr("Recherche"),
                                                  QObject::tr("compte a chercher existe\n"
                                                              "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
                      ui->statusBar->showMessage("recherche terminée");
                      d.notifications_trouvergestionclientIM();
                        }




    }



void MainWindow::on_pb_rechercherIM_2_clicked()
{
    gestionclient d ;

         QString nom=ui->id_suppIM_3->text();




                         if (nom=="")
                         {
                             ui->affichage_2->setModel(d.afficherIM());
                             QMessageBox::warning(nullptr, QObject::tr("erreur"),
                                                                QObject::tr("Echec de la recherche.\n"
                                                                            "Click Cancel to exit."), QMessageBox::Cancel);
                         }
                         else
                         {
                           ui->affichage_2->setModel(d.chercherIM_2(nom)) ;
                           QMessageBox::information(nullptr, QObject::tr("Recherche"),
                                                   QObject::tr("compte a chercher existe\n"
                                                               "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
                       ui->statusBar->showMessage("recherche terminée");
                       d.notifications_trouvergestionclientIM();
                         }


    }




void MainWindow::on_pb_rechercherIM_3_clicked()
{
    gestionclient d ;

         QString mail=ui->id_suppIM_3->text();




                         if (mail=="")
                         {
                             ui->affichage_2->setModel(d.afficherIM());
                             QMessageBox::warning(nullptr, QObject::tr("erreur"),
                                                                QObject::tr("Echec de la recherche.\n"
                                                                            "Click Cancel to exit."), QMessageBox::Cancel);
                         }
                         else
                         {
                           ui->affichage_2->setModel(d.chercherIM_3(mail)) ;
                           QMessageBox::information(nullptr, QObject::tr("Recherche"),
                                                   QObject::tr("compte a chercher existe\n"
                                                               "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
                       ui->statusBar->showMessage("recherche terminée");
                       d.notifications_trouvergestionclientIM();
                         }

    }





void MainWindow::on_pb_trierIM_clicked()
{
    gestionclient F;
    ui->affichage->setModel(F.trieIM());
    ui->affichage->setModel(F.afficherIM());
    bool test=F.trieIM();
    QMessageBox msgBox ;

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("tri"),
                                QObject::tr("comptes triés \n"
                                            "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
     ui->affichage->setModel(F.trieIM());
      ui->affichage_2->setModel(F.trieIM());
       ui->affichage_3->setModel(F.trieIM());
       ui->statusBar->showMessage("comptes triés");
         F.notifications_donetriIM();
    }
    else
    {  QMessageBox::warning(nullptr, QObject::tr("erreur"),
                            QObject::tr("Echec de la tri.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}


}



void MainWindow::on_pb_trierIM_2_clicked()
{
    gestionclient F;
    ui->affichage->setModel(F.trieIM_2());
    ui->affichage->setModel(F.afficherIM());
    bool test=F.trieIM_2();
    QMessageBox msgBox ;

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("tri"),
                                QObject::tr("comptes triés \n"
                                            "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
     ui->affichage->setModel(F.trieIM_2());
      ui->affichage_2->setModel(F.trieIM_2());
       ui->affichage_3->setModel(F.trieIM_2());
       ui->statusBar->showMessage("comptes triés");
         F.notifications_donetriIM();
    }
    else
    {  QMessageBox::warning(nullptr, QObject::tr("erreur"),
                            QObject::tr("Echec de la tri.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}


}






void MainWindow::on_pb_trierIM_3_clicked()
{
    gestionclient F;
    ui->affichage->setModel(F.trieIM_3());
    ui->affichage->setModel(F.afficherIM());
    bool test=F.trieIM_3();
    QMessageBox msgBox ;

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("tri"),
                                QObject::tr("comptes triés \n"
                                            "Cliquez sur cancel Pour Quitter."), QMessageBox::Cancel);
     ui->affichage->setModel(F.trieIM_3());
      ui->affichage_2->setModel(F.trieIM_3());
       ui->affichage_3->setModel(F.trieIM_3());
       ui->statusBar->showMessage("comptes triés");
         F.notifications_donetriIM();
    }
    else
    {  QMessageBox::warning(nullptr, QObject::tr("erreur"),
                            QObject::tr("Echec de la tri.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}


}










void MainWindow::on_pb_excelIM_clicked()

     //export excel
    {



            QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                                    tr("Excel Files (*.xls)"));
                    if (fileName.isEmpty())
                        return;

                    ExportExcelObject obj(fileName, "mydata", ui->affichage_3);

                    obj.addField(0, "nom", "char(20)");
                    obj.addField(1, "prenom", "char(20)");
                    obj.addField(2, "IDD", "char(20)");
                    obj.addField(3, "mail", "char(20)");
                    obj.addField(4, "categorie", "char(20)");



                    int retVal = obj.export2Excel();

                    if( retVal > 0)
                    {
                        QMessageBox::information(this, tr("Done"),
                                                 QString(tr("%1 records exported!")).arg(retVal)
                                                 );
                    }

}


void MainWindow::on_pb_printIM_clicked()
{   QString strStream;

            QTextStream out(&strStream);



    QString fileName = QFileDialog::getOpenFileName((QWidget* )0, "ouvrir en Excel", QString(), "*.xls");
                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".xls"); }
                QPrinter *printer=new  QPrinter(QPrinter::PrinterResolution);
                printer->setOutputFormat(QPrinter::PdfFormat);
                printer->setPaperSize(QPrinter::A4);
                printer->setOutputFileName(fileName);

                QTextDocument doc;
                doc.setHtml(strStream);
                doc.setPageSize(printer->pageRect().size());
                doc.print(printer);

                QPrinter *p=new QPrinter();
                QPrintDialog dialog(p,this);
                if(dialog.exec()== QDialog::Rejected)
                {
                    return;
                }
}


void MainWindow::on_pb_demande_retour_clicked()
{
    ui->menuu->setCurrentIndex(0);
}

void MainWindow::on_pb_dd_clicked()
{
    ui->menuu->setCurrentIndex(8);
}


void MainWindow::on_pb_demande_ajouter_clicked()
{
    ui->menuu->setCurrentIndex(9);
}

   void MainWindow::on_pb_demande_afficher_clicked()
   {
    ui->menuu->setCurrentIndex(10);
    gestionclient F;
    ui->affichage->setModel(F.afficherIM());
   }//11
    void MainWindow::on_pb_demande_rechercher_clicked()
    {
     ui->menuu->setCurrentIndex(11);
     gestionclient F;
     ui->affichage_2->setModel(F.afficherIM());
    }//12
    void MainWindow::on_pb_demande_modifier_clicked()
    {
     ui->menuu->setCurrentIndex(12);

    }//13
     void MainWindow::on_pb_demande_imprimer_clicked()
     {
      ui->menuu->setCurrentIndex(13);
       gestionclient F;
       ui->affichage_3->setModel(F.afficherIM());
     }//14


     void MainWindow::on_pb_r1_clicked()
     {
         ui->menuu->setCurrentIndex(8);
     }

     void MainWindow::on_pb_r2_clicked()
     {
         ui->menuu->setCurrentIndex(8);
     }

     void MainWindow::on_pb_r3_clicked()
     {
         ui->menuu->setCurrentIndex(8);
     }

     void MainWindow::on_pb_r4_clicked()
     {
         ui->menuu->setCurrentIndex(8);
     }

     void MainWindow::on_pb_r5_clicked()
     {
         ui->menuu->setCurrentIndex(8);
     }

