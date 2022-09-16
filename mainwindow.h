#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//-----------------
#include <QMainWindow>
#include "gestionmagasin.h"
#include "historique.h"
#include "notif.h"
#include "ui_mainwindow.h"
//-------DEMANDE(client)----------
#include "gestionclient.h"
#include "exportexcelobject.h"
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QTextStream>
//---------------------

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void update_label();
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_id_2_clicked();
    void on_pb_ajouterm_clicked();
    void on_pb_retour_supp_clicked();
    void on_pb_retour_ajouter_clicked();
    void on_pb_afficherm_clicked();
    void on_pb_retour_afficher_clicked();
    void on_pb_supprimerm_clicked();
    void on_pb_modifierm_clicked();
    void on_pb_retour_modifier_clicked();
    void on_pb_trier_clicked();
    void on_pb_trier_nom_clicked();
    void on_pb_trier_email_clicked();
    void on_pb_rechercherm_clicked();
    void on_pushButton_2_clicked();
    void on_pb_retour_rechercher_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_m_currentTextChanged(const QString &arg1);
    void on_id_m_clicked();
    void on_pb_ficher_excel_clicked();
    void on_id_rechercher_textChanged(const QString &arg1);
    void on_nom_rechercher_textChanged(const QString &arg1);
    void on_email_rechercher_textChanged(const QString &arg1);

    void on_pb_retour_historique_clicked();

    void on_pb_historique_clicked();

    void on_pb_afficher_historique_clicked();

    void on_pb_compte_offre_clicked();

    void on_pb_offre_retour_clicked();


    void on_pb_demande_retour_clicked();


    void on_pb_dd_clicked();
     void on_pb_stat_clicked();


 //-----------DEMANDE(client)----------

    void on_pb_ajouterIM_clicked();
    void on_pb_supprimerIM_clicked();
    void on_pb_modifierIM_clicked();
    void on_pb_rechercherIM_clicked();
     void on_pb_rechercherIM_2_clicked();
      void on_pb_rechercherIM_3_clicked();
    void on_pb_trierIM_clicked();
    void on_pb_trierIM_2_clicked();
    void on_pb_trierIM_3_clicked();
    void on_pb_excelIM_clicked();
    void on_pb_printIM_clicked();
    void on_pb_demande_ajouter_clicked();//10
       void on_pb_demande_afficher_clicked();//11
        void on_pb_demande_rechercher_clicked();//12
        void on_pb_demande_modifier_clicked();//13
         void on_pb_demande_imprimer_clicked();//14
          void on_pb_r1_clicked();// retour 1
          void on_pb_r2_clicked();// retour 2
          void on_pb_r3_clicked();// retour 3
          void on_pb_r4_clicked();// retour 4
          void on_pb_r5_clicked();// retour 5

    //------------------------------


private:
    Ui::MainWindow *ui;
    gestionmagasin G;
    historique histo;
    historique histo1;
    historique histo2;
    notification N;
   //---------------------
    gestionclient Etmp ;

};

#endif // MAINWINDOW_H
