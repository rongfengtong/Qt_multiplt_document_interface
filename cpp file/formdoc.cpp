#include "formdoc.h"
#include "ui_formdoc.h"

#include<QFile>
#include<QTextStream>
#include<QFileInfo>

bool FormDoc::already_open_file()
{
    return already_file;
}

// 子窗口加载路径文件
void FormDoc::load_file(QString file_name)
{
    QFile file(file_name);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);

        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(stream.readAll());

        // 状态更新
        cur_open_file_name = file_name;     //记录下来
        already_file = true;

        QFileInfo file_info(file_name);
        QString cur_file_str = file_info.fileName();
        setWindowTitle(cur_file_str);
    }

}

QString FormDoc::get_cur_file_name()
{
    return cur_open_file_name;
}

#include<QFontDialog>
void FormDoc::set_font()
{
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}

void FormDoc::text_copy()
{
    ui->plainTextEdit->copy();
}

void FormDoc::text_cut()
{
    ui->plainTextEdit->cut();
}

void FormDoc::text_paste()
{
    ui->plainTextEdit->paste();
}




FormDoc::FormDoc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDoc)
{
    ui->setupUi(this);
}

FormDoc::~FormDoc()
{
    delete ui;
}
