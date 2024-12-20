#ifndef MUSICMODEL_H
#define MUSICMODEL_H

#include <QStandardItemModel>


class MusicModel: public QStandardItemModel
{

public:
    MusicModel(QObject *parent = nullptr);
    void addRow(QString composer, QString album, double replacementValue, int rating);
    void updateRowColor(int row);

private:

};

#endif // MUSICMODEL_H
