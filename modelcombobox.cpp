#include "modelcombobox.h"
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

CustomItemView::CustomItemView(QWidget *parent)
    : QFrame(parent)
{
    _labelName = new QLabel(this);
    QFont font = _labelName->font();
    font.setPointSize(12);
    font.setBold(true);
    _labelName->setFont(font);
    _labelName->setText("-- 请选择 --");

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setContentsMargins(8, 8, 8, 8);
    vlayout->setSpacing(2);
    vlayout->addWidget(_labelName);

    this->setLayout(vlayout);
}

QString CustomItemView::text() const
{
    return "-- 请选择 --";
}

ModelItemView::ModelItemView(QWidget *parent)
    : CustomItemView(parent)
{
    _labelSummary = new QLabel(this);
    _labelSummary->setWordWrap(true);
    QFont font = _labelSummary->font();
    font.setPointSize(11);
    _labelSummary->setFont(font);

    this->layout()->addWidget(_labelSummary);
}

QString ModelItemView::text() const
{
    return _model.name;
}

void ModelItemView::setModel(const Entity &model)
{
    _model = model;
    _labelName->setText(model.name);
    _labelSummary->setText(model.summary);

    this->adjustSize();
}

ModelComboBox::ModelComboBox(QWidget *parent)
    : QComboBox(parent)
{
    QFont font = this->font();
    font.setPointSize(12);
    this->setFont(font);

    _listWidget = new QListWidget(this);

    this->setEditable(true);
    this->lineEdit()->setReadOnly(true);  // 可选：禁止用户直接编辑
}

void ModelComboBox::setText(const QString &text)
{
    this->setEditText(text);
}

void ModelComboBox::setList(const QList<Entity> &list)
{
    _modelList = list;

    CustomItemView *itemView = new CustomItemView(this);
    QListWidgetItem *item = new QListWidgetItem(_listWidget);
    _listWidget->setItemWidget(item, itemView);
    item->setSizeHint(itemView->sizeHint());

    for (auto &model : list) {
        ModelItemView *itemView = new ModelItemView(this);
        itemView->setModel(model);

        QListWidgetItem *item = new QListWidgetItem(_listWidget);
        _listWidget->setItemWidget(item, itemView);
        item->setSizeHint(itemView->sizeHint());
    }
    setModel(_listWidget->model());
    setView(_listWidget);
}

int ModelComboBox::findModelIndex(const QString &name)
{
    for (int i=0; i<_modelList.size(); i++)
    {
        Entity lm = _modelList.at(i);
        if (lm.name == name) {
            return i+1;
        }
    }
    return -1;
}

QString ModelComboBox::getModelText(int index)
{
    if (index == 0) return "-- 请选择 --";

    Entity model = _modelList.at(index-1);
    return model.name;
}

Entity ModelComboBox::currentModel()
{
    int index = this->currentIndex();
    if (index == 0) return Entity();
    return _modelList.at(index-1);
}
