#include <iostream>
#include "dbtp.h"
#include "Tables.h"
using namespace std;

//////////////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////////////
int main ()
{
        /*******************************************************/
        /*******************************************************/
        /**   Create and load the initial database            **/
        /*******************************************************/
        /*******************************************************/

    // I have commented this part temporary to avoid the loading of the database each single test
        /*
        table BL2013_F;
        table BL2013_F1599;
        table BL2013_F2599;
        table BL2013_MF;
        table BL2013_MF1599;
        table BL2013_MF2599;

        loadTable("Education/BL2013_F.csv", &BL2013_F);
        loadTable("Education/BL2013_F1599.csv", &BL2013_F1599);
        loadTable("Education/BL2013_F2599.csv", &BL2013_F2599);
        loadTable("Education/BL2013_MF.csv", &BL2013_MF);
        loadTable("Education/BL2013_MF1599.csv", &BL2013_MF1599);
        loadTable("Education/BL2013_MF2599.csv", &BL2013_MF2599);

        table test = JOIN(BL2013_F1599,BL2013_MF,"year");
        cout<<test.tuples.size()<<endl;
        */

        /*******************************************************/
	/*******************************************************/
	/*******************************************************/

	/*******************************************************/
        /*** Creation of Query Plan for Example 1           ****/
        /*******************************************************/

        QueryPlan queryPlan;
        queryPlan.addNode(0,0,"O-JOIN","partkey");
        queryPlan.addNode(1,0,"O-DISTINCT","partkey");
        queryPlan.addNode(2,1,"O-PROJECTION","partkey");
        queryPlan.addNode(3,2,"P","2*supplycost,<,retailprice");
        queryPlan.addNode(4,3,"O-JOIN","retailprice");
        queryPlan.addNode(5,4,"T","P");
        queryPlan.addNode(6,4,"T","PS");
        queryPlan.addNode(7,0,"P","10*avail,<,numsold");
        queryPlan.addNode(8,7,"O-JOIN","partkey");
        queryPlan.addNode(9,8,"Y","avail");
        queryPlan.addNode(10,9,"P","retailprice,=,OTHER");
        queryPlan.addNode(11,8,"Y","numsold");
        queryPlan.addNode(12,11,"P","receiptdate,>,2007-1-1,AND,OTHER");
        queryPlan.addNode(13,12,"T","L");
        queryPlan.addNode(14,13,"P","p_partkey,=,ps_partkey");
        /******************************************************/
        /** Source-Graph for transitively equated predicates **/
        /******************************************************/
        queryPlan.attributesEq.push_back("p_partkey,=,ps_partkey");
        queryPlan.attributesEq.push_back("p_partkey,=,avail.partkey");
        queryPlan.attributesEq.push_back("p_partkey,=,sold.partkey");

        /*******************************************************/
        /** Execution                                         **/
        /*******************************************************/
        queryPlan.createPredLists();
        queryPlan.createSources();
        queryPlan.showVector("GENERAL PREDICATE LIST",queryPlan.generalPredicateList.pList);
        queryPlan.showVector("CONJ PREDICATE LIST",queryPlan.conjPredicateList.pList);
        queryPlan.showMapSources();
        queryPlan.getAip();
        queryPlan.showMapSources();
        queryPlan.showMapInterestedIn();
        /*******************************************************/

/*
        // Show List of Nodes
        queryPlan.showNodeList();
        vector<string> predList;
        predList = queryPlan.getPredicatesNode(11);
        queryPlan.showVector("NODE PREDICATES", predList);

        vector<string> att, poa;
        att = queryPlan.getAttributes(3);
        queryPlan.showVector("NODE ATTRIBUTES", att);

        poa = queryPlan.getPredicatesOver(att);
        queryPlan.showVector("PRED OVER ATT(3)",poa);

        vector<string> aaa,bbb,ccc,ddd;
        aaa.push_back("aaa");
        aaa.push_back("bbb");
        aaa.push_back("ccc");
        aaa.push_back("ddd");
        aaa.push_back("eee");
        //aaa.push_back("fff");
        aaa.push_back("ggg");

        bbb.push_back("aaa");
        bbb.push_back("aaa");
        bbb.push_back("ddd");
        bbb.push_back("fff");
        ccc = queryPlan.subtractLists(aaa,bbb);
        queryPlan.showVector("SUBTRACT LIST",ccc);

        ddd = queryPlan.intersectLists(aaa,bbb);
        queryPlan.showVector("INTERSECT LIST",ddd);

        // Adding definition for predicate nodes
*/

/*
        // TEST for AIP Registry
	PredicateData aipRegistry;
	//aipRegistry.checkPredicate(0);
	aipRegistry.addPredicate(0,"preda",0);
	aipRegistry.addPredicate(1,"predb",1);
	aipRegistry.addPredicate(2,"predc",2);
	aipRegistry.addPredicate(3,"predd",3);
        aipRegistry.showFullRegistry();

        aipRegistry.checkPredicate(1);
*/

        printf("PID of this process: %d\n", getpid());
        pthread_t thread1, thread2;
        pthread_create(&thread1, NULL, someThread, NULL);
        sleep(1);
        pthread_create(&thread2, NULL, someThread, NULL);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);


	exit(0);
}
