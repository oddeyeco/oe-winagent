#include "advanced_perfcounters_enabled.h"

INIT_METRIC_CHECKER(AdvancedPerfCountersEnabled, )
{
    auto a = ConfigSection();

    for( auto it = a.begin(); it != a.end(); ++it )
    {
        QString sMetricName = it.key().trimmed();
        QString sCounterPath = it.value().toString().trimmed();

        Q_ASSERT( !sMetricName.isEmpty() );
        Q_ASSERT( !sCounterPath.isEmpty() );

        if( sMetricName.isEmpty() || sCounterPath.isEmpty() )
            continue;

        try
        {
            // give data provider
           AddPerformanceCounterChecker( sCounterPath, "AdvancedPerformanceCounters", sMetricName);
        }
        catch( std::exception const& oExc )
        {
            QString sMsg = QString( "Advanced Performance Counters metric initialization failed: Error: %1" ).arg( oExc.what() );
            LOG_ERROR( sMsg.toStdString() );
        }

    }
}
