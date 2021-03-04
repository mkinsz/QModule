#include "helps.h"

#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMutex>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QtCore>
#include <QtGui>

#if (QT_VERSION > QT_VERSION_CHECK(5,0,0))
#include <QtWidgets>
#endif

QString Helps::Base::appPath = "";

#ifdef Q_OS_WIN
int Helps::Base::appFontSize = 10;
QString Helps::Base::appFontName = "Microsoft YaHei";
#endif

#ifdef Q_OS_LINUX
#ifdef __arm__
int Base::appFontSize = 11;
QString Base::appFontName = "WenQuanYi Micro Hei";
#else
int Base::appFontSize = 11;
QString Base::appFontName = "WenQuanYi";
#endif
#endif

#ifdef Q_OS_MAC
int Base::appFontSize = 11;
QString Base::appFontName = "Heiti SC";
#endif

namespace Helps {

void Base::readConfig()
{
    readConfig("AppConfig", "skey");
}

QString Base::readConfig(const QString skey)
{
    return readConfig("AppConfig", skey);
}

QString Base::readConfig(const QString sGroup, const QString skey)
{
    QString fileName = Base::appPath + "config.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup(sGroup);
    QString sValue = set->value(skey).toString();
    set->endGroup();

    return sValue;
}

void Base::writeConfig()
{
    writeConfig("AppConfig", "skey", "sValue");
}

void Base::writeConfig(const QString skey, QString sValue)
{
    writeConfig("AppConfig", skey, sValue);
}

void Base::writeConfig(const QString sGroup, const QString skey, QString sValue)
{
    QString fileName = Base::appPath + "config.txt";
    QSettings *set = new QSettings(fileName, QSettings::IniFormat);
    set->beginGroup(sGroup);
    set->setValue(skey, sValue);
    set->endGroup();
}

App *App::instance()
{
    static QMutex mutex;
    if (!s_instance)
    {
        QMutexLocker locker(&mutex);
        if (!s_instance)
        {
            s_instance = new App;
        }
    }
    return s_instance;
}

App *Helps::App::s_instance = nullptr;


void App::setIcon(QLabel *lab, QChar chr)
{
    m_iconfont.setPointSize(Base::appFontSize);
    lab->setFont(m_iconfont);
    lab->setText(chr);
}

void App::setIcon(QPushButton *btn, QChar chr)
{
    m_iconfont.setPointSize(Base::appFontSize);
    btn->setFont(m_iconfont);
    btn->setText(chr);
}

void App::loadInfo()
{
    setChinese();
    qApp->setFont(QFont(Base::appFontName, Base::appFontSize));

     Base::appPath = QApplication::applicationDirPath();
}

bool App::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *wdt = (QWidget *)obj;
        if (!wdt->property("CanMove").toBool()) {
            return QObject::eventFilter(obj, evt);
        }

        QMouseEvent *event = static_cast<QMouseEvent *>(evt);
        if (event->type() == QEvent::MouseButtonPress) {
            if (event->button() == Qt::LeftButton) {
                m_mouse_pressed = true;
                m_mouse_point = event->globalPos() - wdt->pos();
                return true;
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            m_mouse_pressed = false;
            return true;
        } else if (event->type() == QEvent::MouseMove) {
            if (m_mouse_pressed && (event->buttons() & Qt::LeftButton)) {
                wdt->move(event->globalPos() - m_mouse_point);
                return true;
            }
        }

        return QObject::eventFilter(obj, evt);
}

void App::autoRunWithSystem(bool ifAutoRun, QString appName, QString appPath)
{
    QSettings *reg = new QSettings(
                "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
                QSettings::NativeFormat);

    if (ifAutoRun) {
        reg->setValue(appName, appPath);
    } else {
        reg->setValue(appName, "");
    }
}

void App::setStyle(const QString &qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void App::setChinese()
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(":/pic/picture/qt_zh_CN.qm");
    qApp->installTranslator(translator);
}

void App::sleep(int sec)
{
    QTime dieTime = QTime::currentTime().addMSecs(sec);

    while ( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void App::moveFormToCenter(QWidget *frm)
{
    int frmX = frm->width();
    int frmY = frm->height();

    QDesktopWidget dwt;

    int deskWidth = dwt.availableGeometry().width();
    int deskHeight = dwt.availableGeometry().height();

    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    frm->move(movePoint);
}

App::App(QObject *parent) : QObject(parent)
{
    int fontId = QFontDatabase::addApplicationFont(":/res/font/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);

    m_mouse_pressed = false;
    m_iconfont = QFont(fontName);

    qApp->installEventFilter(this);
}

}
