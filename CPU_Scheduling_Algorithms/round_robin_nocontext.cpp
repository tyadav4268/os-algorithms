#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Process{
    int id;
    int arrival_time;
    int burst_time;
    int finish_time;
    int valid_bit;
    int initial_burst_time;
    int initial_arrival_time;
};

Process fake_process;
Process current_process;
void getProcess(int &cpu_time, queue<Process> &process_queue);
void calculation(vector<Process> process_queue);
void sort_process_queue(queue<Process> &process_queue);

int main(){
    // SIZE stores total number of processes
    // time_quanta stores the value of Time Quanta
    int SIZE, time_quanta;
    cout<<"Enter Number of Processes: ";
    cin>>SIZE;
    cout<<"Enter value of Time Quanta: ";
    cin>>time_quanta;

    cout<<"\nEnter Details of Processes: \n";
    // queue to store the Processes
    queue<Process> process_queue;
    for(int i = 0; i < SIZE; i++){
        Process process;
        process.id = i;
        cout<<"\nProcess Id: "<<i<<endl;
        cout<<"Enter Arrival Time: ";
        cin>>process.arrival_time;
        process.initial_arrival_time = process.arrival_time;
        cout<<"Enter Burst Time: ";
        cin>>process.burst_time;
        process.initial_burst_time = process.burst_time;
        process.finish_time = -1;
        process.valid_bit = 1;
        process_queue.push(process);
    }
    sort_process_queue(process_queue);
    // Scheduling as per the Round Robin Algorithm
    // finished_vector stores the processes those have
    // finished Execution
    vector<Process> finished_vector;
    int cpu_time = 0, waste_time = 0, remaining_time = time_quanta;
    cout<<"\n\tStarting Execution\t CPU Time: "<<cpu_time<<endl;
    getProcess(cpu_time, process_queue);
    while(finished_vector.size() != SIZE){

        if(current_process.valid_bit == -1){
            // cout<<"\nNo Process \n";
            cpu_time++;
            waste_time++;
            getProcess(cpu_time, process_queue);
        }
        else{
            cout<<"\nServing process: "<<current_process.id<<endl;
            cpu_time++;
            remaining_time--;
            current_process.burst_time--;
            cout<<"\nCPU Time: "<<cpu_time<<"\tTime Quanta Remaining: "<<remaining_time<<endl;
            // cout<<"\nburst time of process "<<current_process.id<<" "<<current_process.burst_time<<endl;
            if(current_process.burst_time == 0){
                cout<<"\n===Process "<<current_process.id<<" Finished====="<<endl;
                current_process.finish_time = cpu_time;
                finished_vector.push_back(current_process);
                getProcess(cpu_time, process_queue);
                remaining_time = time_quanta;
            }
            else if(remaining_time == 0){
                cout<<"\n!!Time Quanta is over!!\n";
                Process previous_process = current_process;
                previous_process.arrival_time = cpu_time;
                getProcess(cpu_time, process_queue);
                process_queue.push(previous_process);
                remaining_time = time_quanta;
            }
        }
    }

    // Printing the details of processes after Execution
    cout<<"\nProcesses after execution:\n";
    for(int i = 0; i < SIZE; i++){
        Process process = finished_vector[i];
        cout<<"\nProcess Id: "<<process.id<<endl;
        cout<<"Process Arrival Time: "<<process.initial_arrival_time<<endl;
        cout<<"Process Finish Time: "<<process.finish_time<<endl;
    }
    calculation(finished_vector);
    return 0;
}

void getProcess(int &cpu_time, queue<Process>& process_queue){
    // cout<<"\nIN getProcess: "<<"cpu_time: \n"<<cpu_time;
    fake_process.valid_bit = -1;
    // checking if any process has arrived or not
    sort_process_queue(process_queue);
    if(process_queue.front().arrival_time <= cpu_time){
        if(cpu_time > 0){
            cout<<"\nSwitching to new Process.......\n";
            cout<<"\nCurrent CPU Time: "<<cpu_time<<endl;
        }

        current_process = process_queue.front();
        process_queue.pop();
    }
    else{
        current_process = fake_process;
    }
}

void sort_process_queue(queue<Process> &process_queue){
	vector<Process> process_vector;
	while(!process_queue.empty()){
		process_vector.push_back(process_queue.front());
		process_queue.pop();
	}
	sort(process_vector.begin(), process_vector.end(), [](Process &a, Process &b){
    	return (a.arrival_time < b.arrival_time);
    });
	for(int i = 0; i < process_vector.size(); i++){
		process_queue.push(process_vector[i]);
	}
}

void calculation(vector<Process> process_queue){
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    int size = process_queue.size();
    for(int i = 0; i < size; i++){
        int waiting_time = 0;
        int turnaround_time = 0;
        turnaround_time = process_queue[i].finish_time - process_queue[i].initial_arrival_time;
        waiting_time = turnaround_time - process_queue[i].initial_burst_time;
        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;
    }
    cout<<"\nAverage Turnaround Time: " << total_turnaround_time / size;
    cout<<"\nAverage Waiting Time: " << total_waiting_time / size;
}
