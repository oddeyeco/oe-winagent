#ifndef CAGENTITIALIZER_H
#define CAGENTITIALIZER_H

#include "engine.h"

class CAgentInitialzier
{
public:
    static void InitializeLogger();
    static void InitializeEngine( CEngine* pEngine );
    static IMetricsCategoryCheckerSPtr CreateCheckerByConfigName( QString const& sConfigName,
                                                                  QString const& sSectionName = QString());

    //static QString MakeCheckerName( QString const& sDirtyName );

private:
    // helpers
    static QString SimplifyName( QString sName );
    static QString ToCamelCase(const QString& s);
    static QString MakeCheckerName( QString const& sConfigName,
                                    QString const& sSectionName = QString() );


private:
    // content
    static QString s_sDefaultLogDir;
};

#endif // CAGENTITIALIZER_H
