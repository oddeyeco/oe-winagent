#include "application.h"
#include "logger.h"

CApplication::CApplication(int &argc, char **argv)
    : Base( argc, argv )
{
}

bool CApplication::notify(QObject* pObject, QEvent *pEvent)
{
    try
    {
        return Base::notify( pObject, pEvent );
    }
    catch( std::exception const& oExcep )
    {
        LOG_ERROR( std::string( "Exception: " ) + oExcep.what() );
    }
    catch(...)
    {
        LOG_ERROR( "Critical Error: Undefined exception!" );
    }
    return false;
}
