/**************************************************************************
** Copyright (C) 2010-2014 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2014 MS-Cheminformatics LLC, Toin, Mie Japan
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

#ifndef QUANMETHOD_HPP
#define QUANMETHOD_HPP

#include "adcontrols_global.h"
#include "constants.hpp"
#include "idaudit.hpp"
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <cstdint>
#include <memory>
#include <string>

namespace adcontrols {

    class ADCONTROLSSHARED_EXPORT QuanMethod {

    public:
        ~QuanMethod();
        QuanMethod();
        QuanMethod( const QuanMethod& );

        enum CalibEq {
            idCalibOnePoint
            , idCalibLinear_origin
            , idCalibLinear
            , idCalibPolynomials
        };

        enum CalibWeighting {
            idWeight_C1
            , idWeight_C2
            , idWeight_C3
            , idWeight_Y1
            , idWeight_Y2
            , idWeight_Y3
        };

        enum Bracketing {
            idBracketNone
            , idBracketStandard
            , idBracketOverlapped
            , idBracketAverage
        };

        const idAudit& ident() const { return ident_; }

        CalibEq equation() const;
        void equation( CalibEq );

        uint32_t polynomialOrder() const;
        void polynomialOrder( uint32_t );

        bool isCounting() const;
        void setIsCounting( bool );

        bool isChromatogram() const;
        void setIsChromatogram( bool );

        bool isWeighting() const;
        void setIsWeighting( bool );

        bool isBracketing() const;
        void setIsBracketing( bool );

        Bracketing bracketing() const;
        void setBracketing( Bracketing );

        CalibWeighting weighting() const;
        void setWeighting( CalibWeighting );

        bool isInternalStandard() const;
        void setIsInternalStandard( bool );

        bool isExternalStandard() const { return !isInternalStandard(); }

        uint32_t levels() const;
        void setLevels( uint32_t );

        uint32_t replicates() const;
        void setReplicates( uint32_t );

        // debug&trace methods
        uint32_t debug_level() const;
        void set_debug_level( uint32_t );

        bool save_on_datasource() const;
        void set_save_on_datasource( bool );
        // <--

        const wchar_t * quanMethodFilename() const { return quanMethodFilename_.c_str(); }
        void quanMethodFilename( const wchar_t * d ) { quanMethodFilename_ = d; }

        const wchar_t * quanCompoundsFilename() const { return quanCompoundsFilename_.c_str(); }
        void quanCompoundsFilename( const wchar_t * d ) { quanCompoundsFilename_ = d; }

        const wchar_t * quanSequenceFilename() const { return quanSequenceFilename_.c_str(); }
        void quanSequenceFilename( const wchar_t * d ) { quanSequenceFilename_ = d; }

        void setInlet( Quan::QuanInlet );
        Quan::QuanInlet inlet() const;

    private:
        idAudit ident_;
        bool isCounting_;
        bool isChromatogram_;
        bool isISTD_;
        bool use_weighting_;
        bool use_bracketing_;
        CalibEq eq_;
        CalibWeighting weighting_;
        Bracketing bracketing_;
        uint32_t levels_;
        uint32_t replicates_;
        uint32_t polynomialOrder_;
        uint32_t debug_level_; // determine which intermediate results to be stored on database
        bool save_on_datasource_;

        std::wstring quanMethodFilename_;
        std::wstring quanCompoundsFilename_;
        std::wstring quanSequenceFilename_;
        Quan::QuanInlet inlet_;

        friend class boost::serialization::access;
        template<class Archive>
            void serialize( Archive& ar, const unsigned int version ) {
            using namespace boost::serialization;

            ar & BOOST_SERIALIZATION_NVP( ident_ )
                & BOOST_SERIALIZATION_NVP( isChromatogram_ )
                & BOOST_SERIALIZATION_NVP( isISTD_ )
                & BOOST_SERIALIZATION_NVP( use_weighting_ )
                & BOOST_SERIALIZATION_NVP( use_bracketing_ )
                & BOOST_SERIALIZATION_NVP( eq_ )
                & BOOST_SERIALIZATION_NVP( weighting_ )
                & BOOST_SERIALIZATION_NVP( bracketing_ )
                & BOOST_SERIALIZATION_NVP( levels_ )
                & BOOST_SERIALIZATION_NVP( replicates_ )
                & BOOST_SERIALIZATION_NVP( polynomialOrder_ )
                & BOOST_SERIALIZATION_NVP( quanMethodFilename_ )
                & BOOST_SERIALIZATION_NVP( quanCompoundsFilename_ )
                & BOOST_SERIALIZATION_NVP( quanSequenceFilename_ )
                ;
            if ( version >= 2 ) {
                ar & BOOST_SERIALIZATION_NVP( debug_level_ );
                ar & BOOST_SERIALIZATION_NVP( save_on_datasource_ );
            }
            if ( version >= 3 ) {
                ar & BOOST_SERIALIZATION_NVP( isCounting_ );
            }
            if ( version >= 4 ) {
                ar & BOOST_SERIALIZATION_NVP( inlet_ );
            }
        };

    };

}

BOOST_CLASS_VERSION( adcontrols::QuanMethod, 4 )

#endif // QUANMETHOD_HPP
