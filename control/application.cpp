#include "application.h"

CApplication::CApplication(int &argc, char **argv)
    : Base(argc, argv)
{
    QStringList args = Base::arguments();

    if (args.size() > 1) {
        QString a =  args.at(1);
        if (a == QLatin1String("-s") || a == QLatin1String("-start"))
        {
            printf("OddEye Agent is Starting\n");
            m_oController.Start();
//            if (!controller.isInstalled()) {
//                QString account;
//                QString password;
//                if (args.size() > 2)
//                    account = args.at(2);
//                if (args.size() > 3)
//                    password = args.at(3);
//                if (!install(account, password)) {
//                    fprintf(stderr, "The service %s could not be installed\n", serviceName().toLatin1().constData());
//                    return -1;
//                } else {
//                    printf("The service %s has been installed under: %s\n",
//                        serviceName().toLatin1().constData(), filePath().toLatin1().constData());
//                }
//            } else {
               fprintf(stderr, "The service %s is already installed\n");
//            }
        } else  if (a == QLatin1String("-h") || a == QLatin1String("-help")) {
            printf("\n%s -[i|u|e|t|p|r|c|v|h]\n"
                   "\t-i(nstall) [account] [password]\t: Install the service, optionally using given account and password\n"
                   "\t-u(ninstall)\t: Uninstall the service.\n"
                   "\t-e(xec)\t\t: Run as a regular application. Useful for debugging.\n"
                   "\t-t(erminate)\t: Stop the service.\n"
                   "\t-p(ause)\t: Pause the service.\n"
                   "\t-r(esume)\t: Resume a paused service.\n"
                   "\t-c(ommand) num\t: Send command code num to the service.\n"
                   "\t-v(ersion)\t: Print version and status information.\n"
                   "\t-h(elp)   \t: Show this help\n"
                   "\tNo arguments\t: Start the service.\n",
                   args.at(0).toLatin1().constData());
        }

    }
}
