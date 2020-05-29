#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardItem>
#include <QCryptographicHash>
#include <QStandardItemModel>
#include <QDateTime>
#include <QtMath>

#include "pagination.h"
#include "wsclient.h"
#include "downloadmanager.h"

QString io2sz(const int i, const QJsonObject &o) {
    switch(i) {
    case 0: return o["type"].toString();
    case 1: return QDateTime::fromTime_t(o["time"].toVariant().toUInt()).toString("yyyy-MM-dd HH:mm:ss");
    case 2: return o["user"].toString();
    case 3: return o["event"].toString();
    case 4: return o["param"].toString();
    default: return "";
    }
}

DownloadManager* MainWindow::s_downMg = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    initUI();

    //    m_ws = new WsClient(QUrl("ws://127.0.0.1:56789/echo"));
    m_ws = new WsClient(QUrl("ws://10.20.132.2:8080/schedule/ws"));
    //        m_ws = new WsClient(QUrl("ws://10.67.76.62:8080/schedule/ws"));
    connect(m_ws, &WsClient::connected, this, &MainWindow::connected);
    connect(m_ws, &WsClient::disconnected, this, [&]{ m_tk.clear(); });
    connect(m_ws, &WsClient::recv, this, &MainWindow::recv);

    m_mapFun["/mpuapi/v1r2/author/token/ack"] = &MainWindow::handleTokenAck;
    m_mapFun["/mpuapi/v1r2/author/login/ack"] = &MainWindow::handleLoginAck;
    m_mapFun["/mpuapi/v1r2/author/keeplive/ack"] = &MainWindow::handleAliveAck;
    m_mapFun["/mpuapi/v1r2/log/query/ack"] = &MainWindow::handleLogQueryAck;
    m_mapFun["/mpuapi/v1r2/log/export/ack"] = &MainWindow::handleLogExportAck;

    qDebug() << typeid(&MainWindow::handleLogExportAck).name();
}

MainWindow::~MainWindow()
{
    killTimer(m_tid);
    delete s_downMg;
    delete m_ws;
}

void MainWindow::initUI()
{
    ui->setupUi(this);

    ui->pastdt->setVisible(false);
    ui->nowdt->setVisible(false);
    ui->okbtn->setVisible(false);

    ui->pgn->setStyleSheet("QPushButton { margin: 0 3px; color: #AABEBE; background: #444444; border: 1px solid #888888; border-radius: 4px; } "
                           "QPushButton:disabled { color: #666666; border: 1px solid #666666; } "
                           "QPushButton:checked { color: #1890FE; border: 1px solid #1890FE; } "
                           "QPushButton:hover { background:transparent; color: #1890FE; border: 1px solid #1890FE; }");
    ui->pgn->setTotalPages(10);
    ui->pgn->setCurrentPage(1);
    ui->pgn->setButtonsSize(QSize(38, 32));
    ui->pgn->show();

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    m_model = new QStandardItemModel();
    m_model->setColumnCount(5);
    m_model->setHeaderData(0,Qt::Horizontal,"类型");   //设置表头内容
    m_model->setHeaderData(1,Qt::Horizontal,"时间");
    m_model->setHeaderData(2,Qt::Horizontal,"用户");
    m_model->setHeaderData(3,Qt::Horizontal,"事件");
    m_model->setHeaderData(4,Qt::Horizontal,"详情");
    ui->tableView->setModel(m_model);

    connect(ui->cusbtn, &QToolButton::clicked, this, &MainWindow::handleClick);
    connect(ui->okbtn,  &QToolButton::clicked, this, &MainWindow::handleClick);
    connect(ui->allbtn, &QToolButton::clicked, this, &MainWindow::handleClick);
    connect(ui->daybtn, &QToolButton::clicked, this, &MainWindow::handleClick);
    connect(ui->weekbtn,  &QToolButton::clicked, this, &MainWindow::handleClick);
    connect(ui->monthbtn, &QToolButton::clicked, this, &MainWindow::handleClick);
    connect(ui->searchet, &SearchEdit::Sig_Search, this, &MainWindow::handleSearch);
    connect(ui->searchet, &SearchEdit::Sig_Delete, this, &MainWindow::handleDelete);

    connect(ui->dlbtn, &QToolButton::clicked, this, [&]{ query(true); });
    connect(ui->pgn, &Pagination::onPageChange, [=](int value) {
        m_offset = m_size * static_cast<uint>(value - 1);
        query();
    });
//    ui->dlbtn->setToolTip("skdfjslkdfjal\r\nsjdlkfsjdflsjdakfsf\r\n");
}

DownloadManager *MainWindow::downloadManager()
{
    if (!s_downMg) {
        s_downMg = new DownloadManager();
    }
    return s_downMg;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    send("/mpuapi/v1r2/author/keeplive");
}

void MainWindow::recv(const QString &msg)
{
    QByteArray a = msg.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(a);
    QJsonObject json = doc.object();
    QString evt = json["evt"].toString();

    QMap<QString, handler>::iterator ite = m_mapFun.find(evt);
    if (ite != m_mapFun.end())
    {
        (this->*(ite.value()))(json);
    }else {
        qDebug() << "recv:" << msg.toUtf8().constData();
    }
}

void MainWindow::send(const QString &evt, const QJsonObject &obj)
{
    QJsonObject json;
    json["evt"] = evt;
    json["body"] = obj;
    if(!m_tk.isEmpty()) json["token"] = m_tk;
    QJsonDocument doc(json);
    m_ws->send(QString(doc.toJson(QJsonDocument::Compact)));

    if(!evt.contains("keeplive"))
        qDebug() << "send:" << doc.toJson(QJsonDocument::Compact).constData();
}

void MainWindow::connected()
{
    QJsonObject obj;
    obj["timestamp"] = "0";
    send("/mpuapi/v1r2/author/token", obj);
    m_tid = startTimer(5000);
}

void MainWindow::handleClick()
{
    QToolButton* btn = qobject_cast<QToolButton*>(sender());
    if(!btn) return;

    m_offset = 0;
    bool flag = false;  //custom visible

    QDate d = QDate::currentDate();
    QDateTime dt = QDateTime::currentDateTime();

    if(btn == ui->allbtn) {
        m_ndt = 0;
        m_pdt = 0;
    }else if(btn == ui->daybtn) {
        m_ndt = dt.toTime_t();
        m_pdt = QDateTime(d.addDays(-1)).toTime_t();
    }else if(btn == ui->weekbtn) {
        m_ndt = dt.toTime_t();
        m_pdt = QDateTime(d.addDays(-7)).toTime_t();
    }else if(btn == ui->monthbtn) {
        m_ndt = dt.toTime_t();
        m_pdt = QDateTime(d.addDays(-30)).toTime_t();
    }else if(btn == ui->cusbtn) {
        flag = true;
        ui->nowdt->setDateTime(dt);
        ui->pastdt->setDateTime(QDateTime(d.addDays(-1)));
    }else if(btn == ui->okbtn) {
        m_ndt = ui->nowdt->dateTime().toTime_t();
        m_pdt = ui->pastdt->dateTime().toTime_t();
    }

    ui->pastdt->setVisible(flag);
    ui->nowdt->setVisible(flag);
    ui->okbtn->setVisible(flag);
    if(flag) return;
    ui->pgn->setCurrentPage(1);
    query();
}

void MainWindow::handleSearch(const QString &text)
{
    m_cd = text;
    query();
}

void MainWindow::handleDelete()
{
    m_cd.clear();
    query();
}

void MainWindow::query(const bool download)
{
    QJsonObject obj;
    obj["src"] = "mpu";
    obj["order"] = true;
    obj["offset"] = static_cast<int>(m_offset);
    if(!download) obj["size"] = static_cast<int>(m_size);
    if(m_pdt) obj["tstart"] = static_cast<int>(m_pdt);
    if(m_ndt) obj["tend"] = static_cast<int>(m_ndt);
    if(!m_cd.isEmpty()) obj["condition"] = m_cd;
    send(download ? "/mpuapi/v1r2/log/export" : "/mpuapi/v1r2/log/query", obj);
}

void MainWindow::handleTokenAck(const QJsonObject &json) {
    QJsonDocument doc(json);
    qDebug() << doc.toJson().constData();
    QJsonObject body = json["body"].toObject();
    m_tk = body["token"].toString();

    QString md5;
    QString pwd = "admin123";
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);
    ba = pwd.toUtf8();
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());

    QJsonObject obj;
    obj["user"] = "admin";
    obj["password"] = md5;
    send("/mpuapi/v1r2/author/login", obj);
}

void MainWindow::handleLoginAck(const QJsonObject &json) {
    QJsonDocument doc(json);
    qDebug() << QString::fromUtf8(doc.toJson()).constData();

    query();
}

void MainWindow::handleAliveAck(const QJsonObject &json) {
    Q_UNUSED(json)
}

void MainWindow::handleLogQueryAck(const QJsonObject &json) {
    QJsonDocument doc(json);
    auto body = doc.object()["body"].toObject();
    auto tsize = body["totalsize"].toInt();
    //    auto size = body["size"].toInt();
    //    auto offset = body["offset"].toInt();
    //    qDebug() << doc.toJson().constData();
    //    qDebug() << tsize << size << offset;
    ui->pgn->updateTotalPages(qCeil(tsize/17.0));
    qDebug() << m_model->rowCount();
    m_model->removeRows(0, m_model->rowCount());
    if(body["items"].isArray()) {
        auto arr = body["items"].toArray();
        auto ite = arr.begin();
        while(ite != arr.end()) {
            for (int i = 0;i < 5;++i) {
                auto sm = io2sz(i, ite->toObject());
                auto *m = new QStandardItem(sm);
                m->setToolTip(sm);
                m_model->setItem(ite.i, i, m);
            }
            ++ite;
        }
    }
}

void MainWindow::handleLogExportAck(const QJsonObject &json) {
    QJsonDocument doc(json);
    qDebug() << doc.toJson().constData();
    auto body = doc.object()["body"].toObject();
    auto path = body["filepath"].toString();
    QUrl url("http://10.20.132.2:8080/"+path);
    MainWindow::downloadManager()->download(url);
}
