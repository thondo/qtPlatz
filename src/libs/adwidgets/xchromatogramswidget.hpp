/**************************************************************************
** Copyright (C) 2010-2017 Toshinobu Hondo, Ph.D.
** Copyright (C) 2013-2017 MS-Cheminformatics LLC, Toin, Mie Japan
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

#include "adwidgets_global.hpp"
#include <adwidgets/lifecycle.hpp>
#include <QWidget>
#include <memory>

class QMenu;
class QStandardItemModel;

namespace adcontrols { class TofChromatogramsMethod; class XChromatogramsMethod; class MassSpectrometer; }

namespace adwidgets {

    class ADWIDGETSSHARED_EXPORT XChromatogramsWidget : public QWidget
                                                      , public adplugin::LifeCycle {

        Q_OBJECT
        Q_INTERFACES( adplugin::LifeCycle )

    public:
        enum columns { c_id, c_formula, c_mass, c_masswindow, c_time, c_timewindow, c_algo, c_protocol, ncolumns };

        explicit XChromatogramsWidget(QWidget *parent = 0);
        ~XChromatogramsWidget();

        // adplugin::LifeCycle
        void OnCreate( const adportable::Configuration& ) override;
        void OnInitialUpdate() override;
        void onUpdate( boost::any&& ) override;
        void OnFinalClose() override;
        bool getContents( boost::any& ) const override;
        bool setContents( boost::any&& ) override;
        //
        bool getContents( adcontrols::XChromatogramsMethod& ) const;

        adcontrols::XChromatogramsMethod getValue() const;
        bool setValue( const adcontrols::XChromatogramsMethod& );
        //
        void setDigitizerMode( bool ); // true for soft accumulate, false for hard averaged
        void setMassSpectrometer( std::shared_ptr< const adcontrols::MassSpectrometer > );

    private:

        class impl;
        std::unique_ptr< impl > impl_;

    signals:
        void valueChanged( const QString& json );
        void editorValueChanged( const QModelIndex&, double );

    public slots:

    private slots:
        void handleValueChanged();

    };

}
