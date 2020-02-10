#ifndef PERSON_H
#define PERSON_H

#include <QWidget>

namespace Ui {
class person;
}

class person : public QWidget
{
    Q_OBJECT

public:
    explicit person(QWidget *parent = 0);
    ~person();
    void init(QString sno,QString sname);

private:
    Ui::person *ui;
};

#endif // PERSON_H
