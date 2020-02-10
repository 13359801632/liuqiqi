#ifndef DENGLU_H
#define DENGLU_H

#include <QWidget>

namespace Ui {
class denglu;
}

class denglu : public QWidget
{
    Q_OBJECT

public:
    explicit denglu(QWidget *parent = 0);
    ~denglu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::denglu *ui;
};

#endif // DENGLU_H
