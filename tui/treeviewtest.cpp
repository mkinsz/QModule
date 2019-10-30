#include "treeviewtest.h"
#include "treemodel.h"
#include <QHeaderView>
#include <QFile>
#include <QHBoxLayout>
#include <QPainter>
#include <QListView>
#include "itemdelegate.h"

TreeViewTest::TreeViewTest(QWidget *parent) : QWidget(parent),
                                              m_menu(nullptr)
{
        m_comboBox = new QComboBox(this);
        QStringList list;
        list << "样式1"
             << "样式2"
             << "样式3";
        for (int i = 0; i < list.count(); ++i)
        {
                m_comboBox->addItem(list.at(i));
        }
        m_comboBox->setFixedSize(100, 25);
        m_comboBox->setView(new QListView());

        connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeStyle(int)));

        m_treeView = new QTreeView(this);
        ItemDelegate *delegate = new ItemDelegate(this);
        TreeModel *model = new TreeModel(this);

        //    delegate->setView(m_treeView);
        model->setXML(":/treeview/config.xml");

        m_treeView->setModel(model);
        m_treeView->setItemDelegate(delegate);
        m_treeView->setHeaderHidden(true);
        m_treeView->setAnimated(true);
        m_treeView->setMouseTracking(true);
        m_treeView->setExpandsOnDoubleClick(true);
        m_treeView->setContextMenuPolicy(Qt::CustomContextMenu);
        m_treeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        connect(delegate, SIGNAL(expanded(const QModelIndex &)), this, SLOT(expanded(const QModelIndex &)));

        QVBoxLayout *mainLayout = new QVBoxLayout();
        mainLayout->addWidget(m_comboBox);
        mainLayout->addWidget(m_treeView);
        setLayout(mainLayout);

        connect(m_treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeViewCustomContextMenuRequested(QPoint)));

        m_treeView->expandAll();
        changeStyle(0);
}

TreeViewTest::~TreeViewTest()
{
}

void TreeViewTest::changeStyle(int index)
{
        QString styleOne = "QTreeView{\
        border: 1px solid lightgray;\
    }\
    QTreeView::item {\
            height: 40px;\
            border-radius: 2px;\
            border: 1px solid transparent;\
            background: transparent;\
            color: black;\
    }\
    QTreeView::item:hover {\
            border: 1px solid rgb(185, 215, 250);\
    }\
    QTreeView::item:selected {\
            border: 1px solid rgb(170, 190, 230);\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250), stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));\
    }\
    QTreeView::branch:open:has-children {\
            image: url(:/treeview/branchOpen.png);\
    }\
    QTreeView::branch:closed:has-children {\
            image: url(:/treeview/branchClose.png);\
    }";

        QString styleTwo = "QTreeView{\
            border: 1px solid lightgray;\
    }\
    QTreeView::item {\
            height: 40px;\
            border-radius: 2px;\
            border: 1px solid transparent;\
            background: transparent;\
            color: black;\
    }\
    QTreeView::item:has-children {\
            border: none;\
            border-bottom: 1px solid lightgray;\
    }\
    QTreeView::item:hover {\
            border: 1px solid rgb(170, 190, 230);\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250), stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));\
    }\
    QTreeView::item:selected {\
            border: 1px solid rgb(170, 190, 230);\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250), stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));\
    }\
    QTreeView::branch:open:has-children {\
            image: url(:/treeview/branchOpen2.png);\
    }\
    QTreeView::branch:closed:has-children {\
            image: url(:/treeview/branchClose2.png);\
    }";

        QString styleThree = "QTreeView{\
            border: 1px solid lightgray;\
    }\
    QTreeView::item {\
            height: 25px;\
            border: none;\
            background: transparent;\
            color: black;\
    }\
    QTreeView::item:hover {\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(255, 220, 130), stop: 0.5 rgb(255, 220, 130), stop: 1.0 rgb(255, 230, 150));\
    }\
    QTreeView::item:selected {\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(255, 200, 100), stop: 0.5 rgb(255, 230, 150), stop: 1.0 rgb(255, 240, 150));\
    }\
    QTreeView::branch:open:has-children {\
            image: url(:/treeview/branchOpen.png);\
    }\
    QTreeView::branch:closed:has-children {\
            image: url(:/treeview/branchClose.png);\
    }";

        if (index == 0)
        {
                m_treeView->setStyleSheet(styleOne);
        }
        else if (index == 1)
        {
                m_treeView->setStyleSheet(styleTwo);
        }
        else
        {
                m_treeView->setStyleSheet(styleThree);
        }
}

void TreeViewTest::expanded(QModelIndex index)
{
        bool bExpanded = m_treeView->isExpanded(index);
        if (!bExpanded)
        {
                m_treeView->expand(index);
        }
        else
        {
                m_treeView->collapse(index);
        }
}

void TreeViewTest::treeViewCustomContextMenuRequested(const QPoint &pos)
{
        if (!m_menu)
        {
                m_menu = new QMenu(this);

                QAction *expandAllAction = new QAction(m_menu);
                QAction *unExpandAllAction = new QAction(m_menu);
                expandAllAction->setText("全部展开");
                unExpandAllAction->setText("全部折叠");
                m_menu->addAction(expandAllAction);
                m_menu->addAction(unExpandAllAction);

                connect(expandAllAction, SIGNAL(triggered()), m_treeView, SLOT(expandAll()));
                connect(unExpandAllAction, SIGNAL(triggered()), m_treeView, SLOT(collapseAll()));
        }

        m_menu->exec(this->mapToGlobal(pos));
}
