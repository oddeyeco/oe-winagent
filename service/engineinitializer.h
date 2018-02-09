#ifndef CENGINEINITIALIZER_H
#define CENGINEINITIALIZER_H

#include "engine.h"

class CEngineInitialzier
{
public:
    static void InitializeEngine( EngineSPtr pEngine );
    static IMetricsCategoryCheckerSPtr CreateCheckerByConfigName(QString const& sConfigName,
                                                         QString const& sSectionName);
private:
    // helpers
    static QString SimplifyName( QString sName );
    static QString ToCamelCase(const QString& s);
    static QString MakeCheckerName( QString const& sConfigName,
                                    QString const& sSectionName );
};

#endif // CENGINEINITIALIZER_H
