#include <gtest/gtest.h>
#include "mymap.h"
#include "myrandom.h"
#include <sstream>
#include<string>
#include<cstdlib>
#include <map>
#include <vector>
#include <queue>

//ikhan54
//tries out all varities
TEST(Size, testSizeDifferentDataTypes){

    mymap<int, int> map;
    int n = 10;
    int arr[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};

    for (int i = 0; i < n; i++) {
        map.put(arr[i], arr[i]);
    }

    ASSERT_EQ(map.Size(), n);

    mymap<char, int> mapTwo;
    char key = 'A';
    int arrTwo[] = {7, 15, 50, 8, 25, 9, 20, 28, 40, 60};

    for (int i = 0; i < n; i++) {
        mapTwo.put(key, arrTwo[i]);
        key++;
    }

    ASSERT_EQ(mapTwo.Size(), n);

    mymap<string, int> mapThree;
    string arrThree[] = {"Yousef", "Imran", "Waqar","Junaid","Zeeya","Shariq","Muneeb","Sohaib","Naveed","Moneeb"};
    int arrFour[] = {7, 15, 20, 3, 25, 9, 23, 28, 41, 62};

    for (int i = 0; i < n; i++) {
        mapThree.put(arrThree[i], arrFour[i]);
    }

    ASSERT_EQ(mapThree.Size(), n);
    mapThree.clear();
    map.clear();
    mapTwo.clear();

}

//yhabe2
TEST(mymap, get_default) {
    mymap<int, int> m;
    int arr = {};
    EXPECT_EQ(m.get(12837), 0);
}
//yhabe2
TEST(mymap, get_wrong) {

    mymap<int, int> m;
    int arr = {};
    EXPECT_NE(m.get(373837248), 1);
}

//yhabe2
TEST(mymap1, defaultConstructor) {
    mymap<int, int> m;
    EXPECT_EQ(m.Size(), 0);
    EXPECT_NE(m.Size(), 1);
}

//yhabe2
TEST(mymap1, defaultConstructordouble) {
    mymap<int, double> m;
    EXPECT_EQ(m.Size(), 0);
    EXPECT_NE(m.Size(), 1);
}

//yhabe2
TEST(mymap1, defaultConstructordoublestring) {
    mymap<string, double> m;
    EXPECT_EQ(m.Size(), 0);
    EXPECT_NE(m.Size(), 1);
}

//yhabe2
TEST(mymap1, defaultConstructordoublechar) {
    mymap<double, char> m;
    EXPECT_EQ(m.Size(), 0);
    EXPECT_NE(m.Size(), 1);
}

//yhabe2
TEST(mymap1, defaultConstructorstring) {
    mymap<string, int> m;
    EXPECT_EQ(m.Size(), 0);
    EXPECT_NE(m.Size(), 1);
}
//yhabe2
TEST(mymap1, defaultConstructorcharString) {
    mymap<char, string> m;
    EXPECT_EQ(m.Size(), 0);
    EXPECT_NE(m.Size(), 1);
}
//yhabe2
TEST(mymap1, defaultConstructorwrong) {
    mymap<int, int> m;
    EXPECT_NE(m.Size(), 1);
}


// netid: rshah268
// Copy and Clear Stress Test
TEST(mymap, Copy) {
    
    // Create two mymaps m1 and m2
    mymap<int, int> m1;
    mymap<int, int> m2;
    int n = 10000;

    for(int  i = 0; i < n; i++) {

        // Generate two random numbers
        int key = rand() %  100000;
        int val = rand() %  100000;

        // Insert them in map1
        m1.put(key, val);

        // Insert different elements in map2
        if(i % 2) {
            m2.put(val, key);
        }
    }

    // At this point they must be unequal
    ASSERT_NE(m1.Size(), m2.Size());

    // Set map2 equals to map1
    m2 = m1;

    // Both should be the same size and contain the same elements
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());

    // Clear map1
    m1.clear();
   

    // Now they are unequal again
    ASSERT_NE(m1.Size(), m2.Size());
    // Map1 must be empty
    ASSERT_EQ(m1.Size(), 0);
     m2.clear();
}




// milestone 1 tests 
// ssulta24
// default constructor Test and size Test
TEST(mymap, defaultConstructor) {

    // create a mymap
    mymap<int, int> m; 

    // check if the size is 0
    EXPECT_EQ(m.Size(), 0);

}

// ssulta24
// put Test and size Test
TEST(mymap, put) {

    // create a mymap
    mymap<int, int> m; 

    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        m.put(arr[i], arr[i]);
    }
    EXPECT_EQ(m.Size(), 3);
    m.clear();
}


// ssulta24
// stress test combining all the tests above 
TEST(mymap, stressTest) {

    // create a mymap
    mymap<int, int> m; 

    vector< int > arr;

    for (int i = 0; i < 10000; i++) {
        int num = rand() %  10000;
        // append num to arr 
        arr.push_back(num);
        m.put(i, num);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m[i], arr[i]);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.contains(i), true);
    }

    for (int i = 0; i < 10000; i++) {
        EXPECT_EQ(m.get(i), arr[i]);
    }

    EXPECT_EQ(m.Size(), 10000);
    m.clear();
}


//ikhan54
//using int copy 
TEST (mymap, sample) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    int order[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }
    map.clear();
}

//ikhan54
//using int copy 
TEST(mymap, clear) {
  // using int
  mymap<int,int> m;
  for (int i=0;i<5;i++) {
    int x = i;
    m.put(x, x);
    EXPECT_NE(m.Size(), 0);
  }
  m.clear();
  ASSERT_EQ(m.Size(), 0);


}
//ikhan54
//using int copy 
TEST(mymap, clear2) {
  // using int
  mymap<int,int> m;
  for (int i=0;i<10000;i++) {
    int x = rand() %  100000;
    int y = rand() %  100000;
    m.put(x, y);
    EXPECT_NE(m.Size(), 0);
  }
  m.clear();
  ASSERT_EQ(m.Size(), 0);


}

//ikhan54
//using int copy 
TEST(mymap, clear3) {
  // using int
  mymap<int,int> m;
  for (int i=0;i<10000;i++) {
    int x = i;
    m.put(x, x);
    EXPECT_NE(m.Size(), 0);
  }
  m.clear();
  ASSERT_EQ(m.Size(), 0);


}


//ikhan54
//using int copy 
TEST(mymap, copyOperator) {
  // using int
    mymap<int,int> m1;
    for (int i=0;i<100;i++) {
        int x = i;
        m1.put(x, x);
    }
    mymap<int,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());
   m1.clear();
   m2.clear();
}

//ikhan54
//using int copy 
TEST(mymap, copyOperator2) {
  // using int
    mymap<int,int> m1;
    for (int i=0;i<1000;i++) {
        int x = i;
        m1.put(x, x);
    }
    mymap<int,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());
    m1.clear();
   m2.clear();
  
}
//ikhan54
//using int copy 
TEST(mymap, copyOperator3) {
  // using int
    mymap<int,int> m1;
    for (int i=0;i<1000;i++) {
        int x = rand() %  100000;
        int y = rand() %  100000;
        m1.put(x, y);
    }
    mymap<int,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());
    m1.clear();
    m2.clear();
  
}
//ikhan54
//using string copy 
TEST(mymap, copyOperator4) {
  // using int
  vector<string> str = {"Hello","Hello1","Hello2","Hello3","Hello4","Hello5","Hello6","Hello7","Hello8","Hello9","Hello10","Hello11","Hello12","Hello13","Hello14","Hello15"};
    mymap<string,int> m1;
    for (int i=0;i<1000;i++) {
        int x = rand() %  100000;
        int y = rand() %  16;
        string add = str[y];
        m1.put(add, x);
    }
    mymap<string,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());
   m1.clear();
   m2.clear();
  
}
//ikhan54
//using char copy 
TEST(mymap, copyOperator5) {
  // using str
  vector<char> str;
  for(int i=0;i<100;i++){
    int y = randomInteger(65,90);
    char p = (char)y;
    str.push_back(p);
  }
    mymap<char,int> m1;
    for (int i=0;i<1000;i++) {
  
        int y = rand() %  100;
        char add = str[y];
        m1.put(add, y);
    }
    mymap<char,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());
    m1.clear();
   m2.clear();
  
}
//ikhan54
//using char copy 
TEST(mymap, copyOperator6) {
  // using str
  vector<char> str;
  for(int i=0;i<100;i++){
    int y = randomInteger(98,122);
    char p = (char)y;
    str.push_back(p);
  }
    mymap<char,int> m1;
    for (int i=0;i<1000;i++) {
     
        int y = rand() %  100;
        char add = str[y];
        m1.put(add, y);
    }
    mymap<char,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());
   m1.clear();
   m2.clear();
  
}
//ikhan54
//using char copy and clear repeat
TEST(mymap, stress) {
  // using str
  vector<char> str;
  for(int i=0;i<100;i++){
    int y = randomInteger(65,90);
    char p = (char)y;
    str.push_back(p);
  }
    mymap<char,int> m1;
    for (int i=0;i<1000;i++) {
  
        int y = rand() %  100;
        char add = str[y];
        m1.put(add, y);
    }
    mymap<char,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());

    m1.clear();
    EXPECT_EQ(m1.Size(), 0);
    m1 = m2;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());

    m1.clear();
    m2.clear();
    EXPECT_EQ(m2.Size(), m1.Size());
  
}
//ikhan54
//using char copy and clear repeat
TEST(mymap, stress2) {
  // using str
  vector<char> str;
  for(int i=0;i<100;i++){
    int y = randomInteger(98,122);
    char p = (char)y;
    str.push_back(p);
  }
    mymap<char,int> m1;
    for (int i=0;i<1000;i++) {
     
        int y = rand() %  100;
        char add = str[y];
        m1.put(add, y);
    }
    mymap<char,int> m2 = m1;
    m2 = m1;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());

  
    m1.clear();
    EXPECT_EQ(m1.Size(), 0);
    m1 = m2;
    EXPECT_EQ(m2.Size(), m1.Size());
    EXPECT_EQ(m2.toString(), m1.toString());

    m1.clear();
    m2.clear();
    EXPECT_EQ(m2.Size(), m1.Size());
}

//ikhan54
//tests the destructors
TEST(mymap, destructors) {
    mymap<int, int> test;
    for(int i = 0; i < 100; i++) {
    int k = i;
    int v = i+1;
    test.put(k, v);
    }
    mymap<int,int>test2(test);
    mymap<int,int> test3;
    test3 = test2;
    test.clear();
    test2.clear();
    test3.clear();
  
}



int main(int argc, char **argv) 
    {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    }


