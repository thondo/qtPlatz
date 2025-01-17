/**************************************************************************
** Copyright (C) 2010-2014 Toshinobu Hondo, Ph.D.
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

#include "meta_data.hpp"
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <adportable_serializer/portable_binary_iarchive.hpp>
#include <adportable_serializer/portable_binary_oarchive.hpp>
#include <boost/archive/xml_woarchive.hpp>
#include <boost/archive/xml_wiarchive.hpp>

namespace aqmd3controls {

    template<typename T = meta_data>
    class meta_data_archive {
    public:
        template<class Archive>
        void serialize( Archive& ar, T& _, const unsigned int version ) {
            using namespace boost::serialization;
            ar & BOOST_SERIALIZATION_NVP( _.initialXTimeSeconds );
            ar & BOOST_SERIALIZATION_NVP( _.actualPoints );
            ar & BOOST_SERIALIZATION_NVP( _.flags );
            ar & BOOST_SERIALIZATION_NVP( _.actualAverages );
            ar & BOOST_SERIALIZATION_NVP( _.actualRecords );
            ar & BOOST_SERIALIZATION_NVP( _.initialXOffset );
            ar & BOOST_SERIALIZATION_NVP( _.xIncrement );
            ar & BOOST_SERIALIZATION_NVP( _.scaleFactor );
            ar & BOOST_SERIALIZATION_NVP( _.scaleOffset );
            ar & BOOST_SERIALIZATION_NVP( _.dataType );
            ar & BOOST_SERIALIZATION_NVP( _.protocolIndex );
            ar & BOOST_SERIALIZATION_NVP( _.channelMode );

            ar & BOOST_SERIALIZATION_NVP( _.firstValidPoint );
            ar & BOOST_SERIALIZATION_NVP( _.identify );
        }
    };

    template<> AQMD3CONTROLSSHARED_EXPORT void meta_data::serialize( boost::archive::xml_woarchive& ar, unsigned int version )
    {
        meta_data_archive<>().serialize( ar, *this, version );
    }

    template<> AQMD3CONTROLSSHARED_EXPORT void meta_data::serialize( boost::archive::xml_wiarchive& ar, unsigned int version )
    {
        meta_data_archive<>().serialize( ar, *this, version );
    }

    template<> AQMD3CONTROLSSHARED_EXPORT void meta_data::serialize( portable_binary_oarchive& ar, unsigned int version )
    {
        meta_data_archive<>().serialize( ar, *this, version );
    }

    template<> AQMD3CONTROLSSHARED_EXPORT void meta_data::serialize( portable_binary_iarchive& ar, unsigned int version )
    {
        meta_data_archive<>().serialize( ar, *this, version );
    }
}

using namespace aqmd3controls;

meta_data::meta_data() : initialXTimeSeconds( 0 )
                       , actualPoints( 0 )
                       , flags( 0 )
                       , actualAverages( 0 )
                       , actualRecords( 0 )
                       , initialXOffset( 0 )
                       , xIncrement( 0 )
                       , scaleFactor( 0 )
                       , scaleOffset( 0 )
                       , dataType( 0 )
                       , protocolIndex( 0 )
                       , channelMode( None )
                       , firstValidPoint( 0 )
{
}

meta_data::meta_data( const meta_data& t ) : initialXTimeSeconds( t.initialXTimeSeconds )
                                           , actualPoints( t.actualPoints )
                                           , flags( t.flags )
                                           , actualAverages( t.actualAverages )
                                           , actualRecords( t.actualRecords )
                                           , initialXOffset( t.initialXOffset )
                                           , xIncrement( t.xIncrement )
                                           , scaleFactor( t.scaleFactor )
                                           , scaleOffset( t.scaleOffset )
                                           , dataType( t.dataType )     // 2(int16_t)|4(int32_t)|8(int64_t)|-8(double)
                                           , protocolIndex( t.protocolIndex )
                                           , channelMode( t.channelMode )
                                           , firstValidPoint( t.firstValidPoint )
                                           , identify( t.identify )
{
}
