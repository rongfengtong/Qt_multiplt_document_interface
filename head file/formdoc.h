#ifndef FORMDOC_H
#define FORMDOC_H

#include <QWidget>

namespace Ui {
class FormDoc;
}

class FormDoc : public QWidget
{
    Q_OBJECT

public:
    bool already_open_file();
    void load_file(QString file_name);
    QString get_cur_file_name();

    void set_font();
    void text_copy();
    void text_cut();
    void text_paste();



private:
    bool already_file = false;
    QString cur_open_file_name = NULL;


public:
    explicit FormDoc(QWidget *parent = nullptr);
    ~FormDoc();

private:
    Ui::FormDoc *ui;
};

#endif // FORMDOC_H
