#include "oddeyeselfcheck.h"
#include "basicmetricchecker.h"
#include "pinger.h"

//
//  class OddeyeSelfCheck
//
OddeyeSelfCheck::OddeyeSelfCheck( QObject* pParent )
    : Base( pParent )
{
    m_sOddEyeAddress = "api.oddeye.co";
}

void OddeyeSelfCheck::Initialize()
{
    double dConfHighVal   = -1;
    double dConfSevereVal = -1;

    bool bStaticAlertingEnabled = ConfigSection().Value<bool>("static_enabled", false);
    if( bStaticAlertingEnabled )
    {
        dConfHighVal   = ConfigSection().Value<double>("high", -1);
        dConfSevereVal = ConfigSection().Value<double>("severe", -1);
    }

    BasicMetricCheckerSPtr pChecker = std::make_shared<CBasicMetricChecker>("oddeye_self_check_time",
                                                                            EMetricDataType::Counter,
                                                                            "OddEye_Specific", 0,
                                                                            dConfHighVal,
                                                                            dConfSevereVal );
    pChecker->SetValueCheckerFunction(
    [this]()
    {
        Q_ASSERT(!m_sOddEyeAddress.isEmpty());
        double dPingTime = CPinger::RoundTripTime( m_sOddEyeAddress );
        return dPingTime;
    } );

    Base::AddMetricChecker( pChecker );
}


