// This is a -*- C++ -*- header.
/**************************************************************************
** Copyright (C) 2010-2016 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2016 MS-Cheminformatics LLC
*
** Contact: info@ms-cheminfo.com
**
** Commercial Usage
**
** Licensees holding valid MS-Cheminformatics commercial licenses may use this file in
** accordance with the MS-Cheminformatics Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
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

#include "adprocessor_global.hpp"
#include <adcontrols/datasubscriber.hpp>
#include <memory>
#include <vector>
#include <string>

namespace adfs { class filesystem; class sqlite; }

namespace adcontrols {
    class datafile;
    class LCMSDataset;
    class ProcessedDataset;
}

namespace portfolio { class Portfolio; class Folder; class Folium; }

namespace adprocessor {

    class ADPROCESSORSHARED_EXPORT dataprocessor : public std::enable_shared_from_this< dataprocessor >
                                                 , public adcontrols::dataSubscriber {
        
    public:
        virtual ~dataprocessor();
        dataprocessor();

        // dataprocessor
        virtual void setModified( bool );

        virtual bool open( const std::wstring&, std::wstring& errmsg );
        
		virtual const std::wstring& filename() const;

        virtual void setFile( std::unique_ptr< adcontrols::datafile >&& );
        virtual adcontrols::datafile * file();
        virtual const adcontrols::datafile * file() const;
        
        virtual const adcontrols::LCMSDataset * rawdata();

        std::shared_ptr< adfs::sqlite > db() const;

        virtual const portfolio::Portfolio& portfolio() const;
        virtual portfolio::Portfolio& portfolio();

        // implement adcontrols::dataSubscriber
        virtual bool subscribe( const adcontrols::LCMSDataset& ) override;
        virtual bool subscribe( const adcontrols::ProcessedDataset& ) override;
        virtual void notify( adcontrols::dataSubscriber::idError, const wchar_t * ) override;

    private:
        std::unique_ptr< adfs::filesystem > fs_;
        std::unique_ptr< adcontrols::datafile > file_;
        const adcontrols::LCMSDataset * rawdata_;
        bool modified_;
    protected:
        std::unique_ptr< portfolio::Portfolio > portfolio_;
    };

} // mpxcontrols

