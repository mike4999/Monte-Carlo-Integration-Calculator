/*
    PROGRAM: Monte Carlo Integration Calculator
    AUTHOR: Sean Easton (gonrada@gmail.com)
    COURSE INFORMATION: CIS5930 - Summer '11
    Due Date: 6-20-2011

    SUMMARY
        This program will calculate integral using Monte Carlo methods.
        It is the goal of the project to parallelize said methods with the hope
        boosting overall performance.
*/

#include "resources.h"

using namespace std;
using boost::uniform_01;

int main(int argc, char **argv)
{
    boost::mt19937 ranSeed(static_cast<unsigned int>(std::time(0)));
    uniform_01<boost::mt19937&> dist(ranSeed);
    uint64_t n = 0, i = 1;// number of random points
    double nSum = 0, nSumSq = 0, err = 0, e = 1, r;
    double lastPrint=1;
    double fHat, fSqHat;;
    time_t start, end;

    if (argc == 3)
    {
        if (strncmp(argv[1],"-e",2) == 0)
        {
            err = atof(argv[2]);
        }
        else
        {
            n = static_cast<uint64_t>(atof(argv[2]));
        }
    }
    else
    {
        n = 100000;
    }

//    cout<<"got here; n:"<<n<<" err:"<<err<<endl;

    start = time(0);

    r = dist(); // get a random value
    nSum += exp(-r*r);
    nSumSq += exp(-r*r) * exp(-r*r);

    for(i=2; i != n && e > err; ++i)
    {
        r = dist(); // get a random value

        nSum += exp(-r*r);
        nSumSq += exp(-r*r) * exp(-r*r);


        //http://math.fullerton.edu/mathews/n2003/montecarlomod.html

        fHat = nSum / i;
        fSqHat = nSumSq / i;

        e = sqrt((fSqHat-(fHat*fHat))/i);

        /*if ((lastPrint - e) > err)
        {
            cout<<i<<" "<<e<<endl;
            lastPrint = e;
        }*/
    }
    end = time(0);

//    cout<<i<<" "<<e<<endl;
    cerr<<i<<" random points; error:"<<e<<endl;
    cerr<<"time elapsed:"<<end-start<<" sec.\n";

    return 0;
}
