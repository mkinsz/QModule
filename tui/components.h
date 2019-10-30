#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <QWidget>

namespace Ui
{
class Components;
}

class NotifyManager;
class Components : public QWidget
{
    Q_OBJECT

public:
    explicit Components(QWidget *parent = nullptr);
    ~Components();

private:
    Ui::Components *ui;

    NotifyManager *m_nm;
};

#endif // COMPONENTS_H
