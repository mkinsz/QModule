#ifndef HELPS_H
#define HELPS_H

#include <QFont>
#include <QPoint>

class QString;
class QObject;
class QWidget;
class QLabel;
class QChar;
class QFont;
class QPushButton;


namespace Helps {

class Base
{
public:
    static void readConfig();
    static QString readConfig(const QString skey);
    static QString readConfig(const QString sGroup, const QString skey);

    static void writeConfig();
    static void writeConfig(const QString skey, QString sValue);
    static void writeConfig(const QString sGroup, const QString skey, QString sValue);

    static QString appPath;

    static int appFontSize;
    static QString appFontName;
};

class App : public QObject
{

public:
    static App *instance();

    static void setChinese();
    static void setStyle(const QString &qssFile);
    static void autoRunWithSystem(bool ifAutoRun, QString appName, QString appPath);

    static void sleep(int sec);

    static void moveFormToCenter(QWidget *frm);

    void setIcon(QLabel *lab, QChar chr);
    void setIcon(QPushButton *btn, QChar chr);

    void loadInfo();


protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    explicit App(QObject *parent = 0);

    QPoint m_mouse_point;
    bool m_mouse_pressed;

    QFont m_iconfont;
    static App *s_instance;
};
}



#endif // HELPS_H
