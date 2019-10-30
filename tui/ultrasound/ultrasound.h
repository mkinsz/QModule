#ifndef ULTRASOUND_H
#define ULTRASOUND_H
#include <QImage>
#include <QPainter>
#include <QWidget>

class Ultrasound : public QWidget
{
public:
    Ultrasound(QWidget *parent = nullptr);
    ~Ultrasound();

    void paintEvent(QPaintEvent *e);

private:
    QImage *m_pImage = nullptr;
    QImage m_image, m_new;
    QByteArray m_array;
    QTransform m_trans;
    unsigned char *pData = nullptr;
};

#endif // ULTRASOUND_H
