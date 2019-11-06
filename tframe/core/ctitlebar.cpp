#include "ctitlebar.h"
#include "ctoolbutton.h"
#include <QHBoxLayout>
#include <QMenu>

CTitleBar::CTitleBar(QWidget *parent) :
    QFrame(parent)
{
    initData();
    initUI();
    initConnect();
    m_pFixBtn->click();
}

CTitleBar::~CTitleBar()
{
    if(m_pMaxIcon) {
        delete m_pMaxIcon;
        m_pMaxIcon = nullptr;
    }

    if(m_pNormalIcon) {
        delete m_pNormalIcon;
        m_pNormalIcon = nullptr;
    }
}

void CTitleBar::initData()
{
    m_pLogoBtn = new CToolButton(this);
    m_pTitleLabel = new QLabel(this);
    m_pSettingBtn = new CToolButton(this);
    m_pSettingBtn->setFocusPolicy(Qt::NoFocus);
    m_pSkinBtn = new CToolButton(this);
    m_pFixBtn = new CToolButton(this);
    m_pFixBtn->setFocusPolicy(Qt::NoFocus);
    m_pMinBtn = new CToolButton(this);
    m_pMaxBtn = new CToolButton(this);
    m_pCloseBtn = new CToolButton(this);

    m_pLogoBtn->setFocusPolicy(Qt::NoFocus);
    m_pSettingBtn->setFocusPolicy(Qt::NoFocus);
    m_pSkinBtn->setFocusPolicy(Qt::NoFocus);
    m_pFixBtn->setFocusPolicy(Qt::NoFocus);
    m_pMinBtn->setFocusPolicy(Qt::NoFocus);
    m_pMaxBtn->setFocusPolicy(Qt::NoFocus);
    m_pCloseBtn->setFocusPolicy(Qt::NoFocus);

    m_bMax = true;
    m_bFix = false;
    m_pMaxIcon =  new QIcon(":/skin/icon/dark/maxi.png");
    m_pNormalIcon =  new QIcon(":/skin/icon/dark/full.png");
}

void CTitleBar::initUI()
{
    setTitleBarHeight(Title_Height);
    setObjectName("CTitleBar");
    setLogoButton(":/res/icon.png");
    setTitleLabel("T-Frame", "CTitleLabel");
    setSettingButton(":/skin/icon/dark/down.png");
    setSkinButton(":/skin/icon/dark/clothes.png");
    setFixButton(":/skin/icon/dark/lock.png");
    setMinButton(":/skin/icon/dark/minus.png");
    setMaxButton(":/skin/icon/dark/maxi.png");
    setCloseButton(":/skin/icon/dark/close.png", "close");

    QHBoxLayout* mainlayout = new QHBoxLayout(this);
    mainlayout->addWidget(m_pLogoBtn);
    mainlayout->addWidget(m_pTitleLabel);
    mainlayout->addStretch();
    mainlayout->addWidget(m_pSettingBtn);
    mainlayout->addWidget(m_pSkinBtn);
    mainlayout->addWidget(m_pFixBtn);
    mainlayout->addWidget(m_pMinBtn);
    mainlayout->addWidget(m_pMaxBtn);
    mainlayout->addWidget(m_pCloseBtn);
    mainlayout->setContentsMargins(0, 0, 5, 0);
    mainlayout->setSpacing(0);
    setLayout(mainlayout);
}

void CTitleBar::initConnect()
{
    connect(m_pSettingBtn, SIGNAL(clicked()), m_pSettingBtn, SLOT(showMenu()));
    connect(m_pSkinBtn, SIGNAL(clicked()), m_pSkinBtn, SLOT(showMenu()));
    connect(m_pFixBtn, SIGNAL(clicked()), this, SLOT(changeFix()));
    connect(m_pMaxBtn, SIGNAL(clicked()), this, SIGNAL(maximumed()));
    connect(m_pMinBtn, SIGNAL(clicked()), this, SIGNAL(minimuned()));
    connect(m_pCloseBtn, SIGNAL(clicked()), this, SIGNAL(closed()));
    connect(m_pMaxBtn, SIGNAL(clicked()), this, SLOT(switchMaxMin()));
}

void CTitleBar::changeFix()
{
    m_pFixBtn->setIcon(QIcon(m_bFix ? ":/skin/icon/dark/lock.png" : ":/skin/icon/dark/unlock.png"));
    m_bFix = !m_bFix;
}

bool CTitleBar::getFixedflag()
{
    return m_bFix;
}

void CTitleBar::clearChecked()
{
    m_pSettingBtn->setChecked(false);
    m_pSkinBtn->setChecked(false);
    m_pFixBtn->setChecked(false);
    m_pMinBtn->setChecked(false);
    m_pMaxBtn->setChecked(false);
    m_pCloseBtn->setChecked(false);
}

void CTitleBar::setSettingMenu(QMenu *menu)
{
    m_pSettingBtn->setMenu(menu);
}

void CTitleBar::switchMaxMin()
{
    m_bMax = !m_bMax;
    m_pMaxBtn->setIcon(m_bMax ? *m_pMaxIcon : *m_pNormalIcon);
}

void CTitleBar::changeSkin()
{

}

void CTitleBar::setTitleBarHeight(int height)
{
    setFixedHeight(height);
    m_pLogoBtn->setIconSize(QSize(height, height));
    m_pTitleLabel->setFixedHeight(height);
    m_pSettingBtn->setIconSize(QSize(height, height));
    m_pSkinBtn->setIconSize(QSize(height, height));
    m_pMinBtn->setIconSize(QSize(height, height));
    m_pMaxBtn->setIconSize(QSize(height, height));
    m_pCloseBtn->setIconSize(QSize(height, height));
}

void CTitleBar::setLogoButton(const char *str, const char *objectName)
{
    m_pLogoBtn->setIcon(QIcon(str));
    m_pLogoBtn->setIconSize(QSize(height(), height()));
    if(objectName)
        m_pLogoBtn->setObjectName(objectName);
}

CToolButton* CTitleBar::getLogoButton()
{
    return m_pLogoBtn;
}

void CTitleBar::setLogoButtonVisible(bool visible)
{
    m_pLogoBtn->setVisible(visible);
}

bool CTitleBar::isLogoButtonVisible()
{
    return m_pLogoBtn->isVisible();
}

void CTitleBar::setTitleLabel(QString str, const char *objectName)
{
    m_pTitleLabel->setText(str);
    m_pTitleLabel->setFixedHeight(height());
    if (objectName)
        m_pTitleLabel->setObjectName(objectName);
}

QLabel* CTitleBar::getTitleLabel()
{
    return m_pTitleLabel;
}

void CTitleBar::setTitleLabelVisible(bool visible)
{
    m_pTitleLabel->setVisible(visible);
}

bool CTitleBar::isTitleLabelVisible()
{
    return m_pTitleLabel->isVisible();
}

void CTitleBar::setSettingButton(const char *str, const char *objectName)
{
    m_pSettingBtn->setIcon(QIcon(str));
    m_pSettingBtn->setIconSize(QSize(height(), height()));
    if (objectName)
        m_pSettingBtn->setObjectName(objectName);
}

CToolButton* CTitleBar::getSettingButton()
{
    return m_pSettingBtn;
}

void CTitleBar::setSettingButtonVisible(bool visible)
{
    m_pSettingBtn->setVisible(visible);
}

bool CTitleBar::isSettingButtonVisible()
{
    return m_pSettingBtn->isVisible();
}

void CTitleBar::setSkinButton(const char *str, const char *objectName)
{
    m_pSkinBtn->setIcon(QIcon(str));
    m_pSkinBtn->setIconSize(QSize(height(), height()));
    if(objectName)
        m_pSkinBtn->setObjectName(objectName);
}

CToolButton* CTitleBar::getSkinButton()
{
    return m_pSkinBtn;
}

void CTitleBar::setSkinButtonVisible(bool visible)
{
    m_pSkinBtn->setVisible(visible);
}

bool CTitleBar::isSkinButtonVisible()
{
    return m_pSkinBtn->isVisible();
}

void CTitleBar::setFixButton(const char *str, const char *objectName)
{
    m_pFixBtn->setIcon(QIcon(str));
    m_pFixBtn->setIconSize(QSize(height(), height()));
    if(objectName)
        m_pFixBtn->setObjectName(objectName);
}

CToolButton* CTitleBar::getFixButton()
{
    return m_pFixBtn;
}

void CTitleBar::setFixButtonVisible(bool visible)
{
    m_pFixBtn->setVisible(visible);
}

bool CTitleBar::isFixButtonVisible()
{
    return m_pFixBtn->isVisible();
}

void CTitleBar::setMinButton(const char *str, const char *objectName)
{
    m_pMinBtn->setIcon(QIcon(str));
    m_pMinBtn->setIconSize(QSize(height(), height()));
    if (objectName)
        m_pMinBtn->setObjectName(objectName);
}

CToolButton* CTitleBar::getMinButton()
{
    return m_pMinBtn;
}

void CTitleBar::setMinButtonVisible(bool visible)
{
    m_pMinBtn->setVisible(visible);
}

bool CTitleBar::isMinButtonVisible()
{
    return m_pMinBtn->isVisible();
}

void CTitleBar::setMaxButton(const char *str, const char *objectName)
{

    m_pMaxBtn->setIcon(QIcon(str));
    m_pMaxBtn->setIconSize(QSize(height(), height()));
    if (objectName)
        m_pMaxBtn->setObjectName(objectName);
}

CToolButton* CTitleBar::getMaxButton()
{
    return m_pMaxBtn;
}

void CTitleBar::setMaxButtonVisible(bool visible)
{
    m_pMaxBtn->setVisible(visible);
}

bool CTitleBar::isMaxButtonVisible()
{
    return m_pMaxBtn->isVisible();
}

void CTitleBar::setCloseButton(const char *str, const char *objectName)
{
    m_pCloseBtn->setIcon(QIcon(str));
    m_pCloseBtn->setIconSize(QSize(height(), height()));
    if (objectName)
        m_pCloseBtn->setObjectName(objectName);
}

CToolButton* CTitleBar::getCloseButton()
{
    return m_pCloseBtn;
}

void CTitleBar::setCloseButtonVisible(bool visible)
{
    m_pCloseBtn->setVisible(visible);
}

bool CTitleBar::isCloseButtonVisible()
{
    return m_pCloseBtn->isVisible();
}
