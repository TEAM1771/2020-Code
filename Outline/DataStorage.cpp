#include <map>
#include <string>
#include <vector>


//A file that can connect to each of the others and
//handle any of the universal data we need send
//when it's not practical to do so by function alone 


class DataPoint{
public:
	union{
		int i;
		double d;
		long l;
	} 
	n;
	std::string s;
	std::vector<DataPoint*> v;
};



class DataStorage{
public:
	std::map<std::string,DataPoint*> data;
};

int main(){
	return 0;
}