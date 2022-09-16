#include "notif.h"

notification::notification()
{

}
void notification::notification_system()
{
    QSystemTrayIcon * notifyIcon = new QSystemTrayIcon();
    notifyIcon->show();
    notifyIcon->showMessage("done","",QSystemTrayIcon::Information,15000);
}
void notification::notification_sys()
{
    QSystemTrayIcon * notifyIcon = new QSystemTrayIcon();
    notifyIcon->show();
    notifyIcon->showMessage("worked ","",QSystemTrayIcon::Information,15000);
}
