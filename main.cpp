#include <iostream>
#include <ctype.h>
#include <string.h>
using namespace std;
int main(){
    int numStud , numCour;
     // Accept the user to enter the number of students and subjects.
    cout<<"Enter the number of students: ";
    cin>>numStud;
    cout<<"Enter the number of courses: ";
    cin>>numCour;

    int n  , *tally = new int[numStud] , *orders;
    unsigned int *crHr = new unsigned int[numCour];
    char choice ;
    string *subName = new string[numCour] , *studId = new string[numStud] , **gradeMark = new string*[numStud] , searchId , searchSub , lastId , orderId;
    float *totalCrHr = new float[numStud] , *totalPoint = new float[numStud] , *cgpa = new float[numStud] , *totalMark = new float[numStud];
    float **subMark = new float*[numStud] , **point = new float*[numStud] , *avg = new float[numStud] , *temp = new float[numStud] , order , minValue;

     // Create the students array using the specified number of student objects
    for(int i=0; i<numStud; ++i){
        totalCrHr[i] = 0;
        totalPoint[i] = 0;
        totalMark[i] = 0;
        temp[i] = 0;

        //declaring dynamic 2D arrays
        subMark[i] = new float[numCour];
        point[i] = new float[numCour];
        gradeMark[i] = new string[numCour];
    }
    //Accept subject name and creadit hour
    for(int i=0; i<numCour; ++i){
        cout<<endl<<"Enter the name of course(don't use space): "<<i+1;
        cin>>subName[i];


        cout<<"Enter the credit hour of "<<subName[i]<<" : ";
        cin>>crHr[i];
    }

    //Accept ID and check if student is already exist

    for(int i=0; i<numStud; ++i){
        tally[i]=0;
        int error;
        do{
            error=0;
            cout<<endl<<"Enter the ID of student(eg. ETS0404/14): "<<i+1;
            cin>>studId[i];

            for(int j=0; j<i; ++j){
                if(studId[i] == studId[j]){
                    cout<<"The student is already exist."<<endl;
                    error+=1;
                    break;
                }
            }
            tally[i]+=1;
        }while(error!=0 && tally[i]<3);

        if(tally[i] == 3){
            continue;
        }

        //Accept mark for each subject and calculate the equivalent grade

        for(int j=0; j<numCour; ++j){

            int k=0;
            do{
                cout<<"Enter the mark of "<<subName[j]<<" for "<<studId[i]<<" : ";
                cin>>subMark[i][j];

            }while((subMark[i][j] < 0 || subMark[i][j] > 100));

            if(subMark[i][j] >= 85){
                point[i][j] = 4.0;
                gradeMark[i][j] = "A ";
            }
            else if(subMark[i][j] >= 75){
                point[i][j] = 3.5;
                gradeMark[i][j] = "B+";
            }
            else if(subMark[i][j] >= 70){
                point[i][j] = 3.0;
                gradeMark[i][j] = "B ";
            }
            else if(subMark[i][j] >= 60){
                point[i][j] = 2.5;
                gradeMark[i][j] = "C+";
            }
            else if(subMark[i][j] >= 50){
                point[i][j] = 2.0;
                gradeMark[i][j] = "C ";
            }
            else if(subMark[i][j] >= 40){
                point[i][j] = 1.5;
                gradeMark[i][j] = "D ";
            }
            else{
                point[i][j] = 0.0;
                gradeMark[i][j] = "F ";
            }



            temp[i] += 1;
            totalMark[i] += subMark[i][j];

            totalPoint[i] += (crHr[j] * point[i][j]);
            totalCrHr[i] += crHr[j];
        }



        avg[i] = totalMark[i] / temp[i];
        cgpa[i] = totalPoint[i] / totalCrHr[i];
    }
    //order student IDs alphabetically (in ascending order)
    orders = new int[numStud];
    lastId = studId[0];
    for(int i=0; i<numStud; ++i){
        if(tally[i] == 3){
            continue;
        }
        if(lastId <= studId[i]){
            lastId = studId[i];
            orders[numStud-1] = i;
        }
    }
    for(int i=0; i<numStud; ++i){
        if(tally[i] == 3){
            continue;
        }
        orderId = lastId;
        for(int j=0; j<numStud; ++j){
            int count=0;
            for(int k=0; k<i; ++k){
                if(j == orders[k]){
                    count += 1;
                    break;
                }
            }
            if(count==1){
                continue;
            }
            if(orderId >= studId[j]){
                orderId = studId[j];
                orders[i] = j;
            }
        }

    }

    //print the upper borders and titles of the table
    cout<<endl<<"    ";
    for(int i=0; i<numCour; ++i){
        cout<<"        ";
    }
    cout<<"STUDENT'S MARK SHEET"<<endl;

    cout<<"______________";
    for(int i=0; i<numCour; ++i){
        cout<<"________________";
    }
    cout<<"______________________"<<endl;

    cout<<" Stud. ID       ";
    for(int i=0; i<numCour; ++i){
        cout<<"    "<<subName[i]<<"        ";
    }
    cout<<"Average    CGPA"<<endl;

    cout<<"              ";
    for(int i=0; i<numCour; ++i){
        cout<<"________________";
    }
    cout<<endl;

    cout<<"                ";
    for(int i=0; i<numCour; ++i){
        cout<<"Mark : Grade    ";
    }
    cout<<endl;

    cout<<"______________";
    for(int i=0; i<numCour; ++i){
        cout<<"________________";
    }
    cout<<"______________________"<<endl;

    //print each row of the table in ascending order of student IDs
    for(int i=0; i<numStud; ++i){
        if(tally[orders[i]] == 3){
            continue;
        }
        cout<<' '<<studId[orders[i]]<<"   ";
        for(int j=0; j<numCour; ++j){

            cout<<"    "<<subMark[orders[i]][j]<<" : "<<gradeMark[orders[i]][j]<<"     ";
        }
        if(temp[orders[i]] == 0){
            cout<<"    --        --"<<endl<<endl;
            continue;
        }
        cout<<"    "<<avg[orders[i]]<<"        "<<cgpa[orders[i]]<<endl;
        if(i<numStud-1){
            cout<<endl;
        }
    }

    //print the lower borders of the table
    cout<<"______________";
    for(int i=0; i<numCour; ++i){
        cout<<"________________";
    }
    cout<<"______________________"<<endl<<endl;
    delete []orders;

    int COUNT = 0;
    do{
        cout<<"Enter 'S' to search for the result of a specific student\nEnter 'C' to get the Top n results based on CGPA\nYour choice: ";
        cin>>choice;
        choice = toupper(choice);

        int error = 0;
        switch(choice){
            case 'S':
                cout<<"Enter the Id number: ";
                cin>>searchId;
                for(int i=0; i<numStud; ++i){
                    if(tally[i] == 3){
                        continue;
                    }
                    if(studId[i] == searchId){
                        cout<<endl<<"______________";
                        for(int i=0; i<numCour; ++i){
                            cout<<"________________";
                        }
                        cout<<"______________________"<<endl;
                        cout<<" Stud. ID       ";
                        for(int i=0; i<numCour; ++i){
                            cout<<"    "<<subName[i]<<"        ";
                        }
                        cout<<"Average    CGPA"<<endl;

                        cout<<"              ";
                        for(int i=0; i<numCour; ++i){
                            cout<<"________________";
                        }
                        cout<<endl;

                        cout<<"                ";
                        for(int i=0; i<numCour; ++i){
                            cout<<"Mark : Grade    ";
                        }
                        cout<<endl;

                        cout<<"______________";
                        for(int i=0; i<numCour; ++i){
                            cout<<"________________";
                        }
                        cout<<"______________________"<<endl;

                        cout<<' '<<studId[i]<<"   ";
                        for(int j=0; j<numCour; ++j){
                            cout<<"    "<<subMark[i][j]<<" : "<<gradeMark[i][j]<<"     ";
                        }
                        if(temp[i] == 0){
                            cout<<"    --        --"<<endl<<endl;
                        }
                        cout<<"    "<<avg[i]<<"        "<<cgpa[i]<<endl;
                        cout<<"______________";
                        for(int j=0; j<numCour; ++j){
                            cout<<"________________";
                        }
                        cout<<"______________________"<<endl<<endl;
                        break;
                    }
                    else if(i == numStud - 1){
                        cout<<"\nID could not be found.\n"<<endl;
                    }
                }
                break;

            case 'C':
                int n=5;

                //find top 5 students in descending order of CGPA
                orders = new int[n];
                minValue = cgpa[0];
                for(int i=0; i<numStud; ++i){
                    if(tally[i] == 3){
                        continue;
                    }
                    if(minValue >= cgpa[i]){
                        minValue = cgpa[i];
                        orders[n-1] = i;
                    }
                }
                for(int i=0; i<n; ++i){
                    if(tally[i] == 3){
                        continue;
                    }
                    order = minValue;
                    for(int j=0; j<numStud; ++j){
                        int count=0;
                        for(int k=0; k<i; ++k){
                            if(j == orders[k]){
                                count += 1;
                                break;
                            }
                        }
                        if(count==1){
                            continue;
                        }
                        if(order <= cgpa[j]){
                            order = cgpa[j];
                            orders[i] = j;
                        }
                    }

                }

                //print upper borders and titles of the table
                cout<<" ";
                for(int i=0; i<numCour; ++i){
                    cout<<"        ";
                }

                cout<<"Top 5 based on CGPA result"<<endl;


                cout<<"______________";
                for(int i=0; i<numCour; ++i){
                    cout<<"________________";
                }
                cout<<"______________________"<<endl;

                cout<<" Stud. ID       ";
                for(int i=0; i<numCour; ++i){
                    cout<<"    "<<subName[i]<<"        ";
                }
                cout<<"Average    CGPA"<<endl;

                cout<<"              ";
                for(int i=0; i<numCour; ++i){
                    cout<<"________________";
                }
                cout<<endl;

                cout<<"                ";
                for(int i=0; i<numCour; ++i){
                    cout<<"Mark : Grade    ";
                }
                cout<<endl;

                cout<<"______________";
                for(int i=0; i<numCour; ++i){
                    cout<<"________________";
                }
                cout<<"______________________"<<endl;

                //print top 5 students in descending order of CGPA
                for(int i=0; i<n; ++i){
                    cout<<' '<<studId[orders[i]]<<"   ";
                    for(int j=0; j<numCour; ++j){
                        cout<<"    "<<subMark[orders[i]][j]<<" : "<<gradeMark[orders[i]][j]<<"     ";
                    }
                    if(temp[orders[i]] == 0){
                        cout<<"    --        --"<<endl<<endl;
                        continue;
                    }
                    cout<<"    "<<avg[orders[i]]<<"        "<<cgpa[orders[i]]<<endl;
                    if(i<n-1){
                        cout<<endl;
                    }
                }

                //print the lower borders of the table
                cout<<"______________";
                for(int i=0; i<numCour; ++i){
                    cout<<"________________";
                }
                cout<<"______________________"<<endl<<endl;
                delete []orders;

                break;


        }
    }while(COUNT<3);

    return 0;
}

