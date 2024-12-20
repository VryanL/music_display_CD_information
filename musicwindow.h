#ifndef MUSICWINDOW_H
#define MUSICWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

#include "musicmodel.h"
#include "musicdelegate.h"
#include <QTableView>
#include <QHeaderView>
#include <QRect>

class MusicWindow : public QMainWindow
{
    Q_OBJECT

public:
    MusicWindow(QWidget *parent = nullptr);
    ~MusicWindow();

private:
    QLineEdit *composLEdit;
    QLineEdit *albumLEdit;
    QDoubleSpinBox *replaceSEdit;
    QSpinBox *ratingSEdit;
    QPushButton *addButton;
    QPushButton *delButton;

    MusicModel *mModel;
    MusicDelegate *mDelegate;
    QTableView *mView;

    bool altAscendDescend = true;

private slots:
    void add();
    void deleteRow();
    void isThereText();
    void sortColumn(int column);
    void dataChange(QStandardItem *item);

};
#endif // MUSICWINDOW_H
