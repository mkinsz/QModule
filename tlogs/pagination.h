#ifndef PAGINATION_H
#define PAGINATION_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class Pagination : public QWidget {
    Q_OBJECT
public:
    explicit Pagination(QWidget *parent = nullptr, int m_height = 30);

    int getCurrentPage();

    void setCurrentPage(int m_current);

    void show();

    void setTotalPages(int m_total);
    void setButtonsSize(int width, int m_height);
    void setButtonsSize(const QSize &size);
    void setStyleSheet(const QString &m_styleSheet);

    void setPreviousButton(const QPixmap &icon, const QString &text, const QSize &size);
    void setPreviousButton(const QString &text, const QSize &size);

    void setNextButton(const QPixmap &icon, const QString &text, const QSize &size);
    void setNextButton(const QString &text, const QSize &size);

    void updateTotalPages(int m_total);

signals:
    void onPageChange(int m_current);

public slots:

protected:
    void paintEvent(QPaintEvent*) override;

private:
    int m_height;
    int m_total;
    int m_previous;
    int m_current;
    int m_totalButtons;

    QSize m_buttonSize;
    QPushButton *m_pNext;
    QPushButton *m_pPrevious;
    QVector<QPushButton*> m_buttons;
    QString m_styleSheet;
    QHBoxLayout *m_pLayout;

    void calculate();
    void setButton(int index, int pageNumber);
    void applyStyleSheet(QPushButton *button);
    void applySize(QPushButton *button);
};


#endif // PAGINATION_H
