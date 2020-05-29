#include "searchedit.h"
#include <QPushButton>
#include <QHBoxLayout>

SearchEdit::SearchEdit(QWidget *parent) : QLineEdit(parent)
{
    m_pSearchBtn = new QPushButton(this);
    m_pSearchBtn->setObjectName("SearchButton");
    m_pSearchBtn->setCursor(Qt::PointingHandCursor);
    m_pSearchBtn->setFixedSize(20, 20);
    m_pSearchBtn->setToolTip(QStringLiteral("搜索"));

    m_pDeleteBtn = new QPushButton(this);
    m_pDeleteBtn->setObjectName("DeleteButton");
    m_pDeleteBtn->setCursor(Qt::ArrowCursor);
    m_pDeleteBtn->setFixedSize(16, 16);
    m_pDeleteBtn->setToolTip(QStringLiteral("删除"));

    QMargins margins = textMargins();
    setTextMargins(margins.left(), margins.top(), m_pSearchBtn->width(), margins.bottom());

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(m_pDeleteBtn);
    pSearchLayout->addSpacing(10);
    pSearchLayout->addWidget(m_pSearchBtn);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pSearchLayout);
//    setPlaceholderText(QStringLiteral("请输入搜索内容"));

    m_pDeleteBtn->setVisible(false);
    m_pDeleteBtn->setEnabled(false);

    connect(m_pSearchBtn, SIGNAL(clicked()),   this, SLOT(Slt_Search()));
    connect(m_pDeleteBtn, SIGNAL(clicked()), this, SLOT(Slt_Delete()));
    connect(this,		   SIGNAL(returnPressed()), this, SLOT(Slt_Search()));
    connect(this,		   SIGNAL(textChanged(const QString&)), this, SLOT(Slt_TextChanged(const QString&)));

    m_pSearchBtn->setStyleSheet("QPushButton{background: url(:/res/search.png) no-repeat center; background-color:transparent;}");
    m_pDeleteBtn->setStyleSheet("QPushButton{background: url(:/res/clear.png) no-repeat center; background-color:transparent;}");
}

void SearchEdit::Slt_Search()
{
    emit Sig_Search(text());
}

void SearchEdit::Slt_Delete()
{
    clear();
    emit Sig_Delete();
}

void SearchEdit::Slt_TextChanged(const QString &szText)
{
    Q_UNUSED(szText)
    m_pDeleteBtn->setEnabled(!text().isEmpty());
    m_pDeleteBtn->setVisible(!text().isEmpty());
    if(text().isEmpty()) emit Sig_Delete();
}
