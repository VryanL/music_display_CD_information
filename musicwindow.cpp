#include "musicwindow.h"

MusicWindow::MusicWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Music");
    QWidget *mainWidget = new QWidget(this);

    QVBoxLayout *composLayout = new QVBoxLayout();
    composLEdit = new QLineEdit();
    composLayout->addWidget(new QLabel("Composer"));
    composLayout->addWidget(composLEdit);
    composLayout->addStretch();

    QVBoxLayout *albumLayout = new QVBoxLayout();
    albumLEdit = new QLineEdit();
    albumLayout->addWidget(new QLabel("Album title"));
    albumLayout->addWidget(albumLEdit);
    albumLayout->addStretch();

    QVBoxLayout *replaceLayout = new QVBoxLayout();
    replaceSEdit = new QDoubleSpinBox();
    replaceSEdit->setDecimals(2);
    replaceSEdit->setMinimum(0.00);
    replaceSEdit->setSingleStep(0.01);
    replaceSEdit->setMaximum(std::numeric_limits<int>::max());
    replaceLayout->addWidget(new QLabel("Replacement cost(R)"));
    replaceLayout->addWidget(replaceSEdit);
    replaceLayout->addStretch();

    QVBoxLayout *ratingLayout = new QVBoxLayout();
    ratingSEdit = new QSpinBox();
    ratingSEdit->setMinimum(0);
    ratingSEdit->setMaximum(100);
    ratingLayout->addWidget(new QLabel("Rating"));
    ratingLayout->addWidget(ratingSEdit);
    ratingLayout->addStretch();

    QVBoxLayout *addButLayout = new QVBoxLayout();
    addButton = new QPushButton("&Add");
    addButton->setDisabled(true);
    addButLayout->addWidget(new QLabel(""));
    addButLayout->addWidget(addButton);
    addButLayout->addStretch();

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addLayout(composLayout,1);
    topLayout->addLayout(albumLayout,1);
    topLayout->addLayout(replaceLayout,1);
    topLayout->addLayout(ratingLayout);
    topLayout->addLayout(addButLayout);

    mView = new QTableView();
    mModel = new MusicModel();
    mDelegate = new MusicDelegate();
    mView->setModel(mModel);
    mView->setItemDelegate(mDelegate);
    mView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    delButton = new QPushButton("&Delete");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(mView,1);
    mainLayout->addWidget(delButton,0,Qt::AlignRight);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(delButton, SIGNAL(clicked(bool)), this, SLOT(deleteRow()));
    connect(composLEdit, SIGNAL(textChanged(QString)), this, SLOT(isThereText()));
    connect(albumLEdit, SIGNAL(textChanged(QString)), this, SLOT(isThereText()));

    connect(mView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortColumn(int)));
    connect(mModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(dataChange(QStandardItem*)));

}

MusicWindow::~MusicWindow()
{

}

void MusicWindow::add()
{
    QString composer = composLEdit->text();
    QString album = albumLEdit->text();
    double replace = replaceSEdit->value();
    int rating = ratingSEdit->value();

    mModel->addRow(composer, album, replace, rating);

    composLEdit->setText("");
    albumLEdit->setText("");
    replaceSEdit->setValue(0.00);
    ratingSEdit->setValue(0);
    composLEdit->setFocus();
}

void MusicWindow::deleteRow()
{
    QModelIndexList indexes = mView->selectionModel()->selectedRows();
    for (int i = indexes.count() - 1; i >= 0; --i)
    {
        mModel->removeRow(indexes.at(i).row());
    }
}

void MusicWindow::isThereText()
{
    if (composLEdit->text().length() > 0 && albumLEdit->text().length() > 0)
        addButton->setEnabled(true);
    else
        addButton->setDisabled(true);
}

void MusicWindow::sortColumn(int column)
{
    if (mModel)
    {
        if (altAscendDescend)
        {
            mModel->sort(column,Qt::AscendingOrder);
            altAscendDescend = false;
        }
        else
        {
            mModel->sort(column,Qt::DescendingOrder);
            altAscendDescend = true;
        }
    }
}

void MusicWindow::dataChange(QStandardItem *item)
{

    int i = item->index().column();
    switch (i) {
    case 0:
    case 1:
        break;
    case 2:{
        double replace = item->text().toDouble();
        item->setData(QString::number(replace, 'f', 2), Qt::DisplayRole);
        mModel->updateRowColor(item->index().row());
        break;
    }
    case 3: {
        mView->repaint();
        break;
    }
    default:
        break;
    }

}


