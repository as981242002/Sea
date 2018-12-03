#include "../Src/Base/Utility/Log.h"
#include "../Src/Base/Utility/LogStream.h"
#include "../Src/Base/Utility/Utility.h"
using namespace Sea;
using std::cout;
using std::endl;

int main()
{
	LogStream test;
	tm now = GetNowTime();
	test << now;
	cout << test.print() << endl;
}