#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "expander.h"

Expander::Expander(QWidget *parent)
    : QWidget(parent)
{
    button = new QPushButton();
    button->setObjectName("expander_button");
    button->setText("Expander");
    button->setIcon(QIcon(":/arrow-expanded.png"));
    button->setFlat(true);
    button->setStyleSheet("text-align: left; font-weight: bold; border: none;");

    connect(button, SIGNAL(clicked()), this, SLOT(onPressed()));

    stackWidget = new QStackedWidget();

    layout = new QVBoxLayout();
    layout->addWidget(button, 0, Qt::AlignTop);
    layout->addWidget(stackWidget);
    setLayout(layout);
}

void Expander::onPressed()
{

    if (expanded)
    {
        expanded = false;
        button->setIcon(QIcon(":/expander/arrow.png"));
        stackWidget->hide();

        resize(layout->sizeHint().width(), 20);
        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        updateGeometry();
    }
    else
    {
        expanded = true;
        button->setIcon(QIcon(":/expander/arrow-expanded.png"));
        stackWidget->show();

        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        updateGeometry();
    }

    emit expanderChanged(expanded);
}

QSize Expander::sizeHint() const
{
    return QSize(200, 20);
}

void Expander::addPage(QWidget *page)
{
    insertPage(count(), page);
}

void Expander::removePage(int index)
{
    Q_UNUSED(index)
}

int Expander::count() const
{
    return stackWidget->count();
}

int Expander::currentIndex() const
{
    return stackWidget->currentIndex();
}

void Expander::insertPage(int index, QWidget *page)
{
    page->setParent(stackWidget);
    stackWidget->insertWidget(index, page);
}

void Expander::setCurrentIndex(int index)
{
    if (index != currentIndex())
    {
        stackWidget->setCurrentIndex(index);
        emit currentIndexChanged(index);
    }
}

QWidget *Expander::widget(int index)
{
    return stackWidget->widget(index);
}

void Expander::setExpanderTitle(QString const &newTitle)
{
    button->setText(newTitle);
}

QString Expander::expanderTitle() const
{
    return button->text();
}

void Expander::setExpanded(bool flag)
{
    if (flag != expanded)
        onPressed();
    else
        expanded = flag;
}

bool Expander::isExpanded() const
{
    return expanded;
}
