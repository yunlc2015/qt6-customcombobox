#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelcombobox.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    ui->frameBox->setLayout(layout);

    _comboBox = new ModelComboBox(this);
    layout->addWidget(_comboBox);
    connect(_comboBox, &QComboBox::currentIndexChanged, this, [this](int index){
        _comboBox->setText( _comboBox->getModelText(index) );
    });

    QList<Entity> modelList;
    modelList.append(Entity{.name="test1",.summary="summary1"});
    modelList.append(Entity{.name="test2",.summary="summary2"});
    modelList.append(Entity{.name="test3",.summary="summary3"});

    _comboBox->setList(modelList);
    _comboBox->setCurrentIndex(0);
    _comboBox->setText("-- 请选择 --");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (_comboBox->currentIndex() == 0) {
        QMessageBox::information(this, "", "请选择一项");
        return;
    }

    Entity model = _comboBox->currentModel();
    QMessageBox::information(this, "", QString("选择了：%1").arg(model.name));
}

