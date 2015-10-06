/*
 * DynamicBayesNetTestSuite.h
 *
 *  Created on: 16 avr. 2009
 *      Author: morgan
 */


#include <cxxtest/TestSuite.h>
#include "../src/DynamicBayesNet.h"
#include <agrum/multidim/labelizedVariable.h>


class DynamicBayesNetTestSuite : public CxxTest::TestSuite {

public:

	gum::LabelizedVariable *var1, *var2, *var3, *var4, *var5;

	void setUp() {
		var1 = new gum::LabelizedVariable( "var1", "1", 2 );
		var2 = new gum::LabelizedVariable( "var2", "2", 2 );
		var3 = new gum::LabelizedVariable( "var3", "3", 2 );
		var4 = new gum::LabelizedVariable( "var4", "4", 2 );
		var5 = new gum::LabelizedVariable( "var5", "(gum::Size) 5", 3 );
	}

	void tearDown() {
		delete var1;
		delete var2;
		delete var3;
		delete var4;
		delete var5;
	}


	void testConstructor() {
		DynamicBayesNet *topology=NULL;
		TS_ASSERT_THROWS_NOTHING( topology = new DynamicBayesNet() );
		TS_ASSERT_THROWS_NOTHING( delete topology );
	}

	void testInsertion() {
		DynamicBayesNet dbn;

		TS_ASSERT_THROWS_NOTHING( dbn.addVariable(*var1));

	}

};
