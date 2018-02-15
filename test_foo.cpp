extern "C"{
	#include "foo.h"
}

#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

using namespace std;
using namespace CppUnit;

class TestFoo : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestFoo);
	CPPUNIT_TEST(testFoo);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{}
	void tearDown()
	{}

protected:
	void testFoo(){
		CPPUNIT_ASSERT(foo() == 0);
	}
};

// main

CPPUNIT_TEST_SUITE_REGISTRATION(TestFoo);

int
main(int argc, char **argv)
{
	if(argc > 1)
		cerr << "usage: " << argv[0] << endl;

	CPPUNIT_NS::TestResult testresult;

	CPPUNIT_NS::TestResultCollector	collectedresults;
	testresult.addListener(&collectedresults);

	CPPUNIT_NS::BriefTestProgressListener progress;
	testresult.addListener(&progress);

	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testresult);

	CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	compileroutputter.write();

	ofstream xmlFileOut("test_foo.xml");
	XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	xmlOut.write();

	return collectedresults.wasSuccessful() ? 0: 1;
}
