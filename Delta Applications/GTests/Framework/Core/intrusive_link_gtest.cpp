#include "gtest-common.h"
#include "TIntrusiveLink.h"
#include "TIntrusiveLinkedList.h"

class Dummy {
	friend class BareIntrusiveLinkTest;
	friend class PopulatedIntrusiveLinkTest;
private:
	TIntrusiveLink<Dummy> link;		
};

class BareIntrusiveLinkTest: public testing::Test {
protected:
	TIntrusiveLinkedList<Dummy, offsetof(Dummy, link)> list;
	Dummy d1, d2, d3;
};

class PopulatedIntrusiveLinkTest: public testing::Test {
	void SetUp() {
		list.AppendElement(&d1);
		list.AppendElement(&d2);
		list.AppendElement(&d3);
	}

protected:
	TIntrusiveLinkedList<Dummy, offsetof(Dummy, link)> list;
	Dummy d1, d2, d3;
};

TEST_F(BareIntrusiveLinkTest, CanAppend) {
	list.AppendElement(&d1);

	// Make sure it got inserted into the list correctly.
	EXPECT_EQ(&d1, list.GetHeadElement());
	EXPECT_EQ(&d1, list.GetTailElement());

	// Make sure adding a second element puts it into the list properly (APPEND)
	list.AppendElement(&d2);
	EXPECT_NE(&d2, list.GetHeadElement());
	EXPECT_EQ(&d2, list.GetTailElement());
	EXPECT_EQ(list.GetLinkFromElement(&d2), list.GetTail());	
}

TEST_F(BareIntrusiveLinkTest, CanPrepend) {
	list.PrependElement(&d1);

	// Make sure it got inserted into the list correctly.
	EXPECT_EQ(&d1, list.GetHeadElement());
	EXPECT_EQ(&d1, list.GetTailElement());

	// Make sure adding a second element puts it into the list properly (PREPEND)
	list.PrependElement(&d2);
	EXPECT_EQ(&d2, list.GetHeadElement());
	EXPECT_NE(&d2, list.GetTailElement());
	EXPECT_NE(list.GetLinkFromElement(&d2), list.GetTail());	
}

TEST_F(PopulatedIntrusiveLinkTest, GetNextPreviousLinks) {
	TIntrusiveLink<Dummy>* d1link = list.GetLinkFromElement(&d1);
	TIntrusiveLink<Dummy>* d2link = list.GetLinkFromElement(&d2);
	TIntrusiveLink<Dummy>* d3link = list.GetLinkFromElement(&d3);

	EXPECT_EQ(list.GetPreviousLink(d2link), d1link);
	EXPECT_EQ(list.GetNextLink(d2link), d3link);

	EXPECT_EQ(list.GetPreviousLink(d1link), (void*)NULL);
	EXPECT_EQ(list.GetNextLink(d1link), d2link);

	EXPECT_EQ(list.GetNextLink(d3link), (void*)NULL);
	EXPECT_EQ(list.GetPreviousLink(d3link), d2link);
}




