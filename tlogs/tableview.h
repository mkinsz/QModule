#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

class TableView : public QTableView
{
    Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);

public slots:
    void removeOne();
    void removeAll();

};

#endif // TABLEVIEW_H
