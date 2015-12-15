/**************************************************************************
** Copyright (C) 2010-2016 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2016 MS-Cheminformatics LLC, Toin, Mie Japan
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

#include "datareader.hpp"
#include "datainterpreter_u5303a.hpp"
#include "datainterpreter_histogram.hpp"
#include "datainterpreter_timecount.hpp"
#include "datainterpreter_softavgr.hpp"
#include <adportable/debug.hpp>
#include <adfs/filesystem.hpp>
#include <adfs/sqlite.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <memory>
#include <atomic>
#include <mutex>

namespace acqrsinterpreter {

    template< typename Interpreter > struct TID {
        static const std::string value;
        typedef Interpreter type;
    };

    template<> const std::string TID<u5303a::DataInterpreter >::value = "1.u5303a.ms-cheminfo.com";
    template<> const std::string TID<timecount::DataInterpreter >::value = "timecount.1.u5303a.ms-cheminfo.com";
    template<> const std::string TID<histogram::DataInterpreter >::value = "histogram.timecount.1.u5303a.ms-cheminfo.com";
    template<> const std::string TID<softavgr::DataInterpreter>::value = "tdcdoc.waveform.1.u5303a.ms-cheminfo.com";

    typedef boost::mpl::vector<
        TID<u5303a::DataInterpreter >
        , TID<timecount::DataInterpreter>
        , TID<histogram::DataInterpreter>
        , TID<softavgr::DataInterpreter> > interpreter_types;

    template< typename T > struct wrap {};

    struct make_list {
        std::vector< std::string >& list;
        make_list( std::vector< std::string >& _list ) : list(_list ){}
        template < typename T > void operator () ( wrap<T> ) const {
            list.push_back( T::value );
        }
    };
        
    struct lookup_and_create {
        const char * id;
        std::unique_ptr< adcontrols::DataInterpreter >& interpreter;
        lookup_and_create( const char * _id, std::unique_ptr< adcontrols::DataInterpreter >& t ) : id( _id ), interpreter( t ) {}
        template < typename T > void operator () ( wrap<T> ) const {
            if ( id == T::value ) {
                interpreter = std::unique_ptr< typename T::type >( new typename T::type() );
                ADDEBUG() << "found: " << T::value;
            }
        }
    };

}

using namespace acqrsinterpreter;

DataReader::~DataReader()
{
}

DataReader::DataReader( const char * traceid ) : adcontrols::DataReader( traceid )
{
    // traceid determines type of trace, a.k.a. type of mass-spectormeter, multi-dimentional chromatogram etc.
    // Though traceid does not indiecate trace object (in case two UV-ditectors on the system, traceid does not tell which one)

    boost::mpl::for_each< interpreter_types, wrap< boost::mpl::placeholders::_1> >( lookup_and_create( traceid, interpreter_ ) );
}

// static
std::vector< std::string >
DataReader::traceid_list()
{
    std::vector< std::string > list;
    boost::mpl::for_each< interpreter_types, wrap< boost::mpl::placeholders::_1> >( make_list( list ) );
    return list;
}

bool
DataReader::initialize( adfs::filesystem& dbf, const boost::uuids::uuid& objid, const std::string& objtext )
{
    if ( interpreter_ ) {
        objid_ = objid; // objid tells channel/module id
        objtext_ = objtext; // for debugging convension
        db_ = dbf._ptr();
        return true;
    }
    return false;
}

void
DataReader::finalize()
{
}

size_t
DataReader::ticCount() const
{
    if ( auto db = db_.lock() ) {

        adfs::stmt sql( *db );
        sql.prepare( "SELECT COUNT( DISTINCT fcn ) FROM AcquiredData WHERE objuuid = ?" );
        sql.bind( 1 ) = objid_;
        
        size_t fcnCount( 0 );
        while ( sql.step() == adfs::sqlite_row )
            fcnCount += sql.get_column_value< int64_t >( 0 );
        
        return fcnCount;
    }
    return 0;
}
