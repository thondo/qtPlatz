/**************************************************************************
** Copyright (C) 2014-2024 MS-Cheminformatics LLC, Toin, Mie Japan
*
** Contact: toshi.hondo@qtplatz.com
**
** Commercial Usage
**
** Licensees holding valid MS-Cheminformatics commercial licenses may use this file in
** accordance with the MS-Cheminformatics Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and MS-Cheminformatics LLC.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.TXT included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#pragma once

#include <QWidget>

namespace figshare {

    class CSVWnd : public QWidget {
        Q_OBJECT
    public:
        explicit CSVWnd(QWidget *parent = 0);
        ~CSVWnd();

        void setData( const QByteArray& ba );

    public slots:
        void handleReply( const QByteArray&, const QString& url );
        void handleFigshareReply( const QByteArray&, const QString& url );
        void handleDownloadReply( const QByteArray&, const QString& url );
        void handleCSVReply( const QByteArray&, const QString&, size_t );

    private:
        class impl;
        impl * impl_;
    };

}