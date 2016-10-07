#ifndef EDITORBASE_HPP
#define EDITORBASE_HPP

#include <QWidget>
#include "../../backend/database.hpp"

class EditorBase : public QWidget
{
    Q_OBJECT
public:
    explicit EditorBase(QWidget *parent = 0);
    virtual void save(Database& db)=0;
    virtual void save_as(Database& db)=0;

signals:
    void base_text(QString);

public slots:
};

#endif // EDITORBASE_HPP
