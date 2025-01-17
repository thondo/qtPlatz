// This is a -*- C++ -*- header.
/**************************************************************************
** Copyright (C) 2010-2015 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2015 MS-Cheminformatics LLC
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

#include "adcontrols_global.h"
#include <boost/serialization/version.hpp>
#include <memory>
#include <string>

namespace boost {
    namespace serialization { class access; }
    namespace uuids { struct uuid; }
}

namespace adcontrols {

    class ADCONTROLSSHARED_EXPORT threshold_action {
    public:
        ~threshold_action(void);
        threshold_action(void);
		threshold_action(const threshold_action &);
        static const char * modelClass() { return "threshold_action"; }
        static const char * itemLabel() { return "threshold_action"; }
        static const boost::uuids::uuid& clsid();

        bool enable;
        double delay;
        double width;
        bool enableTimeRange;
        bool recordOnFile;
        bool exclusiveDisplay;
        
        // class v2
        std::string objid_spectrometer;
        std::string formula;
        uint32_t mode;
        double mass;
        
        static bool archive( std::ostream&, const threshold_action& );
        static bool restore( std::istream&, threshold_action& );
        static bool xml_archive( std::wostream&, const threshold_action& );
        static bool xml_restore( std::wistream&, threshold_action& );        

    private:
        friend class boost::serialization::access;
        template<class Archive> void serialize( Archive& ar, const unsigned int version );
	};

#if defined _MSC_VER
    ADCONTROLSSHARED_TEMPLATE_EXPORT template class ADCONTROLSSHARED_EXPORT std::weak_ptr< threshold_action >;
#endif    
}

BOOST_CLASS_VERSION( adcontrols::threshold_action, 2 )

