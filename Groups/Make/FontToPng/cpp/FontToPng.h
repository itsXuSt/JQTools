﻿#ifndef __FontToPng_h__
#define __FontToPng_h__

// C++ lib import
#include <functional>

// Qt lib import
#include <QVector>
#include <QMap>
#include <QImage>
#include <QQuickImageProvider>
#include <QJsonArray>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define FONTTOPNG_INITIALIZA                                                        \
{                                                                                   \
    auto fontToPngManage = new FontToPng::Manage;                                   \
    engine.addImageProvider("FontToPngManage", fontToPngManage);                    \
    engine.rootContext()->setContextProperty("FontToPngManage", fontToPngManage);   \
}

namespace FontToPng
{

struct CharAdaptation
{
    qreal xOffset = 0;
    qreal yOffset = 0;
    qreal scale = 1;
};

struct CharPackage
{
    ushort code;
    QString name;

    CharAdaptation charAdaptation;
    QImage preview;
};

struct FontPackage
{
    QString fontName;
    QString ttfFilePath;
    QString txtFilePath;

    int fontId;
    QString familieName;

    QMap< ushort, CharPackage > charPackages;
};

class Manage: public AbstractTool, public QQuickImageProvider
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

public slots:
    void begin();

    QJsonArray getCharList(const QString &familieName, const QString &searchKey);

private:
    void loadFont(const QString fontName);

    QImage paintChar(const QString &familieName, const CharPackage &charPackage, const QColor &color, const QSizeF &charSize, const QSizeF &backgroundSize);

    void makeAdaptation(const QString &familieName, CharPackage &charPackage);

    QImage requestImage(const QString &id, QSize *, const QSize &);

private:
    QVector< FontPackage > fontPackages_;
    QMutex mutex_;
};

}

#endif//__FontToPng_h__