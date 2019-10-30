#include "ultrasound.h"
#include <QFile>
#include "pgm.h"
#include <QDebug>
#include <QApplication>
#include <QDir>
#include <QImageReader>
#include <QImageIOHandler>

Ultrasound::Ultrasound(QWidget *parent) : QWidget(parent)
{
    //! ------------------------read-------------------------------
    //    FILE *fp = nullptr;
    //    int w = 384;
    //    int h = 256;
    //    fopen_s(&fp,"a.pgm","rb");
    //    if(fp){
    //        fscanf_s(fp,"%*c%*c\n%d %d\n%*d\n",&w,&h);
    //        long pos = ftell(fp);
    //        pData = (unsigned char*)malloc(w*h*sizeof(unsigned char));
    //        fread(pData, w*h*sizeof(unsigned char) , 1, fp);
    //        long end = ftell(fp) - pos;
    //        fclose(fp);
    //    }
    //    m_pImage = new QImage(pData, w, h , QImage::Format_Grayscale8);

    //! --------------------------save-----------------------------
    //    write_pgm_file("b.pgm", w, h, pData);

    //! -------------Tell the IO that image's format is pgm-------------
    //    qDebug() << QDir::currentPath();
    //    QFile file(":/ultrasound/a.pgm");
    //    file.open(QIODevice::ReadOnly);
    //    QByteArray array = file.readAll();
    //    m_image.loadFromData(array, "pgm");
    //    file.close();

    m_image.load(":/ultrasound/a.pgm", "pgm");
    //    m_image.save("b.bmp", "bmp");

    //! -------------Don't have the header of pgm format---------------
    QFile file(":/ultrasound/c.dat");
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Open failed...";
    m_array = file.readAll();
    m_pImage = new QImage((uchar *)m_array.data(), 289, 384, 289, QImage::Format_Grayscale8);
    qDebug() << m_pImage->size();
    file.close();

    //! ------------rotate 90 degrees------------
    m_trans.rotate(90);
    m_new = m_pImage->transformed(m_trans, Qt::SmoothTransformation);

    //! -------------------QImageReader & Transform------------------
    //    QImageReader reader(":/ultrasound/b.pgm");
    //    reader.setAutoTransform(true);
    //    m_new = reader.read();
    //    QImageIOHandler::Transformations transformation;
    //    if(!m_new.isNull()) {
    //        transformation = reader.transformation();
    //        qDebug() << "transformation is " << transformation;

    //        if(transformation == QImageIOHandler::TransformationRotate90) {
    //            QTransform matrix;
    //            matrix.rotate(90);
    //            m_new = m_new.transformed(matrix);
    //        }
    //    }
}

Ultrasound::~Ultrasound()
{
    free(pData);
    pData = nullptr;

    if (m_pImage)
        delete m_pImage;
    m_pImage = nullptr;
}

void Ultrasound::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter p(this);
    p.drawImage(0, 0, *m_pImage);
    //    p.drawImage(300, 0, m_image);
    p.drawImage(300, 0, m_new);
}
