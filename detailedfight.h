#ifndef DETAILEDFIGHT_H
#define DETAILEDFIGHT_H

#include <QDialog>

namespace Ui {
class DetailedFight;
}

class DetailedFight : public QDialog
{
    Q_OBJECT

public:
    explicit DetailedFight(QWidget *parent = nullptr);
    ~DetailedFight();

private:
    Ui::DetailedFight *ui;
};

#endif // DETAILEDFIGHT_H
