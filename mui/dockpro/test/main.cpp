#include <gtest/gtest.h>

#include <QString>
#include <QtGlobal>
#include <QLoggingCategory>

int main(int argc, char *argv[])
{
    qSetMessagePattern(QStringLiteral("             ["
                                      "%{if-debug}\e[37mDEBUG\e[0m%{endif}"
                                      "%{if-info}\e[96mINFO \e[0m%{endif}%"
                                      "{if-warning}\e[93mWARN \e[0m%{endif}"
                                      "%{if-critical}\e[91mERROR\e[0m%{endif}"
                                      "%{if-fatal}\e[95mFATAL\e[0m%{endif}"
                                      " %{time yyyy/MM/dd hh:mm:ss.zzz} #%{threadid}] "
                                      "%{message}"));
    QLoggingCategory::setFilterRules("*.debug=true\n"
                                     "*.info=true\n"
                                     "*.warning=true\n"
                                     "*.error=true\n"
                                     "*.critical=true\n"
                                     "*.ssl.warning=false");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
