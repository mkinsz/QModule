#ifndef UTIL_H
#define UTIL_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QApplication>
#include <QFontDatabase>

void MsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QString outmsg;

    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        outmsg = QString("Debug: %1 %2 %3 %4\r\n").arg(localMsg.constData(), context.file, QString(context.line), context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        outmsg = QString("Warning: %1 %2 %3 %4 \r\n").arg(localMsg.constData(), context.file, QString(context.line), context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        outmsg = QString("Critical: %1 %2 %3 %4 \r\n").arg(localMsg.constData(), context.file, QString(context.line), context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        outmsg = QString("Fatal: %1 %2 %3 %4 \r\n").arg(localMsg.constData(), context.file, QString(context.line), context.function);
        abort();
    default:;
    }

    QFile outFile("debuglog.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << outmsg <<endl;
}

void loadFonts(QApplication& app) {
    QFontDatabase database;
    QStringList fontlist = database.families();

    QStringList preferList;
    preferList.append("Microsoft YaHei");
    //    preferList.append("微软雅黑");
    preferList.append("SimSong");
    preferList.append("宋体");
    preferList.append("WenQuanYi Micro Hei");
    preferList.append("文泉驿微米黑");

    foreach (QString font, preferList) {
        if (fontlist.contains(font)) {
            app.setFont(QFont(font));
            qDebug()<<&app<<" set font: "<<font;
            return;
        }
    }
}


#endif // UTIL_H
