#ifndef FIGHTLIST_H
#define FIGHTLIST_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class FightList;
}

class FightList : public QDialog
{
    Q_OBJECT

public:
    explicit FightList(QWidget *parent = nullptr);
    ~FightList();
    QList<int> fightList;

private slots:
    void on_pushButton_Ok_clicked();
    void CreateItem(QListWidget * TheList , QString& TheText);
public slots:
    void SetData();
    void fightDetail(QString idFight);

private:
    Ui::FightList *ui;
};

#endif // FIGHTLIST_H
