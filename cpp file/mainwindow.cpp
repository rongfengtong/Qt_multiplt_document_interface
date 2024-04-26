#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formdoc.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->mdiArea);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actDoc_New_triggered()
{
    FormDoc *form_doc = new FormDoc(this);
    // form_doc->setAttribute(Qt::WA_DeleteOnClose);

    ui->mdiArea->addSubWindow(form_doc);
    form_doc->show();
}

#include<QMdiSubWindow>
#include<QFileDialog>
void MainWindow::on_actDoc_Open_triggered()
{
    //先打开新窗口
    FormDoc *form_doc;
    bool need_new_form = false;
    if(ui->mdiArea->subWindowList().count() > 0){
        form_doc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
        need_new_form = form_doc->already_open_file();
    }
    else{
        need_new_form = true;
    }

    if(need_new_form){
        form_doc = new FormDoc(this);
        ui->mdiArea->addSubWindow(form_doc);
    }

    //
    QString file_name = QFileDialog::getOpenFileName(this, "mytitle", "", "cpp程序(.h *cpp);;所有文件(*.*)");
    form_doc->load_file(file_name);
    form_doc->show();

    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actFont->setEnabled(true);

}


void MainWindow::on_actCloseALL_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actFont_triggered()
{
    FormDoc *form_doc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    form_doc->set_font();
}


void MainWindow::on_actCut_triggered()
{
    FormDoc *cur_form_doc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    cur_form_doc->text_cut();
}


void MainWindow::on_actCopy_triggered()
{
    FormDoc *cur_form_doc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    cur_form_doc->text_copy();
}


void MainWindow::on_actPaste_triggered()
{
    FormDoc *cur_form_doc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
    cur_form_doc->text_paste();
}


//布局方式
void MainWindow::on_actViewMode_triggered(bool checked)
{
    if(checked){
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
        ui->mdiArea->setTabsClosable(true);

        ui->actCascade->setEnabled(false);
        ui->actTile->setEnabled(false);

    }   else{
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
        ui->actCascade->setEnabled(true);
        ui->actTile->setEnabled(true);
    }
}


void MainWindow::on_actCascade_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actTile_triggered()
{
    ui->mdiArea->tileSubWindows();
}





void MainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    if(ui->mdiArea->subWindowList().count() == 0){
        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actCut->setEnabled(false);
        ui->actFont->setEnabled(false);
        ui->statusbar->clearMessage();

    }
    else{
        FormDoc *form_doc = (FormDoc*)ui->mdiArea->activeSubWindow()->widget();
        ui->statusbar->showMessage(form_doc->get_cur_file_name());
    }
}











