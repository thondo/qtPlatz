
// This is a -*- C++ -*- header.
/**************************************************************************
** Copyright (C) 2010-2019 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2019 MS-Cheminformatics LLC
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
#include "metric/prefix.hpp"
#include <functional>
#include <string>
#include <memory>
#include <vector>

namespace boost {
    namespace archive {
        class binary_oarchive;
        class binary_iarchive;
    }
    namespace serialization {
        class access;
    }
    namespace uuids {
        struct uuid;
    }
}

class portable_binary_oarchive;
class portable_binary_iarchive;

namespace adcontrols {

    class MassSpectrum;

    typedef std::shared_ptr<MassSpectrum> MassSpectrumPtr;
    typedef std::tuple< double, double, double, int > mass_value_type;

    enum MS_POLARITY { PolarityIndeterminate
                       , PolarityPositive = (1)
                       , PolarityNegative
                       , PolarityMixed
    };

    enum CentroidAlgorithm { CentroidNone
                             , CentroidPeakMass
                             , CentroidPeakAreaWaitedMass
                             , CentroidPeakMoment
                             , CentroidIsotopeSimulation
                             , CentroidNative      // instrument manufacturer's native algorithm
                             , CentroidHistogram   // histogram based on counting (added 2018-MAY)
    };

    class annotation;
    class description;
    class descriptions;
    class MSCalibration;
    class MSProperty;
    class annotations;
	class ScanLaw;

    class ADCONTROLSSHARED_EXPORT MassSpectrum;

    class MassSpectrum {
    public:
        ~MassSpectrum();
        MassSpectrum();
        MassSpectrum( const MassSpectrum& );
        MassSpectrum& operator = ( const MassSpectrum& );
        MassSpectrum& operator += ( const MassSpectrum& );

        // algorithm
        constexpr const static size_t npos = size_t(-1);
        size_t lower_bound( double mass, bool isMass = true ) const;
        size_t find( double mass, double tolerance ) const;

        // methods
        void clone( const MassSpectrum&, bool deep = false );
        static const wchar_t * dataClass() { return L"MassSpectrum"; }

        size_t size() const;
        void resize( size_t );

        const double * getMassArray() const;
        const double * getIntensityArray() const;
        const double * getTimeArray() const;
        const uint8_t * getColorArray() const;
        const std::vector< double >& intensityArray() const;
        const std::vector< double >& timeArray() const;
        const std::vector< double >& massArray() const;
        const std::vector< uint8_t >& colorArray() const;

        size_t operator << ( const std::pair< double, double >& ); // add (mass,intensity), return index
        void setValue( size_t idx, std::tuple< double, double >&& );      // tof,mass,intensity
        void setValue( size_t idx, std::tuple< double, double, double >&& );      // tof,mass,intensity
        void setValue( size_t idx, std::tuple< double, double, double, int >&& ); // tof,mass,intensity,color

        void setMass( size_t idx, double mass );
        void setIntensity( size_t idx, double intensity );
        void setTime( size_t idx, double time );
        void setColor( size_t idx, uint8_t color );
        void setAcquisitionMassRange( double, double );
        void setMassArray( const double *, bool setRange = false );
        void setIntensityArray( const double * );
        void setTimeArray( const double * );
		// void setColorArray( const uint8_t * );
        bool isCentroid() const;
        bool isHistogram() const;
        void setCentroid( CentroidAlgorithm );
        CentroidAlgorithm centroidAlgorithm() const;

        void setIntensityArray( std::vector< double >&& );
        void setMassArray( std::vector< double >&& );
        void setTimeArray( std::vector< double >&& );
        void setColorArray( std::vector< uint8_t >&& );

        // ---
        void setDataReaderUuid( const boost::uuids::uuid& );
        const boost::uuids::uuid& dataReaderUuid() const;

        // ---
        MS_POLARITY polarity() const;
        void setPolarity( MS_POLARITY );
        int mode() const;

        typedef double( mass_assign_t )( double time, int mode );
        typedef std::function< mass_assign_t > mass_assignee_t;

        bool assign_masses( mass_assignee_t );
        //void setScanLaw( const adcontrols::ScanLaw&, bool assignMasses = false );
        void setCalibration( const adcontrols::MSCalibration&, bool assignMasses = false );
        std::shared_ptr< const MSCalibration > calibration() const;

        void setMSProperty( const adcontrols::MSProperty& );
        const MSProperty& getMSProperty() const;
        MSProperty& getMSProperty();

        void normalizeIntensities( uint32_t nImaginalAverage );

        // [[deprecated("use MSProperty,acceleratorVoltage&tDelay")]]
        //     const ScanLaw* scanLaw() const;

        template<class T> void set( const T& t );
        template<class T> const T& get();
        std::pair<double, double> getAcquisitionMassRange() const;
        std::pair<size_t, size_t> minmax_element() const;
        size_t max_element( const std::pair< double, double >&, bool isTime = false ) const;
        std::pair<size_t, size_t> minmax_element( const std::pair< double, double >&, bool isTime = false ) const;

        double maxIntensity() const;
        double minIntensity() const;
        double mass( size_t idx ) const;
        double intensity( size_t idx ) const;
        double time( size_t idx ) const;

        size_t getIndexFromMass( double, bool closest = false ) const;
		size_t getIndexFromTime( double seconds, bool closest = false ) const;

        int color( size_t idx ) const;

        // time, mass, intensity, color
        std::tuple< double, double, double, int > value( size_t idx ) const;

        void addDescription( const description& );
        void addDescription( description&& );
        const descriptions& getDescriptions() const;

        void set_annotations( const annotations& );
        void set_annotations( adcontrols::annotations&& );
        const adcontrols::annotations& annotations() const;

        adcontrols::annotations& annotations();
        void addAnnotation( annotation&& a, bool uniq = true );

        int32_t protocolId() const;
        int32_t nProtocols() const;
        void setProtocol( int, int );

        int64_t rowid() const;
        void setRowid( int64_t );

        std::wstring saveXml() const;
        void loadXml( const std::wstring& );

        // adfs::cpio (serializer)
        static bool archive( std::ostream&, const MassSpectrum& );
        static bool restore( std::istream&, MassSpectrum& );

        MassSpectrum& getSegment( size_t fcn /* o..n */ );

        const MassSpectrum& getSegment( size_t fcn /* 0..n */ ) const;

        MassSpectrum * findProtocol( int32_t proto );
        const MassSpectrum * findProtocol( int32_t proto ) const;
        std::shared_ptr< const MassSpectrum > getProtocol( int proto ) const; // Added 15/May 2019

        void clearSegments();
        size_t numSegments() const;
        void uuid( const char * uuid );
        const char * uuid() const;
        bool trim( adcontrols::MassSpectrum&, const std::pair<double, double>& massrange ) const;

        typedef std::vector< std::shared_ptr< MassSpectrum > >::iterator iterator;
        typedef std::vector< std::shared_ptr< MassSpectrum > >::const_iterator const_iterator;

        MassSpectrum& operator << ( std::shared_ptr< MassSpectrum >&& );
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        iterator erase( const_iterator first, const_iterator last );

    private:
        friend class boost::serialization::access;
        template<class Archiver> void serialize(Archiver& ar, const unsigned int version);

        class impl;
        impl * impl_;
    };

    struct ADCONTROLSSHARED_EXPORT segments_helper {
        static double max_intensity( const MassSpectrum& );
		static double min_intensity( const MassSpectrum& );
        static void set_color( MassSpectrum&, size_t fcn, size_t idx, int color );
        static int  get_color( const MassSpectrum&, size_t fcn, size_t idx );
        static std::pair<int, int> base_peak_index( const MassSpectrum&, double x1, double x2, bool isTime = false );
        static std::pair<double, double> acquisition_time_range( const MassSpectrum& );
        static double get_mass( const MassSpectrum&, const std::pair< int, int >& );
        static double get_intensity( const MassSpectrum&, const std::pair< int, int >& );
        static bool add( MassSpectrum&, const MassSpectrum& );
        static bool normalize( MassSpectrum&, uint32_t imaginalNumAverage = 10000 );
        static const annotations& get_annotations( const MassSpectrum&, const std::pair< int, int >& );
		static annotations& get_annotations( MassSpectrum&, const std::pair< int, int >& );
        static void addAnnotation( MassSpectrum&, adcontrols::annotation&&, const std::pair< int, int >& );
    };

    template<> ADCONTROLSSHARED_EXPORT void MassSpectrum::serialize( portable_binary_oarchive&, const unsigned int );
    template<> ADCONTROLSSHARED_EXPORT void MassSpectrum::serialize( portable_binary_iarchive&, const unsigned int );

}
