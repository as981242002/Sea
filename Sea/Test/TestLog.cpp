#include "../Src/Base/Utility/Log.h"
#include "../Src/Base/Utility/LogStream.h"
#include "../Src/Base/Utility/Utility.h"
#include "../Test/TestLog.h"

using namespace Sea;
using std::cout;
using std::endl;

void testLog()
{
	LogStream test;
	tm now = GetNowTime();
	test << now;
	cout << test.print() << endl;
}
