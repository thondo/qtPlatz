/**************************************************************************
** Copyright (C) 2010-2016 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2016 MS-Cheminformatics LLC, Toin, Mie Japan
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

#include "../adcontrols_global.h"
#include "eventcap.hpp"
#include <boost/uuid/uuid.hpp>
#include <vector>
#include <tuple>

namespace adcontrols {

    namespace ControlMethod {

        /* Time event module capability
         */

        class ADCONTROLSSHARED_EXPORT ModuleCap {
        public:
            ModuleCap();
            ModuleCap( const boost::uuids::uuid& clsid, const std::string& model_display_name );
            ModuleCap( const ModuleCap& );

            const boost::uuids::uuid& clsid() const;
            const std::string& model_display_name() const;
            const std::vector< EventCap >& eventCaps() const;
            std::vector< EventCap >& eventCaps();
            
        private:
            boost::uuids::uuid clsid_; // model class
            std::string model_display_name_;
            std::vector< EventCap > eventCaps_;
        };
        
    }
}
