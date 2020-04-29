#ifndef CTITLEBAR_H
#define CTITLEBAR_H

#include <QFrame>
#include <QLabel>


#define Title_Height 25

class QMenu;
class CToolButton;
class QPushButton;
class CTitleBar : public QFrame
{
    Q_OBJECT
public:
    explicit CTitleBar(QWidget *parent = nullptr);
    ~CTitleBar();

    bool getFixedflag();

    void setTitleBarHeight(int height);
    void setSettingMenu(QMenu* menu);

    void setLogoButton(const char *str, const char *objectName=nullptr);
    QPushButton* getLogoButton();
    void setLogoButtonVisible(bool visible);
    bool isLogoButtonVisible();

    void setTitleLabel(QString str, const char *objectName=nullptr);
    QLabel* getTitleLabel();
    void setTitleLabelVisible(bool visible);
    bool isTitleLabelVisible();

    void setSettingButton(const char *str, const char *objectName=nullptr);
    CToolButton* getSettingButton();
    void setSettingButtonVisible(bool visible);
    bool isSettingButtonVisible();

    void setSkinButton(const char *str, const char *objectName=nullptr);
    CToolButton* getSkinButton();
    void setSkinButtonVisible(bool visible);
    bool isSkinButtonVisible();

    void setFixButton(const char *str, const char *objectName=nullptr);
    CToolButton* getFixButton();
    void setFixButtonVisible(bool visible);
    bool isFixButtonVisible();

    void setMinButton(const char *str, const char *objectName=nullptr);
    CToolButton* getMinButton();
    void setMinButtonVisible(bool visible);
    bool isMinButtonVisible();

    void setMaxButton(const char *str, const char *objectName=nullptr);
    CToolButton* getMaxButton();
    void setMaxButtonVisible(bool visible);
    bool isMaxButtonVisible();

    void setCloseButton(const char *str, const char *objectName=nullptr);
    CToolButton* getCloseButton();
    void setCloseButtonVisible(bool visible);
    bool isCloseButtonVisible();

signals:
    void maximumed();
    void minimuned();
    void normaled();
    void closed();

public slots:
    void switchMaxMin();
    void changeSkin();
    void clearChecked();
    void changeFix();

private:
    void initData();
    void initEvt();
    void initUi();

private:
    QIcon* m_pLogoIcon;
    QIcon* m_pSettingIcon;
    QIcon* m_pSkinIcon;
    QIcon* m_pMinIcon;
    QIcon* m_pMaxIcon;
    QIcon* m_pNormalIcon;
    QIcon* m_pCloseIcon;
    QLabel* m_pTitleLabel;

    QPushButton* m_pLogoBtn;
    CToolButton* m_pSettingBtn;
    CToolButton* m_pSkinBtn;
    CToolButton* m_pFixBtn;
    CToolButton* m_pMinBtn;
    CToolButton* m_pMaxBtn;
    CToolButton* m_pCloseBtn;

    bool m_bMax;
    bool m_bFix;
};

#endif // CTITLEBAR_H
