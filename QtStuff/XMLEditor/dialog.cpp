#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //Create the model
    Filename = "E:/Test/MyXML.xml";
    model = new QStandardItemModel(0, 1, this);

    ReadFile();

    ui->treeView->setModel(model);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::ReadFile()
{
    QStandardItem *root = new QStandardItem("Books");
    model->appendRow(root);

    QDomDocument document;

    //Load the XML file
    QFile file(Filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        document.setContent(&file);
        file.close();
    }

    //Get the XML root element
    QDomElement xmlRoot = document.firstChildElement();

    //Read the books
    QDomNodeList books = xmlRoot.elementsByTagName("Book");
    for (int i = 0; i < books.count(); i++)
    {
        QDomElement book = books.at(i).toElement();
        QStandardItem *bookItem = new QStandardItem(book.attribute("Name"));


        //Read the chapters of the book
        QDomNodeList chapters = book.elementsByTagName("Chapter");
        for (int h = 0; h < chapters.count(); h++)
        {
            QDomElement chapter = chapters.at(h).toElement();
            QStandardItem *chapterItem = new QStandardItem(chapter.attribute("Name"));
            bookItem->appendRow(chapterItem);
        }
        root->appendRow(bookItem);
    }

}

void Dialog::WriteFile()
{
    //Write the XML file
    QDomDocument document;

    //Make a root node
    QDomElement xmlRoot = document.createElement("Books");
    document.appendChild(xmlRoot);

    QStandardItem *root = model->item(0, 0);
    for (int i = 0; i < root->rowCount(); i++)
    {
        QStandardItem *book = root->child(i, 0);

        QDomElement xmlBook = document.createElement("Book");
        xmlBook.setAttribute("Name", book->text());
        xmlBook.setAttribute("ID", i);
        xmlRoot.appendChild(xmlBook);

        for(int h = 0; h < book->rowCount(); h++)
        {
            QStandardItem *chapter = book->child(h, 0);

            QDomElement xmlChapter = document.createElement("Chapter");
            xmlChapter.setAttribute("Name", chapter->text());
            xmlChapter.setAttribute("ID", h);
            xmlBook.appendChild(xmlChapter);
        }
    }

    //Save to disk
    QFile file(Filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
            qDebug() << "Failed to write file";
    }

    QTextStream stream(&file);
    stream << document.toString();
    file.close();

    qDebug() << "Finished";
}

void Dialog::on_pushButton_clicked()
{
    //Save the document
}
