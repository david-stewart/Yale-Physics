#ifndef MINMAXMEANVAR__H
#define MINMAXMEANVAR__H

#include "TMath.h"
#include <iostream>
class MinMaxMeanVar {
    private:
        long long int n;
        double sum;
        double sumSq;
        double minval;
        double maxval;
    public:
        MinMaxMeanVar() :
            n{0},
            sum{0.},
            sumSq{0.},
            minval{0.},
            maxval{0.}
        {};
        void operator()(double val){
            std::cout << "This is val " << val;
            if (n == 0) {
                minval = val;
                maxval = val;
            } else {
                if (val < minval) minval = val;
                if (val > maxval) maxval = val;
            }
            n += 1;
            sum += val;
            sumSq += val*val;
            std::cout << " n " << n << "  sum " << sum << "   min " << minval << "   maxval " << maxval << std::endl;

        };
        void operator()(int val){
            if (n == 0) {
                minval = val;
                maxval = val;
            } else {
                if (val < minval) minval = val;
                if (val > maxval) maxval = val;
            }
            n += 1;
            sum += val;
            sumSq += val*val;

        };
        double my_std() { return TMath::Sqrt( (sumSq - (sum*sum)/n)/(n-1)); };
        double std() { return TMath::Sqrt( (sumSq - (sum*sum)/n)/(n-1)); };
        double my_mean() { return sum / n; };
        double mean() { return sum / n; };
        double min()  { return minval; };
        /* int    minInt() { return (int) minval; }; */
        double max()  { return maxval; };
        /* double maxInt()  { return (int) maxval; }; */
        int    get_n() { return n; } ;
        void print(FILE* fout, const char name[30]) {
            std::cout << " ---  Data : " << name << "  "<<n<<"  "<<minval<<"  "<<maxval<<"  "<<my_mean()<<"  "<<my_std()<< std::endl;
            printf("#!    %9lli %8.4f %8.4f %8.4f %8.4f\n", n, minval, maxval, my_mean(), my_std());
            /* else */
                /* fprintf(fout, "#!   %9i %10.5f %10.5f %10.5f %10.5f\n", n, minval, maxval, mean(), std()); */

            /* printf("----"); */
            /* printf("      nam  %f %f %i\n", n, minval, maxval); */
            /* printf("again name %i %i %i %f\n",  n,minval, maxval, mean()); */
            /* printf("-.-.-.-"); */
            /* std::cout << " name" << name << "  "<<n<<"  "<<minval<<"  "<<maxval<<"  "<<mean()<<"  "<<std()<< std::endl; */
        };
};

#endif
