
// Is bigger smarter?

#include <iostream>
#include <ostream>
#include <iterator>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;


class Elephant
{
  int weight;
  int IQ;

  int index;

public:

    Elephant( int _index, int _weight, int _IQ ) {  set_index(_index); set_weight(_weight); set_IQ(_IQ); }

    void set_weight(int _weight ) { weight = _weight; }
    void set_IQ(int _IQ ) { IQ = _IQ; }
    void set_index( int _index ) { index = _index; }

    int get_weight() const { return weight; }
    int get_IQ() const { return IQ; }
    int get_index() const { return index; }

    bool operator< ( Elephant e2 ) const {
      if ( weight != e2.get_weight())
        return weight < e2.get_weight();
      else
        return IQ > e2.get_IQ();
    }

};

std::ostream& operator<<( std::ostream& os, const Elephant& e )
{
    os << e.get_index() << " " << e.get_weight() << " " << e.get_IQ();
}

typedef vector<Elephant> elephant_list;


elephant_list read_input(string filename)
{
     elephant_list v;
     ifstream f(filename.c_str(), ifstream::in);

     int weight, IQ, i = 0;
     while( f.good() )
     {
        f >> weight >> IQ;
        Elephant p(i, weight, IQ);
        v.push_back(p);
        i++;
     }
     f.close();
     return v;
}

void LIS( const elephant_list &a )
{
    int P[100];
    int L[100];

    int maxlis = 1, best = 0;
    int s = a.size();

    L[0] = 1; P[0] = -1;

    for( int poz=1; poz < s; poz++ )
    {
      L[poz] = 1;
      P[poz] = -1;
      for( int k = 0; k < poz; k++ )
      {
        if ( a[k].get_weight()<a[poz].get_weight() && a[k].get_IQ()>a[poz].get_IQ() && L[k] < L[poz] + 1) {
            L[poz] = L[k] + 1;
            P[poz] = k;
        }
      }
      if(maxlis < L[poz]) {
        maxlis = L[poz];
        best = poz;
      }
    }

    cout << maxlis << endl;

    stack<Elephant> solution;

    for( int k = best; k!=-1; k = P[k] )  solution.push(a[k]);

    while(!solution.empty()) { cout << solution.top().get_index() + 1 << endl; solution.pop(); }
}

void show_elephants( const elephant_list &elephants )
{
    copy(elephants.begin(), elephants.end(), ostream_iterator<Elephant>(cout, "\n"));
}

int main(void)
{
    elephant_list elephants = read_input("P11.6.1_input.1.txt");
	
	// Solve, find the longest increasing subsequence in a specially sorted sequence
    sort(elephants.begin(), elephants.end());
    LIS(elephants);
    return 0;
}
