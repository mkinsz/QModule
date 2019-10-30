#ifndef TREEVIEWTEST_H
#define TREEVIEWTEST_H

#include <QWidget>
#include <QTreeWidget>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QComboBox>
#include "Windows.h"

class TreeViewTest : public QWidget
{
    Q_OBJECT

public:
    explicit TreeViewTest(QWidget *parent = nullptr);
    ~TreeViewTest();

private slots:
    void expanded(QModelIndex index);
    void treeViewCustomContextMenuRequested(const QPoint &pos);
    void changeStyle(int index);

private:
    QTreeView *m_treeView;
    QMenu *m_menu;
    QComboBox *m_comboBox;
};
#endif // TREEVIEWTEST_H
