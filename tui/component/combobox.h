#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class ComboBoxPrivate;
class ComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit ComboBox(QWidget *parent = nullptr);
    ~ComboBox();

    void setCurrentIndex(int index);
    int currentIndex() const;

    QString currentName() const;
    QColor currentColor1() const;
    QColor currentColor2() const;

    static QPair<QColor, QColor> colorPair(int index);

    void showPopup();
    void hidePopup();

protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);
    QSize minimumSizeHint() const;

private slots:
    void onActivated(int index);

private:
    ComboBoxPrivate *m_dptr;

    Q_DISABLE_COPY(ComboBox)
};
#endif // GRADIENTCOMBOBOX_H
