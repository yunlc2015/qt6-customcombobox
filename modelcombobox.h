#ifndef MODELCOMBOBOX_H
#define MODELCOMBOBOX_H

#include <QComboBox>
#include <QListWidget>
#include <QLabel>
#include "entity.h"

class CustomItemView : public QFrame
{
public:
    CustomItemView(QWidget *parent = nullptr);
    const Entity &model() const { return _model; }
    virtual QString text() const;

protected:
    Entity _model;
    QLabel *_labelName;

private:
};

class ModelItemView : public CustomItemView
{
public:
    ModelItemView(QWidget *parent = nullptr);
    void setModel(const Entity &model);
    virtual QString text() const override;

private:
    QLabel *_labelSummary;
};

class ModelComboBox : public QComboBox
{
public:
    ModelComboBox(QWidget *parent = nullptr);

    void setText(const QString &text);
    void setList(const QList<Entity> &list);
    int findModelIndex(const QString &name);
    QString getModelText(int index);
    Entity currentModel();

private:
    QListWidget *_listWidget;
    QList<Entity> _modelList;
};

#endif // MODELCOMBOBOX_H
