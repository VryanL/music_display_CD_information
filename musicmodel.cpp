#include "musicmodel.h"

MusicModel::MusicModel(QObject *parent) : QStandardItemModel(parent)
{
    QStringList headers;
    headers << "Composer" << "Album Title" << "Replacement Value" << "Rating";
    setHorizontalHeaderLabels(headers);
}

void MusicModel::addRow(QString composer, QString album, double replacementValue, int rating)
{
    for (int row = 0; row < rowCount(); row++) {
        if (item(row,0)->text() == composer && item(row,1)->text() == album){
            QModelIndex iReplacment = index(row,2);
            QModelIndex iRating = index(row,3);
            setData(iReplacment, QString::number(replacementValue, 'f', 2));
            setData(iRating, QString::number(rating));
            return;
        }
    }
    QList<QStandardItem*> rowItems;

    QStandardItem *composerItem = new QStandardItem(composer);
    QStandardItem *albumItem = new QStandardItem(album);
    QStandardItem *replacementItem = new QStandardItem(QString::number(replacementValue, 'f', 2));
    QStandardItem *ratingItem = new QStandardItem(QString::number(rating));

    rowItems << composerItem << albumItem << replacementItem << ratingItem;
    appendRow(rowItems);

    updateRowColor(rowCount()-1);

}

void MusicModel::updateRowColor(int row)
{
    double replacementValue = index(row, 2).data().toDouble();
    Qt::GlobalColor color = replacementValue >= 200 ? Qt::red : Qt::white;
    for (int col = 0; col < columnCount(); ++col)
    {
        item(row, col)->setBackground(QBrush(color));
    }

}
