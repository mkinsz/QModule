#include "pagination.h"

#include <QPainter>
#include <QStyleOption>
#include <QSizePolicy>

Pagination::Pagination(QWidget *parent, int height) : QWidget(parent),
    m_height(height) {

    m_pLayout = new QHBoxLayout(this);
    m_pLayout->setContentsMargins(6, 0, 6, 0);
    m_pLayout->setSpacing(0);

    m_pPrevious = new QPushButton(this);
    m_pNext = new QPushButton(this);

    setMinimumHeight(height);

    m_previous = -1;
    m_current = 1;
    m_totalButtons = 7;
}

int Pagination::getCurrentPage() {
    return m_current;
}

void Pagination::setButtonsSize(int width, int height) {
    m_buttonSize = QSize(width, height);
}

void Pagination::setButtonsSize(const QSize &size) {
    m_buttonSize = size;
}

void Pagination::setNextButton(const QPixmap &icon, const QString &text, const QSize &size) {
    m_pNext->setText(text);
    m_pNext->setIcon(icon);
    m_pNext->setMinimumSize(size);
    m_pNext->setMaximumSize(size);
}

void Pagination::setNextButton(const QString &text, const QSize &size) {
    setNextButton(QPixmap(), text, size);
}

void Pagination::setPreviousButton(const QPixmap &icon, const QString &text, const QSize &size) {
    m_pPrevious->setText(text);
    m_pPrevious->setIcon(icon);
    m_pPrevious->setMinimumSize(size);
    m_pPrevious->setMaximumSize(size);
}

void Pagination::setPreviousButton(const QString &text, const QSize &size) {
    setNextButton(QPixmap(), text, size);
}

void Pagination::setCurrentPage(int currentPage) {
    if (currentPage > m_total) {
        currentPage = 1;
    }
    m_current = currentPage;
}

void Pagination::setTotalPages(int totalPages) {
    m_total = totalPages;
    m_current = 1;
}

void Pagination::setStyleSheet(const QString &styleSheet) {
    m_styleSheet = styleSheet;
}

void Pagination::updateTotalPages(int totalPages) {
    if (m_total == totalPages) {
        return;
    }

    m_total = totalPages;
    if (m_current > totalPages) {
        m_current = 1;
    }
    m_previous = -1;
    m_totalButtons = 7;

    m_buttons.clear();

    while (QLayoutItem* item = m_pLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    m_pPrevious = new QPushButton(this);
    m_pNext = new QPushButton(this);

    show();
}

void Pagination::show() {
    QSpacerItem *horizontalSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_pLayout->addItem(horizontalSpacer1);

    m_pPrevious->setText("<");
    m_pPrevious->setEnabled(false);
    m_pPrevious->setVisible(false);
    connect(m_pPrevious, &QPushButton::clicked, [&](){
        m_previous = m_current;
        m_current -= 1;

        calculate();

        emit onPageChange(m_current);
    });
    applyStyleSheet(m_pPrevious);
    applySize(m_pPrevious);

    m_pNext->setText(">");
    m_pNext->setEnabled(false);
    m_pNext->setVisible(false);
    connect(m_pNext, &QPushButton::clicked, [&]() {
        m_previous = m_current;
        m_current += 1;

        calculate();

        emit onPageChange(m_current);
    });
    applyStyleSheet(m_pNext);
    applySize(m_pNext);

    if (m_total > 1) {
        m_pPrevious->setVisible(true);
        m_pLayout->addWidget(m_pPrevious);
    }

    if (m_totalButtons > m_total) {
        m_totalButtons = m_total;
    }

    for (int i = 0; i < m_totalButtons; i++) {
        QPushButton *button = new QPushButton(this);
        button->setMinimumSize(24, 24);
        button->setCheckable(true);
        applyStyleSheet(button);
        applySize(button);

        int pageNumber = -1;
        if (m_total >= m_totalButtons + 1) {
            if (i == 0) {
                button->setProperty("page", 1);
                pageNumber = 1;
            } else if (i == m_totalButtons - 1) {
                button->setProperty("page", m_total);
                pageNumber = m_total;
            } else {
                if (i <= 4) {
                    pageNumber = i + 1;
                }
            }
        } else {
            pageNumber = i + 1;
        }

        button->setProperty("page", pageNumber);
        if (pageNumber > 0) {
            button->setText(QString::number(pageNumber));
        } else {
            button->setText("...");
        }

        connect(button, &QPushButton::clicked, [this, button]() {
            QVariant variant = button->property("page");
            int pageNumber = variant.toInt();
            int newCurrentPage = m_current;

            if (pageNumber > 0) {
                newCurrentPage = pageNumber;
            } else if (pageNumber == -1) {
                newCurrentPage = m_current + 3;
            } else if (pageNumber == -2) {
                newCurrentPage = m_current - 3;
            }

            if (newCurrentPage < 1) {
                newCurrentPage = 1;
            } else if (newCurrentPage > m_total) {
                newCurrentPage = m_total;
            }

            m_previous = m_current;
            m_current = newCurrentPage;

            calculate();

            emit onPageChange(m_current);
        });
        m_pLayout->addWidget(button);
        m_buttons.append(button);
    }

    if (m_total > 1) {
        m_pNext->setVisible(true);
        m_pNext->setEnabled(true);
        m_pLayout->addWidget(m_pNext);
    }
//    QSpacerItem *horizontalSpacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Preferred);
//    m_pLayout->addItem(horizontalSpacer2);

    calculate();
}

void Pagination::calculate() {

    if (m_total > m_totalButtons) {
        bool button1 = false;
        bool button5 = false;
        if (m_current - 1 > 3) {
            button1 = true;
            setButton(1, -2);
        } else {
            setButton(1, 2);
            setButton(2, 3);
            setButton(3, 4);
            setButton(4, 5);
        }

        if (m_total - m_current > 3) {
            button5 = true;
            setButton(5, -1);
        } else {
            setButton(2, m_total - 4);
            setButton(3, m_total - 3);
            setButton(4, m_total - 2);
            setButton(5, m_total - 1);
        }

        if (button1 && button5) {
            setButton(2, m_current - 1);
            setButton(3, m_current);
            setButton(4, m_current + 1);
        }
    }

    for (auto button : m_buttons) {
        int page = button->property("page").toInt();
        if (m_current == page) {
            button->setEnabled(false);
            button->setChecked(true);
        } else {
            button->setEnabled(true);
            button->setChecked(false);
        }
    }

    m_pPrevious->setEnabled(m_current > 1);
    m_pNext->setEnabled(m_current < m_total);
}

void Pagination::paintEvent(QPaintEvent *) {
    QStyleOption styleOption;
    styleOption.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOption, &painter, this);
}

void Pagination::applySize(QPushButton *button) {
    if (m_buttonSize.isValid()) {
        button->setMinimumSize(m_buttonSize);
        button->setMaximumSize(QSize(m_buttonSize.width()*4, m_buttonSize.height()));
    }
}

void Pagination::applyStyleSheet(QPushButton *button) {
    if (!m_styleSheet.isEmpty()) {
        button->setStyleSheet(m_styleSheet);
    }
}

void Pagination::setButton(int index, int pageNumber) {

    QString text;
    if (pageNumber > 0) {
        text = QString::number(pageNumber);
    } else {
        text = "...";
    }

    QPushButton *button = m_buttons.at(index);
    button->setProperty("page", pageNumber);
    button->setText(text);
}
