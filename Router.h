#include <time.h>
#include <vector>
#include <climits>
using namespace std;

class Router
{
  private:
    int ID;
    double delayProcessing;
    double delayTransmission;
    double delayQueueing;
    double delayPropagation;
    double speedPropagation;
    double lossProbability;
    double bandwidth;
  public:
    Router();
    Router(int id, double s_prop, double loss, double band);
    ~Router();

    void newLink(Router * newRouter, int length);
    double internalDelay();
    double timeOfTravel(Router * dest, int packetSize);
    int getID();

    vector<pair<Router*, int> > routerLinks;
};