#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

class historique
{
    QString tmp;
  public:
      historique();
      void save(QString,QString,QString,QString,QString,QString);
      void save1(QString,QString);
      void save2(QString,QString,QString,QString,QString,QString,QString);
      QString load();
};

#endif // HISTORIQUE_H
