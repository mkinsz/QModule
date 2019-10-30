#ifndef SEARCHEDIT_H
#define SEARCHEDIT_H
#include <QLineEdit>
#include <QWidget>
class QToolButton;
class QHBoxLayout;
class QWidget;

class SearchEdit : public QLineEdit
{
    Q_OBJECT

public:
    SearchEdit(QWidget *parent = nullptr);
    ~SearchEdit();

    void initForm();
    void initConnect();
    void translator();

protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

private Q_SLOTS:
    void searchContent();

Q_SIGNALS:
    void search(const QString &test);

private:
    QToolButton *m_tbnSearch;
    QHBoxLayout *m_mainLayout;
};

#endif // SEARCHEDIT_H
