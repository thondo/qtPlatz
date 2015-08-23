/**************************************************************************
** Copyright (C) 2010-2015 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2015 MS-Cheminformatics LLC, Toin, Mie Japan
*
** Contact: toshi.hondo@qtplatz.com
**
** Commercial Usage
**
** Licensees holding valid MS-Cheminfomatics commercial licenses may use this file in
** accordance with the MS-Cheminformatics Commercial License Agreement provided with
** the Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and MS-Cheminformatics.
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

#include <QObject>
#include <atomic>
#include <memory>
#include <mutex>

class QSettings;

namespace chemistry {

    class ChemConnection;
    class ChemQuery;

    class ChemDocument : public QObject
    {
        Q_OBJECT
        explicit ChemDocument(QObject *parent = 0);
        static std::atomic< ChemDocument * > instance_;
        static std::mutex mutex_;
    public:
        static ChemDocument * instance();
        
        void initialSetup();
        void finalClose();

        QSettings * settings();
        void setConnection( ChemConnection * );
        ChemConnection * connection();

        void setQuery( ChemQuery * );
        ChemQuery * query();


    private:    
        class impl;
        impl * impl_;

        void dbInit( ChemConnection * );

    signals:
        void onConnectionChanged();
                                  
    public slots:

    };

}

