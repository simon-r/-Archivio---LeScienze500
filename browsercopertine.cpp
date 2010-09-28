//     Copyright 2010 Simone Riva
//     mail:  simone (dot) rva (lumachina) gmail.com
//
//    This file is part of LeScienze500.
//
//    LeScienze500 is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    LeScienze500 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with LeScienze500.  If not, see <http://www.gnu.org/licenses/>.

#include "browsercopertine.h"
#include "ui_browsercopertine.h"
#include<QFile>
#include<QDebug>

BrowserCopertine::BrowserCopertine(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::BrowserCopertine)
{
    ui->setupUi(this);
}

BrowserCopertine::~BrowserCopertine()
{
    delete ui ;
}

void BrowserCopertine::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void BrowserCopertine::appendAnnoGUI( QString anno )
{
    ui->ListaAnni->addItem( anno );
}

void BrowserCopertine::clearListaAnni()
{
    ui->ListaAnni->clear();
}

void BrowserCopertine::openBrowser()
{
    this->fillListaAnni() ;

    this->setModal(true);
    this->setFocus();
    this->show();

    showAnno( "1999" ) ;
}

void BrowserCopertine::openListaRiviste( const QString anno )
{
    QFile res ;
    res.open(QIODevice::ReadOnly) ;
    res.setFileName( ":/html/html/testata_lista_copertine.html" );
    res.close();

    pagina_anno.clear();
    pagina_anno = res.readAll() ;
    pagina_anno.replace( QRegExp("<!--anno-->") , anno ) ;


}

void BrowserCopertine::appendRivista( const QString copertina , const QString mese )
{
    QFile res ;
    res.setFileName( ":/html/html/corpo_lista_copertine.html" );

    res.open(QIODevice::ReadOnly) ;
    QString corpo = res.readAll() ;
    res.close();

    corpo.replace( QRegExp("<!--mese-->") , mese ) ;
    corpo.replace( QRegExp("<!--file_copertina-->") , copertina ) ;

    pagina_anno.append( " " ) ;
    pagina_anno.append( corpo ) ;
}

void BrowserCopertine::closeListaCopertine()
{
    QFile res ;
    res.setFileName( ":/html/html/corpo_lista_copertine.html" );

    res.open(QIODevice::ReadOnly) ;
    QString fine = res.readAll() ;
    res.close();

    pagina_anno.append( " " ) ;
    pagina_anno.append( fine ) ;

    //qDebug() << pagina_anno ;

    ui->MostraRiviste->setHtml( pagina_anno );
}
