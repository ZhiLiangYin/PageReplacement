#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <vector>
#include <unistd.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

struct content{
  int page ;
  int time ;
};

struct donedata{
  int page ;
  vector<content> stack ;
  char fault ; 
};

bool isexsit( string namestr, vector<int> &nondo, char &way, char &page ) {
  namestr = namestr + ".txt" ;
  fstream fin ;
  fin.open( namestr.c_str(), ios::in ) ;
  if( !fin ) return false ;
  else{
    
    fin >>  way ;
    fin >> page;
    
    char temp ;
    while ( fin ) {
      fin >> temp ;
      nondo.push_back( (int)temp - 48 ) ;	
    }
    
    nondo.pop_back() ;
    return true ;
  }


  fin.close() ;
  return false ;
}

bool issame( vector<content> record, int page, int &where ) {
  for( int i = 0 ; i < record.size() ; i++ ) {
    if ( record[i].page == page ) {
      where = i ;
      return true ;
    } // if
  }

  where = -1 ;
  return false ;
}

int minnum( vector<content> record ) {
  int temptime = record[0].time ;
  int tempnum = 0  ;
  for( int i = 0 ; i < record.size() ; i++ ) {
    if ( temptime > record[i].time ) {
      temptime = record[i].time ;
      tempnum = i ;
    } // if
  }

  return tempnum ;
}

int maxnum( vector<content> record ) {
  int temptime = record[0].time ;
  int tempnum = 0  ;
  for( int i = 0 ; i < record.size() ; i++ ) {
    if ( temptime < record[i].time ) {
      temptime = record[i].time ;
      tempnum = i ;
    } // if
  }

  return tempnum ;
}

void FIFO( vector<int> nondo, char page, vector<donedata> &fifodone  ){
  vector<content> record ;
  for( int i = 0 ; i < nondo.size() ; i++ ) {
  	donedata tempall ;
  	content tempimp ;
  	tempall.page = nondo[i] ;
  	if( record.size() < page - '0' ) {
  	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	else {
	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	record.erase( record.begin() ) ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	
	fifodone.push_back( tempall ) ;
  	
  }
}

void LRU( vector<int> nondo, char page, vector<donedata> &lrudone  ){
  vector<content> record ;
  for( int i = 0 ; i < nondo.size() ; i++ ) {
  	donedata tempall ;
  	content tempimp ;
  	tempall.page = nondo[i] ;
  	if( record.size() < page - '0' ) {
  	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	tempimp.page = nondo[i] ;
  	  	record.erase( record.begin()+where ) ;
  	  	record.push_back(tempimp) ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	else {
	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	
  	  	tempimp.page = nondo[i] ;
  	  	record.erase( record.begin()+where ) ;
  	  	record.push_back(tempimp) ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	record.erase( record.begin() ) ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	
	lrudone.push_back( tempall ) ;
  	
  }
}

void LFUFI( vector<int> nondo, char page, vector<donedata> &lfufidone  ){
  vector<content> record ;
  for( int i = 0 ; i < nondo.size() ; i++ ) {
  	donedata tempall ;
  	content tempimp ;
  	tempall.page = nondo[i] ;
  	if( record.size() < page - '0' ) {
  	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	record[where].time = record[where].time + 1 ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	tempimp.time = 1 ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	else {
	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	record[where].time = record[where].time + 1 ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	record.erase( record.begin() + minnum( record ) ) ;
	  	tempimp.time = 1 ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	
	lfufidone.push_back( tempall ) ;
  	
  }
}

void MFUFI( vector<int> nondo, char page, vector<donedata> &mfufidone  ){
  vector<content> record ;
  for( int i = 0 ; i < nondo.size() ; i++ ) {
  	donedata tempall ;
  	content tempimp ;
  	tempall.page = nondo[i] ;
  	if( record.size() < page - '0' ) {
  	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	record[where].time = record[where].time + 1 ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	tempimp.time = 1 ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	else {
	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	record[where].time = record[where].time + 1 ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	record.erase( record.begin() + maxnum( record ) ) ;
	  	tempimp.time = 1 ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	
	mfufidone.push_back( tempall ) ;
  	
  }
}

void LFULRU( vector<int> nondo, char page, vector<donedata> &lfulrudone  ){
  vector<content> record ;
  for( int i = 0 ; i < nondo.size() ; i++ ) {
  	donedata tempall ;
  	content tempimp ;
  	tempall.page = nondo[i] ;
  	if( record.size() < page - '0' ) {
  	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	tempimp.page = nondo[i] ;
  	  	tempimp.time = record[where].time + 1 ;
  	  	record.erase( record.begin()+where ) ;
  	  	record.push_back(tempimp) ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	tempimp.time = 1 ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	else {
	  int where = -1 ;
  	  if( issame( record, nondo[i], where ) ) {
  	  	tempimp.page = nondo[i] ;
  	  	tempimp.time = record[where].time + 1 ;
  	  	record.erase( record.begin()+where ) ;
  	  	record.push_back(tempimp) ;
  	  	tempall.stack = record ;
  	  	tempall.fault = '\0' ;
	  }
	  else {
	  	tempimp.page = nondo[i] ;
	  	tempimp.time = 1 ;
	  	record.erase( record.begin() + minnum( record ) ) ;
	  	record.push_back(tempimp) ;
	  	tempall.stack = record ;
	  	tempall.fault = 'F' ;
	  }
	}
	
	lfulrudone.push_back( tempall ) ;
  	
  }
}

void printsingle( vector<donedata> &done, char way, string filename, char page ) {
  filename = "out_" + filename + ".txt" ;
  ofstream fout( filename.c_str() ) ;  

  string temp ;	
  if( way == '1' ) temp = "FIFO" ;
  else if( way == '2' ) temp = "LRU" ;
  else if( way == '3' ) temp = "Least Frequently Used Page Replacement" ;
  else if( way == '4' ) temp = "Most Frequently Used Page Replacement" ;
  else if( way == '5' ) temp = "Least Frequently Used LRU Page Replacement" ;
  
  fout << "--------------"<< temp <<"-----------------------\n"  ;
  cout << "--------------"<< temp <<"-----------------------\n" ;
  
  int fault = 0 ;
  for( int i = 0 ; i < done.size() ; i++ ) {
    fout << done[i].page << "\t" ;
    cout << done[i].page << "\t" ;
    for( int j = done[i].stack.size() - 1 ; j >= 0 ; j-- ) {
    	fout << done[i].stack[j].page  ;
    	cout << done[i].stack[j].page  ;
    }

      if (  done[i].fault == 'F' )
      {
        fault++ ;
        fout << "\tF"  ;
        cout << "\tF"  ;
      } // if

      fout <<"\n" ;
	  cout <<"\n" ;
    }
    
    fout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    fout << "  Page Frames = " << page << "\n\n" ;
    cout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    cout << "  Page Frames = " << page << "\n\n" ;
    
}

void printall( vector<donedata> done1, vector<donedata> done2, vector<donedata> done3, vector<donedata> done4, vector<donedata> done5, string filename, char page ) {
  filename = "out_" + filename + ".txt" ;
  ofstream fout( filename.c_str() ) ;  
/*
  string temp ;	
  if( way == '1' ) temp = "FIFO" ;
  else if( way == '2' ) temp = "LRU" ;
  else if( way == '3' ) temp = "Least Frequently Used Page Replacement" ;
  else if( way == '4' ) temp = "Most Frequently Used Page Replacement" ;
  else if( way == '5' ) temp = "Least Frequently Used LRU Page Replacement" ;
  */
  fout << "--------------FIFO-----------------------\n"  ;
  cout << "--------------FIFO-----------------------\n" ;
  
  int fault = 0 ;
  for( int i = 0 ; i < done1.size() ; i++ ) {
    fout << done1[i].page << "\t" ;
    cout << done1[i].page << "\t" ;
    for( int j = done1[i].stack.size() - 1 ; j >= 0 ; j-- ) {
    	fout << done1[i].stack[j].page  ;
    	cout << done1[i].stack[j].page  ;
    }

      if (  done1[i].fault == 'F' )
      {
        fault++ ;
        fout << "\tF"  ;
        cout << "\tF"  ;
      } // if

      fout <<"\n" ;
	  cout <<"\n" ;
    }
    
    fout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    fout << "  Page Frames = " << page << "\n\n" ;
    cout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    cout << "  Page Frames = " << page << "\n\n" ;
    
  fout << "--------------LRU-----------------------\n"  ;
  cout << "--------------LRU-----------------------\n" ;
  
  fault = 0 ;
  for( int i = 0 ; i < done2.size() ; i++ ) {
    fout << done2[i].page << "\t" ;
    cout << done1[i].page << "\t" ;
    for( int j = done2[i].stack.size() - 1 ; j >= 0 ; j-- ) {
    	fout << done2[i].stack[j].page  ;
    	cout << done2[i].stack[j].page  ;
    }

      if (  done2[i].fault == 'F' )
      {
        fault++ ;
        fout << "\tF"  ;
        cout << "\tF"  ;
      } // if

      fout <<"\n" ;
	  cout <<"\n" ;
    }
    
    fout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    fout << "  Page Frames = " << page << "\n\n" ;
    cout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    cout << "  Page Frames = " << page << "\n\n" ;
    
  fout << "--------------Least Frequently Used Page Replacement-----------------------\n"  ;
  cout << "--------------Least Frequently Used Page Replacement-----------------------\n" ;
  
  fault = 0 ;
  for( int i = 0 ; i < done3.size() ; i++ ) {
    fout << done3[i].page << "\t" ;
    cout << done3[i].page << "\t" ;
    for( int j = done3[i].stack.size() - 1 ; j >= 0 ; j-- ) {
    	fout << done3[i].stack[j].page  ;
    	cout << done3[i].stack[j].page  ;
    }

      if (  done3[i].fault == 'F' )
      {
        fault++ ;
        fout << "\tF"  ;
        cout << "\tF"  ;
      } // if

      fout <<"\n" ;
	  cout <<"\n" ;
    }
    
    fout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    fout << "  Page Frames = " << page << "\n\n" ;
    cout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    cout << "  Page Frames = " << page << "\n\n" ;
    
  fout << "--------------Most Frequently Used Page Replacement-----------------------\n"  ;
  cout << "--------------Most Frequently Used Page Replacement-----------------------\n" ;
  
  fault = 0 ;
  for( int i = 0 ; i < done4.size() ; i++ ) {
    fout << done4[i].page << "\t" ;
    cout << done4[i].page << "\t" ;
    for( int j = done4[i].stack.size() - 1 ; j >= 0 ; j-- ) {
    	fout << done4[i].stack[j].page  ;
    	cout << done4[i].stack[j].page  ;
    }

      if (  done4[i].fault == 'F' )
      {
        fault++ ;
        fout << "\tF"  ;
        cout << "\tF"  ;
      } // if

      fout <<"\n" ;
	  cout <<"\n" ;
    }
    
    fout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    fout << "  Page Frames = " << page << "\n\n" ;
    cout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    cout << "  Page Frames = " << page << "\n\n" ;
    
  fout << "--------------Least Frequently Used LRU Page Replacement-----------------------\n"  ;
  cout << "--------------Least Frequently Used LRU Page Replacement-----------------------\n" ;
  
  fault = 0 ;
  for( int i = 0 ; i < done5.size() ; i++ ) {
    fout << done5[i].page << "\t" ;
    cout << done5[i].page << "\t" ;
    for( int j = done5[i].stack.size() - 1 ; j >= 0 ; j-- ) {
    	fout << done5[i].stack[j].page  ;
    	cout << done5[i].stack[j].page  ;
    }

      if (  done5[i].fault == 'F' )
      {
        fault++ ;
        fout << "\tF"  ;
        cout << "\tF"  ;
      } // if

      fout <<"\n" ;
	  cout <<"\n" ;
    }
    
    fout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    fout << "  Page Frames = " << page << "\n" ;
    cout << "Page Fault = " << fault << "  Page Replaces = " << fault - ( page - '0' ) ;
    cout << "  Page Frames = " << page << "\n" ;
 
    
}

int main(int argc, char** argv) {
    string filename ;
    vector<int>nondo ;
    char page = '\0', way = '\0' ;
    
    while(1){
      do {
        cout << "Please enter file name.  no.txt\n" ;
        cin >> filename ;

      } while( !isexsit( filename, nondo, way, page ) ) ;
      
      
    vector<donedata> fifodone, lrudone, lfufidone, mfufidone, lfulrudone ;
    if ( way == '1' ) {
      FIFO( nondo, page, fifodone );
      printsingle( fifodone, way, filename, page ) ;
	}
	else if ( way == '2' ) {
      LRU( nondo, page, lrudone );
      printsingle( lrudone, way, filename, page ) ;
	}
	else if ( way == '3' ) {
      LFUFI( nondo, page, lfufidone );
      printsingle( lfufidone, way, filename, page ) ;
	}
	else if ( way == '4' ) {
      MFUFI( nondo, page, mfufidone );
      printsingle( mfufidone, way, filename, page ) ;
	}
	else if ( way == '5' ) {
      LFULRU( nondo, page, lfulrudone );
      printsingle( lfulrudone, way, filename, page ) ;
	}
	else if ( way == '6' ) {
      FIFO( nondo, page, fifodone );
      LRU( nondo, page, lrudone );
      LFUFI( nondo, page, lfufidone );
      MFUFI( nondo, page, mfufidone );
      LFULRU( nondo, page, lfulrudone );

      printall( fifodone, lrudone, lfufidone, mfufidone, lfulrudone, filename, page ) ;
	}
	
      /*
    for( int i = 0 ; i < nondo.size() ; i++ ) {
	  cout << nondo[i] << "\n" ;
    }
*/ 
      nondo.clear() ;
      page = '\0', way = '\0' ;
    }
	
	return 0;
}
