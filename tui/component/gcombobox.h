#ifndef GCOMBOBOX_H
#define GCOMBOBOX_H

#include <QComboBox>

class GComboBoxPrivate;
class GComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit GComboBox(QWidget *parent = nullptr);
    ~GComboBox();

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
    GComboBoxPrivate *m_dptr;

    Q_DISABLE_COPY(GComboBox)
};

#endif // GCOMBOBOX_H
