#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<math.h>
#include<iomanip>
#include<numeric>
#include<algorithm>
using namespace std;

/*
 // bitrate to VQM //
 0      1.000
 250    0.765
 375    0.500
 500    0.290
 1000   0.100
 2000   0.000
*/

// Quality idx mapping to VQM //
const double QtoVQM[20]={
    0.953,  //100
    0.906,  //200
    0.859,  //240
    0.812,  //370
    0.765,  //540
    0.1988,  //740
    0.100,  //1000
    0,  //1500
    0,      //2250
    0,      //700
    0,      //900
    0,      //1200
    0,      //1500
    0,      //2000
    0,      //2500
    0,      //3000
    0,      //4000
    0,      //5000
    0,      //6000
    0       //8000
};

const double alpha=3.2;
const double a=3.8;
const double b=4.2;
const double c=2.6;
const double k=0.02;
const double B_one=75.6;
const double B_two=48.2;
const double T=6.0;         // Seg Size

int main(int argc, char* argv[]){
    ifstream infile;
    infile.open(argv[1], ifstream::in);
    
    // Measurement Parameter //
    double initDelay=0;
    double stallCnt=0;
    double stallDuration=0;
    vector<int> QidxSequence;
    
    // Impairment Score //
    double I_id=0;
    double I_st=0;
    double I_lv=0;
    
    string tmpline;
    string field;
    
    // Loop Cnt //
    int cnt=0;
    
    while(getline(infile, tmpline)){
        // First line: init delay //
        initDelay=atof(tmpline.c_str());
        
        // Second line: stall count //
        getline(infile, tmpline);
        stallCnt=atof(tmpline.c_str());
        
        // Third line: stall duration //
        getline(infile, tmpline);
        stallDuration=atof(tmpline.c_str());
        
        // Forth line: quality idx sequence //
        getline(infile, tmpline);
        stringstream element(tmpline);
        QidxSequence.clear();
        while(getline(element,field,',')){
            QidxSequence.push_back(atoi(field.c_str()));
        }
        // Read end //
        
        // Impairment of init delay //
        I_id=alpha*initDelay;
        I_id=(I_id<100.0)? I_id:100.0;
        
        // Impairment of stall //
        I_st=a*stallDuration+b*stallCnt-c*sqrt(stallDuration*stallCnt);
        
        // Impairment of quality //
        double D=0;
        double P_one=QtoVQM[QidxSequence[0]];
        for(int i=1;i<QidxSequence.size();i++){
            // Determine D //
            D=(QidxSequence[i-1]==QidxSequence[i])? D+1:0;
            
            P_one=P_one+QtoVQM[QidxSequence[i]]*exp(k*T*D);
        }
        P_one=P_one/QidxSequence.size();
        
        double P_two=0;
        for(int i=0;i<QidxSequence.size()-1;i++){
            // Determine sign //
            if(QtoVQM[QidxSequence[i+1]]-QtoVQM[QidxSequence[i]]<=0)
                continue;
            P_two=P_two+pow(QtoVQM[QidxSequence[i+1]]-QtoVQM[QidxSequence[i]],2.0);
        }
        P_two=P_two/QidxSequence.size();
        
        I_lv=B_one*P_one+B_two*P_two;
        
        // Final Score //
        cout<<"// Cnt "<<++cnt<<" //"<<endl;
        cout<<"Iid: "<<I_id<<endl;
        cout<<"Ist: "<<I_st<<endl;
        cout<<"Ilv: "<<I_lv<<endl;
        cout<<"fn:  "<<100.0-I_id-I_st-I_lv<<endl;
    }
    
    return 0;
}

/*
// Quality idx and Video bitrate(kbit!!!) //
 50
 100
 150
 200
 250
 300
 400
 500
 600
 700
 900
 1200
 1500
 2000
 2500
 3000
 4000
 5000
 6000
 8000
*/