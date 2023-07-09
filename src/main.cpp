#include <QCoreApplication>
#include <QFile>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc < 3)
    {
        qDebug() << "Usage: program_name input_file output_file";
        return 1;
    }

    QString inputFile = QString::fromUtf8(argv[1]);
    QString outputFile = QString::fromUtf8(argv[2]);

    QFile inputFileObj(inputFile);
    QFile outputFileObj(outputFile);

    if (!inputFileObj.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open input file.";
        return 1;
    }

    if (!outputFileObj.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open output file.";
        return 1;
    }

    QTextStream inputStream(&inputFileObj);
    QTextStream outputStream(&outputFileObj);

    QString inputText = inputStream.readAll();
    QRegExp regex("\\{([^\\}]*)\\}");

    int pos = 0;
    while ((pos = regex.indexIn(inputText, pos)) != -1)
    {
        QString matchedString = regex.cap(0).trimmed();
        outputStream << matchedString << "\n";
        pos += regex.matchedLength();
    }

    inputFileObj.close();
    outputFileObj.close();

    qDebug() << "Strings within curly brackets have been copied to the output file.";


    return a.exec();
}
