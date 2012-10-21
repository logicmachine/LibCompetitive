#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <typename InputIterator, typename OutputIterator>
void coordinates_compression(
	InputIterator begin, InputIterator end, OutputIterator output)
{
	typedef typename iterator_traits<InputIterator>::value_type value_type;
	vector<value_type> a(begin, end);
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
	for(InputIterator it = begin; it != end; ++it){
		*(output++) = lower_bound(a.begin(), a.end(), *it) - a.begin();
	}
}

