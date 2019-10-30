﻿#include "searchedit.h"

#include <QLineEdit>
#include <QToolButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QFocusEvent>
#include <QApplication>
#include <QClipboard>

SearchEdit::SearchEdit(QWidget *parent)
    : QLineEdit(parent)
{
    this->initForm();
    this->initConnect();
    this->translator();
}

SearchEdit::~SearchEdit()
{
}

void SearchEdit::initForm()
{
    this->setFixedSize(260, 24);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    m_tbnSearch = new QToolButton(this);

    m_tbnSearch->setFixedSize(25, 24);
    m_tbnSearch->setAutoRaise(true);
    m_tbnSearch->setCursor(Qt::PointingHandCursor);
    m_tbnSearch->setStyleSheet("QToolButton{border-image:url(:/component/search_dark.png);"
                               "background:transparent;}");

    m_mainLayout = new QHBoxLayout();
    m_mainLayout->addStretch();
    m_mainLayout->addWidget(m_tbnSearch);

    //设置文本边框，防止文本覆盖按钮
    setTextMargins(0, 0, 20, 0);
    setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setContentsMargins(2, 2, 4, 0);
    this->setLayout(m_mainLayout);

    setStyleSheet("height:24px;border:1px ;border-radius:6px;"
                  "background-color:#E1DDDD");
}

void SearchEdit::initConnect()
{
    connect(m_tbnSearch, SIGNAL(clicked(bool)),
            this, SLOT(searchContent()));
    connect(this, SIGNAL(returnPressed()), this, SLOT(searchContent()));
}

//翻译控件
void SearchEdit::translator()
{
    setPlaceholderText(QStringLiteral("请输入要查找的内容"));
    setToolTip(QStringLiteral("查找内容"));
    m_tbnSearch->setToolTip(QStringLiteral("查找"));
}

void SearchEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);

    setStyleSheet("height:24px;border:1px ;border-radius:6px;"
                  "background-color:#FFFFFF");
    m_tbnSearch->setStyleSheet("QToolButton{border-image:url(:/component/search.png);"
                               "background:transparent;}");
}

void SearchEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    setPlaceholderText(QStringLiteral("请输入要查找的内容"));
    setStyleSheet("height:24px;border:1px ;border-radius:6px;"
                  "background-color:#CCC7C7");
    m_tbnSearch->setStyleSheet("QToolButton{border-image:url(:/component/search_dark.png);"
                               "background:transparent;}");
}

void SearchEdit::searchContent()
{
    QString str = text().isEmpty() ? placeholderText() : text();

    emit search(str);
}

#include "moc_searchedit.cpp"
