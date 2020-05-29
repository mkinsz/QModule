#ifndef SEARCHEDIT_H
#define SEARCHEDIT_H

#include <QLineEdit>

class QPushButton;
class SearchEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SearchEdit(QWidget *parent = nullptr);

Q_SIGNALS:
    void Sig_Search(const QString &str);
    void Sig_Delete();

public Q_SLOTS:
    void Slt_Search();
    void Slt_Delete();
    void Slt_TextChanged(const QString& szText);

private:
    QPushButton *m_pSearchBtn;
    QPushButton *m_pDeleteBtn;

};

#endif // SEARCHEDIT_H
