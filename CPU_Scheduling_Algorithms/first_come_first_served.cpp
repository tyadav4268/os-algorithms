/*
Submitted By:
	Tej Pratap Yadav
	195104
*/
#include <iostream>
#include <queue>
using namespace std;

class Process{
	int arrival_time;
	int burst_time;

	public:

	Process(int at, int bt){
		arrival_time = at;
		burst_time = bt;
	}

	void print_process(){
		cout<<"Arrival Time "<<arrival_time<<"\t";
		cout<<"Burst Time "<<burst_time<<endl;
	}

	int get_arrival_time(){
		return arrival_time;
	}
	int get_burst_time(){
		return burst_time;
	}

};

void print_desc(queue<Process> process_queue, int num_of_processes){
	int sno = 0;
	cout<<"=================================="<<endl;
	cout<<"\tDescription of Processes"<<endl;
	while(sno < num_of_processes){
		cout<<"Process Number: "<<sno++<<"\t";
		Process process = process_queue.front();
		process.print_process();
		process_queue.pop();
		cout<<endl;
	}
	cout<<"================================="<<endl;
}

void prepare_gantt_chart(queue<Process> process_queue, int num_of_processes){
	cout<<"\n\tGantt Chart\n";
	float total_turnaround_time = 0;;
	float total_waiting_time = 0;
	int process_start_time = 0;
	int process_finish_time = 0;
	for(int i = 0; i < num_of_processes; i++){
		Process process = process_queue.front();
		cout<<"Process "<<i<<endl;
		cout<<"Started at: "<<process_start_time<<endl;
		process = process_queue.front();
		process_finish_time += process.get_burst_time();
		cout<<"finished at: "<<process_finish_time<<endl;
		total_turnaround_time += process_finish_time - process.get_arrival_time();
		total_waiting_time += (process_finish_time - process.get_arrival_time()) - process.get_burst_time();
		process_start_time = process_finish_time;
		process_queue.pop();
		cout<<endl;
	}
	cout<<"\n\nAvg Turnaround Time = "<<total_turnaround_time/num_of_processes;
	cout<<"\nAvg Waiting Time = "<<total_waiting_time/num_of_processes<<endl;
}

void first_come_first_served(){
	cout<<"Enter Number of Processes: ";
	int num_of_processes;
	cin>>num_of_processes;
	queue<Process> process_queue;
	int num_of_process = 0;
	while(num_of_process < num_of_processes){
		cout<<"\nEnter Arrival Time of Process "<<num_of_process<<": ";
		int at;
		cin>>at;
		cout<<"Enter Burst Time of Process "<<num_of_process<<": ";
		int bt;
		cin>>bt;
		Process process(at, bt);
		process_queue.push(process);
		num_of_process++;
		cout<<"\n";
	}
	print_desc(process_queue, num_of_processes);
	prepare_gantt_chart(process_queue, num_of_processes);
}


int main(){
	cout<<"First Come First Served\n";
	cout<<"--------------------------"<<endl;
	first_come_first_served();
}
